#include "blink.h"

status_t cmd_on(uint32_t argc, char *argv[])
{
    if (argc >= 2) {
        for(int i=1; i<argc; i++) {
            uint8_t gpio_num = atoi(argv[i]);
            gpio_enable(gpio_num, GPIO_OUTPUT);
            gpio_write(gpio_num, true);
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
    if (argc >= 2) {
        for(int i=1; i<argc; i++) {
            uint8_t gpio_num = atoi(argv[i]);
            gpio_enable(gpio_num, GPIO_OUTPUT);
            gpio_write(gpio_num, true);
            printf("On %d\n", gpio_num);
            return OK;
        }
    } else {
        printf("[ERR] Miissing gpio number.\n");
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
    printf("[SYS] Type away while I take a 2 second nap (ie. let you test the UART HW FIFO\n");
    vTaskDelay(2000 / portTICK_PERIOD_MS);
    return OK;
}


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
            printf("cmd_index: %d\n", cmd_index);
            if ( strcmp(argv[0], invoker[cmd_index].cmd_string) == 0 )
                break;
        }

        // If not found, show help command
        if (cmd_index == NUM_OF_CMD)
            printf("[ERR] Unknown command %s, try 'help'\n", argv[0]);
        else
            cmd_status = (*invoker[cmd_index].receiver)(argc, argv);
    }

    /*
    if( cmd_status == OK )
        printf("[SYS] Command successful.\n");
    else if ( cmd_status == FAIL )
        printf("[SYS] Command failed\n");
    else
        printf("[SYS] Unknown command state");
    */
}
