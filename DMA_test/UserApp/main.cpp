//
// Created by master on 2024/3/17.
//
#include "common_inc.h"

//#define BUFFERSIZE 255//可以接收的最大字符个数
//uint8_t ReceiveBuff[BUFFERSIZE]; //接收缓冲区
//uint8_t Rx_len;//接收完成中断标志，接收到字符长度
//extern DMA_HandleTypeDef hdma_usart1_rx;
//void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
//{
//    if(huart==&huart1)//判断是否是串口1中断
//        LED_G_TogglePin;//引脚C13电平反转
//}


/* Thread Definitions -----------------------------------------------------*/
osThreadId_t LEDTaskHandle;
void LEDTask(void *pvParameters) {
    for(;;) {
        LED_R_TogglePin;
        //Respond(*uart1StreamOutputPtr, "[sys] LED LOOP\n");
        osDelay(1000);
    }
}


void Main()
{
//    __HAL_UART_ENABLE_IT(&huart1, UART_IT_IDLE);//使能串口1 IDLE中断
//    /*第二个参数目前为数组 如果为变量需要加取地址符*/
//    HAL_UART_Receive_DMA(&huart1,ReceiveBuff,BUFFERSIZE);//使能接收


    InitCommunication();

    // Init & Run User Threads.
    const osThreadAttr_t LCDTask_attributes = {
            .name = "LCDTask",
            .stack_size = 128 * 8,
            .priority = (osPriority_t) osPriorityNormal,
    };
    LEDTaskHandle = osThreadNew(LEDTask, nullptr, &LCDTask_attributes);

}