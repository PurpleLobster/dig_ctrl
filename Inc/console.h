/*
 * console.h
 *
 *  Created on: Mar 19, 2018
 *      Author: root
 */

#ifndef APPLICATION_USER_CONSOLE_H_
#define APPLICATION_USER_CONSOLE_H_

#include "stm32f1xx_hal.h"

#define RX_BUF_SIZE 10

void CONSOLE_INIT(UART_HandleTypeDef *huart);

uint8_t ConsolePollBuffer(void);
void ConsoleParseBuffer(void);
void ConsoleParseCommand(void);

#endif /* APPLICATION_USER_CONSOLE_H_ */

