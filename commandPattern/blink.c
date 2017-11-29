#include "blink.h"

void cmd_on(uint32_t argc, char *argv[])
{
    if (argc >= 2) {
        for(int i=1; i<argc; i++) {
            uint8_t gpio_num = atoi(argv[i]);
            gpio_enable(gpio_num, GPIO_OUTPUT);
            gpio_write(gpio_num, true);
            printf("On %d\n", gpio_num);
        }
    } else {
        printf("Error: missing gpio number.\n");
    }
}

void cmd_blink(uint32_t argc, char *argv[])
{
    if (argc >= 2) {
        for(int i=1; i<argc; i++) {
            uint8_t gpio_num = atoi(argv[i]);
            gpio_enable(gpio_num, GPIO_OUTPUT);
            gpio_write(gpio_num, true);
            printf("On %d\n", gpio_num);
        }
    } else {
        printf("Error: missing gpio number.\n");
    }
}

void cmd_off(uint32_t argc, char *argv[])
{
    if (argc >= 2) {
        for(int i=1; i<argc; i++) {
            uint8_t gpio_num = atoi(argv[i]);
            gpio_enable(gpio_num, GPIO_OUTPUT);
            gpio_write(gpio_num, false);
            printf("Off %d\n", gpio_num);
        }
    } else {
        printf("Error: missing gpio number.\n");
    }
}


void cmd_help(uint32_t argc, char *argv[])
{
    printf(" [SYS] List of avaliable commands: \n");
    for(int i = 0; i < NUM_OF_CMD; ++i)
        printf("%s", invoker[i].cmd_help);
}

void cmd_sleep(uint32_t argc, char *argv[])
{
    printf("Type away while I take a 2 second nap (ie. let you test the UART HW FIFO\n");
    vTaskDelay(2000 / portTICK_PERIOD_MS);
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

    if (strlen(argv[0]) > 0) {
        if (strcmp(argv[0], "help") == 0) cmd_help(argc, argv);
        else if (strcmp(argv[0], "on") == 0) cmd_on(argc, argv);
        else if (strcmp(argv[0], "off") == 0) cmd_off(argc, argv);
        else if (strcmp(argv[0], "sleep") == 0) cmd_sleep(argc, argv);
        else printf("Unknown command %s, try 'help'\n", argv[0]);
    }
}
