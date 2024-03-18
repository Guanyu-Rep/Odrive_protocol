#include "common_inc.h"

// 5 User-Timers, can choose from htim7/htim10/htim11/htim13/htim14
//Timer timerCtrlLoop(&htim7, 200);



/* Thread Definitions -----------------------------------------------------*/
osThreadId_t LEDTaskHandle;
void LEDTask(void *pvParameters) {
    for(;;) {
        LED_R_TogglePin;
        Respond(*uart1StreamOutputPtr, "[sys] LED LOOP\n");
        osDelay(1000);
    }
}


/* Default Entry -------------------------------------------------------*/
void Main(void)
{

    // Init all communication staff, including USB-CDC/VCP/UART/CAN etc.
    InitCommunication();


    // Init & Run User Threads.
    const osThreadAttr_t LCDTask_attributes = {
            .name = "LCDTask",
            .stack_size = 128 * 8,
            .priority = (osPriority_t) osPriorityNormal,
    };
    LEDTaskHandle = osThreadNew(LEDTask, nullptr, &LCDTask_attributes);

    // System started, light switch-led up.
    //Respond(*uart1StreamOutputPtr, "[sys] Heap remain: %d Bytes\n", xPortGetMinimumEverFreeHeapSize());
//    pwm.SetDuty(PWM::CH_A1, 0.5);
}
