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

#define cb_create_new(name) cb_t name = {  0, 0, 0, 0, 0 }

int main(int argc, const char* argv[] ) {
    element_t a[80];

    cb_create_new(my_cb);
	cb_set_memory(&my_cb, a, sizeof(a));
	
	printf("Memory size of CB: %d\n", sizeof(a));
	printf("Length of CB: %d\n", cb_get_length(&my_cb) );
	printf("Is empty?: %d\n", cb_is_empty(&my_cb) );
	
	for( int i = 0; i < 85; ++i ) {
		cb_write(&my_cb, i+1);
		printf("Element at index %d is %d \n", i, a[i]);
	}
	
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
	++cb->length;
	return true;
}

bool cb_read(cb_t *cb, element_t * data) {
	if (cb->length == 0)
		return false;
	*data = cb->buffer[cb->read];
	if ( ++cb->read == cb->size )
		cb->read = 0;
	--cb->length;
	return false;
}


