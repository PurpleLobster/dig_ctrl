/*
 * console.c
 *
 *  Created on: Mar 19, 2018
 *      Author: root
 */

#include "console.h"
#include "commands.h"


UART_HandleTypeDef *huart;

uint32_t dma_ctr_old;
uint8_t rx_buff[RX_BUF_SIZE];
uint32_t buf_start=0;

uint8_t commandline[RX_BUF_SIZE];
uint8_t commandlineIndex = 0;



void CONSOLE_INIT(UART_HandleTypeDef *huart_ptr)
{
	huart = huart_ptr;
	HAL_UART_Receive_DMA(huart, rx_buff, RX_BUF_SIZE);
	dma_ctr_old = __HAL_DMA_GET_COUNTER(huart->hdmarx);
}

uint8_t ConsolePollBuffer(void)
{
	uint32_t dma_cntr = __HAL_DMA_GET_COUNTER(huart->hdmarx);
	if (dma_ctr_old != dma_cntr)
		{
		return 1;
		dma_ctr_old = dma_cntr;
		}
		else
		{
		return 0;
		}

}

void ConsoleParseBuffer(void)
{
uint32_t buf_end = RX_BUF_SIZE - __HAL_DMA_GET_COUNTER(huart->hdmarx); // -1

while (buf_start != buf_end)
	{
	commandline[commandlineIndex] = rx_buff[buf_start];
	commandlineIndex++;
	if (rx_buff[buf_start] == 13) // CR
		ConsoleParseCommand();

	if (commandlineIndex == RX_BUF_SIZE)  // buffer overflow
			commandlineIndex = 0;

	buf_start++;
	if (buf_start == RX_BUF_SIZE)
    	buf_start = 0;



	}

}
void ConsoleParseCommand (void)
{


	testje();

	HAL_UART_Transmit_IT(huart, commandline, commandlineIndex);
	commandlineIndex=0;
}




