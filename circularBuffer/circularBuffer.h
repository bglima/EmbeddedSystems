#ifndef CIRCULARBUFFER_H
#define CIRCULARBUFFER_H

#define cb_create_new(name) cb_t name = {  0, 0, 0, 0, 0 }

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

#endif