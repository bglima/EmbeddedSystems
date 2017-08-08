#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum { false, true } bool;
typedef uint8_t element_t;

typedef struct {
    element_t *buffer;	// Block of memory
	uint8_t size;		// Total size
	uint8_t length;		// Space already filled
    uint8_t read;		// Holds current read position: 0 to (size-1)
    uint8_t write;		// Holds current write position: 0 to (size-1)
} cb_t;

uint8_t cb_get_length( const cb_t *cb );
uint8_t cb_get_size ( const cb_t *cb );
void cb_set_memory( cb_t *cb, element_t * memory, const uint8_t size );
bool cb_is_empty( const cb_t *cb );
bool cb_write( cb_t *cb, const element_t data );
bool cb_read( cb_t *cb, element_t * data );
void cb_print_data( const cb_t *cb );

#define cb_create_new(name) cb_t name = {  0, 0, 0, 0, 0 }

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

uint8_t cb_get_length (const cb_t *cb) {
    return cb->length;
}

uint8_t cb_get_size (const cb_t *cb) {
    return cb->size;
}

void cb_set_memory (cb_t *cb, element_t * memory, const uint8_t size) {
	cb->buffer = memory;
	cb->size = size;
	cb->length = 0;
	cb->read = 0;
	cb->write = 0;
}

bool cb_is_empty ( const cb_t *cb ) {
	return cb->length == 0;
}

bool cb_write(cb_t *cb, const element_t data) {
	if ( cb->length == cb->size )
		return false;
	cb->buffer[cb->write] = data;
	if ( ++cb->write == cb->size )
		cb->write = 0;
	cb->length = cb->length + 1;
	return true;
}

bool cb_read(cb_t *cb, element_t * data) {
	if (cb->length == 0)
		return false;
	*data = cb->buffer[cb->read];
	if ( ++cb->read == cb->size )
		cb->read = 0;
	cb->length = cb->length - 1;
	return true;
}

void cb_print_data( const cb_t *cb ) {
	if( cb_is_empty( cb ) ) {
		printf("Buffer is empty.\n");
		return;
	}
	printf("Buffer has the following elements: \n");
	int index = cb->read;
	
	do {
		printf("%d\n", cb->buffer[index]);
		++index;
		if(index == cb->size)
			index = 0;
	} while ( index != cb->write );
}




