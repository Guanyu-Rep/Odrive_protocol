#include "common_inc.h"
#include "interface_uart.hpp"
#include "ascii_processor.hpp"
#include "fibre/protocol.hpp"
#include "usart.h"

#define UART_TX_BUFFER_SIZE 64
#define UART_RX_BUFFER_SIZE 64

// DMA open loop continous circular buffer
// 1ms delay periodic, chase DMA ptr around
static uint8_t dma_rx_buffer[UART_RX_BUFFER_SIZE];
static uint32_t dma_last_rcv_id;

// FIXME: the stdlib doesn't know about CMSIS threads, so this is just a global variable
// static thread_local uint32_t deadline_ms = 0;

osThreadId_t uartServerTaskHandle;


class UART1Sender : public StreamSink
{
public:
    UART1Sender()
    {
        channelType = CHANNEL_TYPE_UART1;
    }

    int process_bytes(const uint8_t* buffer, size_t length, size_t* processed_bytes) override
    {
        // Loop to ensure all bytes get sent
        while (length)
        {
            size_t chunk = length < UART_TX_BUFFER_SIZE ? length : UART_TX_BUFFER_SIZE;
            // wait for USB interface to become ready
            // TODO: implement ring buffer to get a more continuous stream of data
            // if (osSemaphoreWait(sem_uart_dma, deadline_to_timeout(deadline_ms)) != osOK)
            if (osSemaphoreAcquire(sem_uart1_dma, PROTOCOL_SERVER_TIMEOUT_MS) != osOK)
                return -1;
            // transmit chunk
            memcpy(tx_buf_, buffer, chunk);
            if (HAL_UART_Transmit_DMA(&huart1, tx_buf_, chunk) != HAL_OK)
                return -1;
            buffer += chunk;
            length -= chunk;
            if (processed_bytes)
                *processed_bytes += chunk;
        }
        //osSemaphoreRelease(sem_uart1_dma);
        return 0;
    }

    size_t get_free_space() override
    { return SIZE_MAX; }

private:
    uint8_t tx_buf_[UART_TX_BUFFER_SIZE];
} uart1_stream_output;

StreamSink* uart1StreamOutputPtr = &uart1_stream_output;
StreamBasedPacketSink uart1_packet_output(uart1_stream_output);
BidirectionalPacketBasedChannel uart1_channel(uart1_packet_output);
StreamToPacketSegmenter uart1_stream_input(uart1_channel);

static void UartServerTask(void* ctx)
{
    (void) ctx;

    for (;;)
    {
        // Check for UART errors and restart recieve DMA transfer if required
        if (huart1.ErrorCode != HAL_UART_ERROR_NONE)
        {
            HAL_UART_AbortReceive(&huart1);
            HAL_UART_Receive_DMA(&huart1, dma_rx_buffer, sizeof(dma_rx_buffer));
        }
        // Fetch the circular buffer "write pointer", where it would write next
        uint32_t new_rcv_id = UART_RX_BUFFER_SIZE - huart1.hdmarx->Instance->NDTR;

        // deadline_ms = timeout_to_deadline(PROTOCOL_SERVER_TIMEOUT_MS);
        // Process bytes in one or two chunks (two in case there was a wrap)
        if (new_rcv_id < dma_last_rcv_id)
        {
            uart1_stream_input.process_bytes(dma_rx_buffer + dma_last_rcv_id,
                                             UART_RX_BUFFER_SIZE - dma_last_rcv_id,
                                             nullptr); // TODO: use process_all
            ASCII_protocol_parse_stream(dma_rx_buffer + dma_last_rcv_id,
                                        UART_RX_BUFFER_SIZE - dma_last_rcv_id, uart1_stream_output);
            dma_last_rcv_id = 0;
        }
        if (new_rcv_id > dma_last_rcv_id)
        {
            uart1_stream_input.process_bytes(dma_rx_buffer + dma_last_rcv_id,
                                             new_rcv_id - dma_last_rcv_id,
                                             nullptr); // TODO: use process_all
            ASCII_protocol_parse_stream(dma_rx_buffer + dma_last_rcv_id,
                                        new_rcv_id - dma_last_rcv_id, uart1_stream_output);
            dma_last_rcv_id = new_rcv_id;
        }

        osDelay(1);
    };
}

const osThreadAttr_t uartServerTask_attributes = {
    .name = "UartServerTask",
    .stack_size = 2000,
    .priority = (osPriority_t) osPriorityNormal,
};

void StartUartServer()
{
    //HAL_UART_Receive_IT(&huart1, (uint8_t *)&dma_rx_buffer[0],1);//调用中断接收函数;
    //HAL_UART_Receive_IT(&huart2, (uint8_t *)&dma_rx_buffer[1],1);//调用中断接收函数;
    // DMA is set up to receive in a circular buffer forever.
    // We don't use interrupts to fetch the data, instead we periodically read
    // data out of the circular buffer into a parse buffer, controlled by a state machine
    HAL_UART_Receive_DMA(&huart1, dma_rx_buffer, sizeof(dma_rx_buffer));
    dma_last_rcv_id = UART_RX_BUFFER_SIZE - huart1.hdmarx->Instance->NDTR;


    // Start UART communication thread
    uartServerTaskHandle = osThreadNew(UartServerTask, nullptr, &uartServerTask_attributes);
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef* huart)
{
    if (huart->Instance == USART1) {
        osSemaphoreRelease(sem_uart1_dma);
    }
}

//void HAL_UART_RxCpltCallback(UART_HandleTypeDef* huart)
//{
//    if (huart->Instance == USART1) {
//        //osSemaphoreRelease(sem_uart1_dma);
//        HAL_UART_Receive_IT(&huart1, (uint8_t *) &dma_rx_buffer[0], 1);   //再开启接收中断（因为里面中断只会触发一次，因此需要再次开启）
//    }
//    else if (huart->Instance == USART2){
//        //osSemaphoreRelease(sem_uart2_dma);
//        HAL_UART_Receive_IT(&huart2, (uint8_t *) &dma_rx_buffer[1], 1);   //再开启接收中断（因为里面中断只会触发一次，因此需要再次开启）
//    }
//}
