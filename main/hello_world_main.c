#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "driver/uart.h"
#include "driver/gpio.h"


#define buffer_size 1024
#define TX_PIN 
#define RX_PIN 

static void loopback(void *arg){
    QueueHandle_t uart_queue;

    uart_driver_install(UART_NUM_1, buffer_size, buffer_size, 10, &uart_queue, 0);
    uart_config_t config = {
            .baud_rate = 115200,
            .data_bits = UART_DATA_8_BITS,
            .parity = UART_PARITY_DISABLE,
            .stop_bits = UART_STOP_BITS_1,
            .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
            .source_clk = UART_SCLK_DEFAULT
    };
    uart_param_config(UART_NUM_1, &config);
    uart_set_pin(UART_NUM_1, TX_PIN, RX_PIN, -1,-1 );
}

void app_main(void){

}
