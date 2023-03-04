/*
 * file:        uart.c
 * author:      VasiliyMatlab
 * version:     1.0
 * date:        04.03.2022
 * copyright:   Vasiliy (c) 2023
 */

#include "stddef.h"

#include "uart.h"

// Initialize UART registers
int32_t uart_init(uartregs_t *uart, uint32_t baseaddr) {
	uart = (uartregs_t *) (intptr_t) (baseaddr + UART_REGISTER_OFFSET);

	uart->ctrl = UART_FIFO_RX_RESET | UART_FIFO_TX_RESET;	// reset FIFO-s
	uart->ctrl = UART_ENABLE_INTR;							// enable interrupt

	return 0;
}

// Reset UART
void uart_reset(uartregs_t *uart) {
	uart->ctrl = UART_FIFO_RX_RESET | UART_FIFO_TX_RESET;	// reset FIFO-s
	uart->ctrl = UART_ENABLE_INTR;							// enable interrupt
}

// Является ли передатчик пустым
__attribute__((always_inline)) _Bool uart_istxempty(uartregs_t *uart) {
	return (uart->state & UART_TX_FIFO_EMPTY) ? 1 : 0;
}

// Заполнен ли передатчик
__attribute__((always_inline)) _Bool uart_istxfull(uartregs_t *uart) {
	return (uart->state & UART_TX_FIFO_FULL) ? 1 : 0;
}

// Является ли приемник пустым
__attribute__((always_inline)) _Bool uart_isrxempty(uartregs_t *uart) {
	return (uart->state & UART_RX_FIFO_NOT_EMPTY) ? 0 : 1;
}

// Заполнен ли приемник
__attribute__((always_inline)) _Bool uart_isrxfull(uartregs_t *uart) {
	return (uart->state & UART_RX_FIFO_FULL) ? 1 : 0;
}

// Послать len данных из buf в UART
uint32_t uart_sendbuf(uartregs_t *uart, uint8_t *buf, uint32_t len) {
	// Если передатчик не пустой, то не посылаем данные
	if (!uart_istxempty(uart)) {
		return 0;
	}

	// Если длина данных больше, чем размер FIFO у UART, то обрезаем данные
	if (len > UART_FIFO_SIZE) {
		len = UART_FIFO_SIZE;
	}

	// Записываем данные в передатчик
	for (uint8_t i = 0; i < len; i++) {
		uart->tx = buf[i];
	}

	return len;
}

// Принять len данных из UART в buf
uint32_t uart_recvbuf(uartregs_t *uart, uint8_t *buf) {
	uint32_t len = 0;

	// Если в UART-е ошибка, то не читаем данные
	if (uart->state & (UART_PARITY_ERROR | UART_FRAME_ERROR | UART_OVERRUN_ERROR)) {
		uart_reset(uart);
		return 0;
	}

	// Пока приемник не пустой, пишем данные в выходной буфер
	while (!uart_isrxempty(uart)) {
		buf[len] = uart->rx;
		len++;
	}

	return len;
}
