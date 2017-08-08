#include <stdint.h>
#include <stdio.h>
#include "circularBuffer.h"

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




