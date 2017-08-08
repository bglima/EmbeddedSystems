#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "circularBuffer.h"

int main(int argc, const char* argv[] ) {
	printf("V. %d.%d.%d\n", MAJOR, MINOR, BUILD);
    srand(time(NULL)); 
	
	element_t memory[80] = {0};
	int	integers[20] = {-1};
	
    cb_create_new(my_cb);
	cb_set_memory(&my_cb, memory, sizeof(memory));
	
	// Trying to write 5 x 20 = 100 bytes at "memory" array.
	// Only 80 will be written.
	for( uint8_t i = 1; i <= 80; ++i ) {
		uint8_t data = rand();
		if ( !cb_write(&my_cb, rand()) ) 
			printf("Write #%d FAIL! Data %x lost. Buffer full.\n", i, data);
		else
			printf("Write #%d OK! Data %x on buffer.\n", i, data);
		usleep(100000); // 100 ms = 100 * 10^3 us	
	}
	
	
	// Copying values to the integers array
	memcpy( integers, memory, sizeof(integers) );
	
	// Show at screen the 20 integers in the integers array:
    printf("\nDisplaying integers array:\n");
	for( uint8_t i = 0; i < 20; ++i )
		printf("Data at index %d is %d. HEX value is: %x.\n", i, integers[i], integers[i]);
		
	return 0;
}
