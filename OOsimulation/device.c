#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "device.h"

/*
 * Function: dev_get_name
 * ----------------------------
 *   Makes the copy data from "dev->name" array to "name" array.
 *
 *   dev: Concerning device. 
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
 *   dev: Concerning device. 
 *   name: array of char which data will be copied from. Must have strlen(name) between 0 and MAX_NAME_SIZE.
 *
 *   returns: Success of operation
 */
bool dev_set_name( device_t *dev, const char * name ) {
	if ( strlen(name) == 0 || strlen(name) > MAX_NAME_SIZE )	
		return false;
	memcpy(dev->name, name, MAX_NAME_SIZE);
	return true;
};

/*
 * Function: dev_get_battery
 * ----------------------------
 *   Get the battery remaining power percentage.
 *
 *   dev: Concerning device. 
 *
 *   returns: Battery power (between 0 and 100)
 */
uint8_t dev_get_battery( const device_t *dev ) {
	return dev->battery;
};

/*
 * Function: dev_set_battery
 * ----------------------------
 *   Set the battery remaining power percentage.
 *
 *   dev: Concerning device. 
 *	 battery: Value in percentage that will be set.
 *
 *   returns: Success of operation
 */
bool dev_set_battery( device_t *dev, uint8_t battery ) {
	if ( battery < 0 || battery > 100 )
		return false;
	
	dev->battery = battery;
	return true;
};

/*
 * Function: dev_get_status
 * ----------------------------
 *   Get the device status.
 *
 *   dev: Concerning device. 
 *
 *   returns: Battery status (CONNECTED, DISCONNECTED or UNKNOWN)
 */
status_t dev_get_status( const device_t *dev ) {
	return dev->status;
};

/*
 * Function: dev_set_status
 * ----------------------------
 *   Set the device status.
 *
 *   dev: Concerning device. 
 *   status: New status which device will be set to.
 *
 *   returns: Success of operation.
 */
bool dev_set_status( device_t *dev, status_t status ) {
	dev->status = status;
	return true;
};

/*
 * Function: dev_get_signal
 * ----------------------------
 *   Get the signal power.
 *
 *   dev: Concerning device. 
 *
 *   returns: Signal power between 0 and 255.
 */
uint8_t dev_get_signal( const device_t *dev ) {
	return dev->signal_strength;
};

/*
 * Function: dev_set_signal
 * ----------------------------
 *   Set the signal power.
 *
 *   dev: Concerning device. 
 *   signal_strength: Value that signal power will be set to. Must be between 0 and 255.
 *
 *   returns: Success of operation
 */
bool dev_set_signal( device_t *dev, uint8_t signal_strength ) {
	if ( signal_strength < 0 || signal_strength > 255 )
		return false;
	
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