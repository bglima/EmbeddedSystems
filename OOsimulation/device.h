#ifndef CIRCULARBUFFER_H
#define CIRCULARBUFFER_H

#define dev_create_new(name) device_t name = {  0, 0, 0, 0, 0 }
#define MAX_NAME_SIZE 20

typedef uint8_t data_t;
typedef enum { false, true } bool;

typedef enum {
	CONNECTED, 
	DISCONECTED,
	UNKOWN
} status_t;

typedef struct {
	char name[MAX_NAME_SIZE];
	uint8_t battery;
	status_t status;
	uint8_t signal_strength;
	data_t * data_buffer	;
	uint8_t data_buffer_size;
} device_t;

void dev_get_name( const device_t *dev, char * name );
bool dev_set_name( device_t *dev, const char * name );

uint8_t dev_get_battery( const device_t *dev );
bool dev_set_battery( device_t *dev, uint8_t battery );

status_t dev_get_status( const device_t *dev );
bool dev_set_status( device_t *dev, status_t status );

uint8_t dev_get_signal( const device_t *dev );
bool dev_set_signal( device_t *dev, uint8_t signal_strength );

data_t * dev_get_data( const device_t *dev );
bool dev_set_data( device_t *dev, data_t * data_buffer, uint8_t data_buffer_size );

#endif