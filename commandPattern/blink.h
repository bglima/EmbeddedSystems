#ifndef BLINK_HEADER
#define BLINK_HEADER

#include <stdint.h>
#include <sys/types.h>
#include <esp8266.h>
#include "espressif/esp_common.h"
#include "FreeRTOS.h"
#include "task.h"

#define MAX_ARGC (10)

typedef enum {
    OK,
    FAIL
} status_t;

typedef enum {
    CMD_ON,
    CMD_OFF,
    CMD_BLINK,
    CMD_SLEEP,
    CMD_HELP,
    NUM_OF_CMD
} __attribute__((__packed__)) command_t;

typedef status_t (*function_t)(uint32_t argc, char *argv[]);

typedef struct {
    char * cmd_string;
    function_t receiver;
    char * cmd_help;
} cmd_desc_t;

/*
 * Functions prototypes
 */
static status_t cmd_on(uint32_t argc, char *argv[]);
static status_t cmd_off(uint32_t argc, char *argv[]);
static status_t cmd_help(uint32_t argc, char *argv[]);
static status_t cmd_sleep(uint32_t argc, char *argv[]);
static status_t cmd_blink(uint32_t argc, char *argv[]);

void receiver_handle( char * cmd_line );
void blink_led_task(void *pvParameters);

/*
 *  Attributes
 */
static cmd_desc_t invoker[NUM_OF_CMD] = {
    {"on", &cmd_on, "  $on <gpio number> [ <gpio number>]+     Set gpio to 1\n"},
    {"off", &cmd_off, "  $off <gpio number> [ <gpio number>]+    Set gpio to 0\n"},
    {"blink", &cmd_blink, "  $blink <gpio number> <frequency>    Starts blining gpio\n"},
    {"sleep", &cmd_sleep, "  $sleep     Take a nap for two seconds\n"},
    {"help", &cmd_help, "  $help     Show all avaliable commands\n"}
};

static uint8_t blink_io = 2;    /* Internal led is GPIO = 2 */
static uint8_t blink_freq = 0;  /* Initialize with blink off */


#endif
