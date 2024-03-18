//
// Created by master on 2024/3/17.
//

#ifndef DMA_TEST_COMMON_INC_H
#define DMA_TEST_COMMON_INC_H

#ifdef __cplusplus
extern "C" {
#endif


#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "cmsis_os.h"

#include "main.h"
#include "gpio.h"
#include "usart.h"
#include "dma.h"

extern osSemaphoreId sem_uart1_dma;

void Main();

#ifdef __cplusplus
}
#endif

#include "communication.hpp"

#endif //DMA_TEST_COMMON_INC_H
