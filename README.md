# AXI UART Lite

Данный драйвер представляет из себя статическую библиотеку для baremetall-программ. Драйвер предоставляет API для управления IP-ядром <a href="https://docs.xilinx.com/v/u/en-US/axi_uartlite_ds741">AXI UART Lite v1.02a</a>.

### Заметки: 
- текущая версия драйвера не использует биты четности (C_USE_PARITY = 0)
- присутствует только одновременный сброс RX и TX FIFO
- прерывания всегда разрешены

### Требования
- glibc
- gcc
- make  
Установить необходимые программы можно командой: `sudo apt install build-essential`

### Сборка библиотеки драйвера
Открыть командную оболочку (shell) и выполнить указанные команды:  
```bash
git clone https://github.com/VasiliyMatlab/axi_uart_lite.git
cd axi_uart_lite/
make
```
Если драйвер предназначен для другой архитектуры (кросскомпиляция), то вместо последнего действия стоит выполнить: `make PREFIX=<your_target_arch>`. Например, компиляция под архитектуру ARM будет выглядеть следующим образом: `make PREFIX=arm-none-eabi-`.

### Использование
В результате сборки будет создана директория `lib`, где будет лежать статическая библиотека `libaxi_uart_lite.a`. Данную статическую библиотеку можно скопировать в свой проект и добавить флаг при линковке: `-laxi_uart_lite`.

### ToDo list:
- реализовать возможность включения/отключения прерываний
- внедрить механизм анализа бита четности (если возникла ошибка ParityError, то очистить байт FIFO)
- сделать отдельный сброс RX FIFO и TX FIFO
- пофиксить pdf, который генерит из LaTeX Doxygen

***
<p align="center"><a href="https://github.com/VasiliyMatlab"><img src="https://github.com/VasiliyMatlab.png" width="100" alt="VasiliyMatlab" /></a></p>
<p align="center"><a href="https://github.com/VasiliyMatlab" style="color: #000000">VasiliyMatlab</a></p>
