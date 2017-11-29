/* Serial terminal example
 * UART RX is interrupt driven
 * Implements a simple GPIO terminal for setting and clearing GPIOs
 *
 * This sample code is in the public domain.
 */

#include <stdint.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <esp8266.h>
#include <esp/uart.h>
#include <stdio.h>
#include "FreeRTOS.h"
#include "espressif/esp_common.h"
#include "task.h"
#include "queue.h"

#include "blink.h"

void keyboard_monitor_task(void *pvParameters)
{
    QueueHandle_t *rawCommandQ = ( QueueHandle_t *) pvParameters;
    char ch;
    char cmd[81];   // Max string size is 80. Last char must be \n or \r
    int i = 0;
    printf("\n\n\nWelcome to gpiomon. Type 'help<enter>' for, well, help\n");
    printf("%% ");
    fflush(stdout); // stdout is line buffered
    while(1) {
        if (read(0, (void*)&ch, 1)) { // 0 is stdin
            printf("%c", ch);
            fflush(stdout);
            if (ch == '\n' || ch == '\r') {
                cmd[i] = 0;
                i = 0;
                printf("\n");

                // Allow handler to execute its
                receiver_handle((char*) cmd);   // Handle cmd line that was read

                printf("%% ");
                fflush(stdout);
            } else {
                if (i < sizeof(cmd)) cmd[i++] = ch;
            }
        } else {
            printf("You will never see this print as read(...) is blocking\n");
        }

    }
}

void user_init(void)
{
    uart_set_baud(0, 115200);
    printf("SDK version:%s\n", sdk_system_get_sdk_version());
    xTaskCreate(keyboard_monitor_task, "keyboard_monitor_task", 256, NULL, 1, NULL);
    xTaskCreate(blink_led_task, "blink_led_task", 256, NULL, 2, NULL);
}
