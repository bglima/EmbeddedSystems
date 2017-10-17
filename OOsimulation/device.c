#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "device.h"

/*
 * Function: dev_get_name
 * ----------------------------
 *   Makes the copy data from "dev->name" array to "name" array.
 *
 *   dev: device which name is wanted to be known. 
 *   name: array of char to be filled with device name. Must have size of MAX_NAME_SIZE
 *
 *   returns: nothing
 */
void dev_get_name( const device_t * dev, char * name ) {
	memcpy(name, dev->name, MAX_NAME_SIZE);
};

/*
 * Function: dev_set_name
 * ----------------------------
 *   Set "dev->name" with "name" array data
 *
 *   dev: device which name is wanted to be set. 
 *   name: array of char which data will be copied from. Must have size of MAX_NAME_SIZE
 *
 *   returns: nothing
 */
bool dev_set_name( device_t *dev, const char * name ) {
	if ( strlen(name) == 0 || strlen(name) > MAX_NAME_SIZE )	
		return false;
	memcpy(dev->name, name, MAX_NAME_SIZE);
	return true;
};

uint8_t dev_get_battery( const device_t *dev ) {
	return dev->battery;
};

bool dev_set_battery( device_t *dev, uint8_t battery ) {
	if ( battery < 0 || battery > 100 )
		return false;
	
	dev->battery = battery;
	return true;
};

status_t dev_get_status( const device_t *dev ) {
	return dev->status;
};

bool dev_set_status( device_t *dev, status_t status ) {
	dev->status = status;
	return true;
};

uint8_t dev_get_signal( const device_t *dev ) {
	return dev->signal_strength;
};

bool dev_set_signal( device_t *dev, uint8_t signal_strength ) {
	dev->signal_strength = signal_strength;
	return true;
};

/* uint8_t * dev_get_data( const device_t *dev ) {
	return dev->data_buffer;
};

bool dev_set_data( device_t *dev, data_t * data_buffer ) {
	dev->data_buffer = data_buffer;
	return true;
}; */