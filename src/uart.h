/**
 * \file uart.h
 * \author VasiliyMatlab
 * \brief UART Lite module
 * \version 1.2
 * \date 05.04.2023
 * \copyright Vasiliy (c) 2023
 */

#ifndef __UART_H__
#define __UART_H__


#include <stdint.h>

#define UART_FIFO_TX_RESET			0x01	///< Reset the transmit FIFO
#define UART_FIFO_RX_RESET			0x02	///< Reset the receive FIFO
#define UART_ENABLE_INTR			0x10	///< Enable interrupt

#define UART_RX_FIFO_NOT_EMPTY		0x01	///< Receive FIFO has valid data
#define UART_RX_FIFO_FULL			0x02	///< Receive FIFO is full
#define UART_TX_FIFO_EMPTY			0x04	///< Transmit FIFO is empty
#define UART_TX_FIFO_FULL			0x08	///< Transmit FIFO is full
#define UART_INTR_ENABLED			0x10	///< Interrupts is enabled
#define UART_OVERRUN_ERROR			0x20	///< Overrun error has occured
#define UART_FRAME_ERROR			0x40	///< Frame error has occured
#define UART_PARITY_ERROR			0x80	///< Parity error has occured

#define UART_FIFO_SIZE				16		///< Receive/Ttransmit FIFO size

#define UART_REGISTER_OFFSET		0x00	///< UART Registers Offset
// #define UART_RX_FIFO_ADDR			0x00	///< Receive Data FIFO Address Offset
// #define UART_TX_FIFO_ADDR			0x04	///< Transmit Data FIFO Address Offset
// #define UART_STAT_REG_ADDR			0x08	///< UART Status Register Address Offset
// #define UART_CTRL_REG_ADDR			0x0C	///< UART Control Register Address Offset

/// UART Registers
typedef struct uartregs {
	volatile uint32_t rx;		///< Receive Data FIFO
	volatile uint32_t tx;		///< Transmit Data FIFO
	volatile uint32_t state;	///< Status Register
	volatile uint32_t ctrl;		///< Control Register
} uartregs_t;

/**
 * \brief Функция инициализации UART
 * 
 * \param[in,out] uart Указатель на дескриптор UART
 * \param[in] baseaddr Базовый адрес
 * \return 0; или -1 в случае ошибки
 */
int32_t uart_init(uartregs_t *uart, uint32_t baseaddr);

/**
 * \brief Сброс UART
 * 
 * \param[in,out] uart Указатель на дескриптор UART
 */
void uart_reset(uartregs_t *uart);

/**
 * \brief Функция, проверяющая, является ли
 * FIFO передатчика пустой
 * 
 * \param[in] uart Указатель на дескриптор UART
 * \return 1, если FIFO передатчика пуста; иначе 0
 */
_Bool uart_istxempty(uartregs_t *uart);

/**
 * \brief Функция, проверяющая, является ли
 * FIFO передатчика заполненной
 * 
 * \param[in] uart Указатель на дескриптор UART
 * \return 1, если FIFO передатчика заполнена; иначе 0 
 */
_Bool uart_istxfull(uartregs_t *uart);

/**
 * \brief Функция, проверяющая, является ли
 * FIFO приемника пустой
 * 
 * \param[in] uart Указатель на дескриптор UART
 * \return 1, если FIFO приемника пуста; иначе 0
 */
_Bool uart_isrxempty(uartregs_t *uart);

/**
 * \brief Функция, проверяющая, является ли
 * FIFO приемника заполненной
 * 
 * \param[in] uart Указатель на дескриптор UART
 * \return 1, если FIFO приемника заполнена; иначе 0 
 */
_Bool uart_isrxfull(uartregs_t *uart);

/**
 * \brief Функция, посылающая данные
 * из буфера в UART
 * 
 * \param[in,out] uart Указатель на дескриптор UART
 * \param[in] buf Указатель на буфер входных данных
 * \param[in] len Количество байт для отправки в UART
 * \return Количество байт, отправленных в UART
 */
uint32_t uart_sendbuf(uartregs_t *uart, uint8_t *buf, uint32_t len);

/**
 * \brief Функция, принимающая данные
 * из UART в буфер
 * 
 * \param[in,out] uart Указатель на дескриптор UART
 * \param[out] buf Указатель на буфер выходных данных
 * \return Количество байт, принятых из UART
 */
uint32_t uart_recvbuf(uartregs_t *uart, uint8_t *buf);

/**
 * \brief Обработчик прерываний UART
 * 
 * \param[in,out] uart Указатель на дескриптор UART
 * \param[out] buf_in Буфер на прием
 * \param[out] len_in Количество принятых байт
 * \param[in] buf_out Буфер на передачу
 * \param[in] len_out Длина буфера данных на передачу
 */
void uart_intrpt_handler(void *uart, uint8_t *buf_in, uint8_t *len_in, uint8_t *buf_out, uint8_t len_out);


#endif /* __UART_H__ */
