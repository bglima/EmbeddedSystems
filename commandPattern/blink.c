#include "blink.h"

/*
 * Task responsible for blinking the blink_io pin at blink_freq frequency.
 */
void blink_led_task(void *pvParameters)
{
    while( 1 ) {
        if ( blink_freq > 0 ) {
            gpio_toggle(blink_io);
            vTaskDelay( (1000 / blink_freq) / portTICK_PERIOD_MS);
         } else {
            vTaskDelay( 1000 / portTICK_PERIOD_MS);
        }
    }
}

/*
 * Responsible for splitting keyboard read line into argc, argv pattern
 */
void receiver_handle( char *cmd )
{
    char *argv[MAX_ARGC];
    int argc = 1;
    char *temp, *rover;
    memset((void*) argv, 0, sizeof(argv));
    argv[0] = cmd;
    rover = cmd;
    // Split string "<command> <argument 1> <argument 2>  ...  <argument N>"
    // into argv, argc style
    while(argc < MAX_ARGC && (temp = strstr(rover, " "))) {
        rover = &(temp[1]);
        argv[argc++] = rover;
        *temp = 0;
    }

    status_t cmd_status = FAIL;
    if (strlen(argv[0]) > 0) {
        // Search for correct command
        int cmd_index;
        for( cmd_index = 0; cmd_index < NUM_OF_CMD; ++cmd_index ) {
            if ( strcmp(argv[0], invoker[cmd_index].cmd_string) == 0 )
                break;
        }

        // If not found, show help command
        if (cmd_index == NUM_OF_CMD)
            printf("[ERR] Unknown command %s, try 'help'\n", argv[0]);
        else
            cmd_status = (*invoker[cmd_index].receiver)(argc, argv);
    }
    if( cmd_status == OK )
        printf("[SYS] Command successful.\n");
    else if ( cmd_status == FAIL )
        printf("[SYS] Command failed\n");
    else
        printf("[SYS] Unknown command state");
}

/*
 *
 * Imlmementation of possible commands declared .h headers
 *
 */
status_t cmd_on(uint32_t argc, char *argv[])
{
    if (argc >= 2) {
        for(int i=1; i<argc; i++) {
            uint8_t gpio_num = atoi(argv[i]);
            gpio_enable(gpio_num, GPIO_OUTPUT);
            gpio_write(gpio_num, true);
            if ( blink_io == gpio_num )
                blink_freq = 0;
            printf("[SYS] On %d\n", gpio_num);
            return OK;
        }
    } else {
        printf("[ERR] Missing gpio number.\n");
        return FAIL;
    }
}

status_t cmd_blink(uint32_t argc, char *argv[])
{
    if (argc >= 3) {
        blink_io = atoi(argv[1]);
        blink_freq = atoi(argv[2]);
        gpio_enable(blink_io, GPIO_OUTPUT);
        gpio_toggle(blink_io);
        printf("Blinking %d\n", blink_io);
        return OK;
    } else {
        printf("[ERR] Miissing frequency (Hz) and/or gpio number.\n");
        return FAIL;
    }
}

status_t cmd_off(uint32_t argc, char *argv[])
{
    if (argc >= 2) {
        for(int i=1; i<argc; i++) {
            uint8_t gpio_num = atoi(argv[i]);
            gpio_enable(gpio_num, GPIO_OUTPUT);
            gpio_write(gpio_num, false);
            if ( blink_io == gpio_num )
                blink_freq = 0;
            printf("[SYS] Off %d\n", gpio_num);
            return OK;
        }
    } else {
        printf("[SYS] Missing gpio number.\n");
        return FAIL;
    }
}

status_t cmd_help(uint32_t argc, char *argv[])
{
    printf("[SYS] List of avaliable commands: \n");
    for(int i = 0; i < NUM_OF_CMD; ++i)
        printf("%s", invoker[i].cmd_help);
    printf("\n\n");
    return OK;
}

status_t cmd_sleep(uint32_t argc, char *argv[])
{
    printf("[SYS] I'll sleep 2 seconds. Let's test UART HW FIFO\n");
    vTaskDelay(2000 / portTICK_PERIOD_MS);
    return OK;
}



