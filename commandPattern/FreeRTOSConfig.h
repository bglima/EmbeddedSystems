/* Terminal FreeRTOSConfig overrides.

   This is intended as an example of overriding some of the default FreeRTOSConfig settings,
   which are otherwise found in FreeRTOS/Source/include/FreeRTOSConfig.h
*/

/* The serial driver depends on counting semaphores */
#define configUSE_COUNTING_SEMAPHORES 1

/* We sleep a lot, so cooperative multitasking is fine. */
#define configUSE_PREEMPTION 0

/* Use the defaults for everything else */
#include_next<FreeRTOSConfig.h>

