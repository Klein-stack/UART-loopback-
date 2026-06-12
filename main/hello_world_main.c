#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "driver/uart.h"
#include "driver/gpio.h"
#include <string.h>


#define buffer_size 1024
#define TX_PIN 21
#define RX_PIN 20
#define TASK_STACK_SIZE 4096

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

    char send_data[] = "Miles to go before I sleep!";
    uart_flush(UART_NUM_1);
    uart_write_bytes(UART_NUM_1, send_data, strlen(send_data));
    
    uint8_t data[128];
    int length = 0;
    uart_get_buffered_data_len(UART_NUM_1, (size_t*)&length);
    length = uart_read_bytes(UART_NUM_1, data, length, 100);
    printf("Received data: %s",data);



}
    
void app_main(void){
    xTaskCreate(loopback, "Loopback_task", TASK_STACK_SIZE, NULL, 1, NULL);
}
