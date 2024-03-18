
/* Includes ------------------------------------------------------------------*/

#include "communication.hpp"
#include "common_inc.h"

/* Private defines -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Global constant data ------------------------------------------------------*/
/* Global variables ----------------------------------------------------------*/
/* Private constant data -----------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
volatile bool endpointListValid = false;
/* Private function prototypes -----------------------------------------------*/
/* Function implementations --------------------------------------------------*/
// @brief Sends a line on the specified output.

osThreadId_t commTaskHandle;
const osThreadAttr_t commTask_attributes = {
    .name = "commTask",
    .stack_size = 128*16,
    .priority = (osPriority_t) osPriorityNormal,
};

void InitCommunication(void)
{
    // Start command handling thread
    commTaskHandle = osThreadNew(CommunicationTask, nullptr, &commTask_attributes);

    while (!endpointListValid)
        osDelay(1);
}

osThreadId_t usbIrqTaskHandle;

// Thread to handle deffered processing of USB interrupt, and
// read commands out of the UART DMA circular buffer
void CommunicationTask(void* ctx)
{
    // Allow main init to continue
    endpointListValid = true;

    StartUartServer();

    for (;;)
    {
        osDelay(1000); // nothing to do
    }
}

extern "C" {
int _write(int file, const char* data, int len);
}

// @brief This is what printf calls internally
int _write(int file, const char* data, int len)
{
    uart1StreamOutputPtr->process_bytes((const uint8_t*) data, len, nullptr);

    return len;
}
