#include <stdint.h>
#include <stdio.h>
#include "circularBuffer.h"

int main(int argc, const char* argv[] ) {
    element_t a[80] = {0};

    cb_create_new(my_cb);
	cb_set_memory(&my_cb, a, sizeof(a));
	
	printf("Memory size of CB: %d\n", sizeof(a));
	
	// Testing writing 80 numbers
	for( int i = 0; i < 90; ++i ) {
		if ( cb_write(&my_cb, i+1) )
			printf("Write#%d of element %d \n", i+1);
		else
			printf("Buffer is full. Cannot write anymore :(\n");
	}
	
	// Print current buffer state
	cb_print_data( &my_cb );

	// Freeing some space at buffer. Read 15 numbers.
	for( int i = 0; i < 20; ++i ) {
		uint8_t data;
		if ( cb_read(&my_cb, &data) )
			printf("Read %d from buffer \n", data);
		else
			printf("Buffer is empty. Cannot read anymore :(\n");
	}

	// Print current buffer state
	cb_print_data( &my_cb );
	
	// Trying to write 30 more elements
	for( int i = 0; i < 30; ++i ) {
		if ( cb_write(&my_cb, i+81) )
			printf("Write#%d of element %d \n", i+81);
		else
			printf("Buffer is full. Cannot write anymore :(\n");
	}
	
	// Print current buffer state
	cb_print_data( &my_cb );
	
    return 0;
}
