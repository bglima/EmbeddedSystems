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
 *   name: Array of char to be filled with device name. Must have size of MAX_NAME_SIZE
 *
 *   returns: nothing
 */
void dev_get_name( const device_t * dev, char * name ) {
	// If name is null, copy UNNAMED as output
	if (!strcmp(dev->name,"")) {
		memcpy(name, unnamed, MAX_NAME_SIZE);
		return;
	}
	// Otherwise, copy dev->name
	memcpy(name, dev->name, MAX_NAME_SIZE);
};

/*
 * Function: dev_set_name
 * ----------------------------
 *   Set "dev->name" with "name" array data
 *
 *   dev: Concerning device. 
 *   name: Array of char which data will be copied from. Must have strlen(name) between 0 and MAX_NAME_SIZE.
 *
 *   returns: Success of operation
 */
bool dev_set_name( device_t *dev, const char * name ) {
	if ( sizeof(name) == 0 || sizeof(name) > MAX_NAME_SIZE )	
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

/*
 * Function: dev_get_data
 * ----------------------------
 *   Get the pointer to device's data_buffer array.
 *
 *   dev: Concerning device. 
 *
 *   returns: Pointer to device data_buffer.
 */
data_t * dev_get_data( const device_t *dev ) {
	return (data_t *) &dev->data_buffer;
};

/*
 * Function: dev_set_data
 * ----------------------------
 *   Copy data to device data_buffer array.
 *
 *   dev: Concerning device. 
 *   data_buffer: Array containing the data which be copied from.
 *
 *   returns: Success of operation
 */
bool dev_set_data( device_t * dev, data_t * data_buffer ) {
	memcpy(dev->data_buffer, data_buffer, MAX_DATA_SIZE);
	return true;
};

/*
 * Function: dev_show
 * ----------------------------
 *   Show all data from device in screen.
 *
 *   dev: Concerning device. 
 *
 *   returns: Nothing
 */
void dev_show( const device_t * dev ) { 
	printf("\nInfo about %s...\n", strcmp(dev->name,"") ? dev->name : unnamed);
	printf("============================\n");
	printf("Battery in %%....: %u\n", dev->battery);
	printf("Status..........: %s\n", status[dev->status]);
	printf("Signal Strength.: %d\n", dev->signal_strength);
	printf("Data buffer follows below:");
	uint16_t i;
	for(i = 0; i < MAX_DATA_SIZE; ++i ) {
		if ( i%10 == 0 ) printf("\n");
		printf("%d ", dev->data_buffer[i]);
	}
	printf("\n============================\n");
};

/*
 * Function: dev_copy
 * ----------------------------
 *   Copy all data from one device to another
 *
 *   dev_to: Destination device
 *	 dev_from: Source device
 *
 *   returns: Nothing
 */
void dev_copy( device_t *dev_to, const device_t *dev_from ) {
	memcpy(dev_to, dev_from, sizeof(device_t));
};

/*
 * Function: dev_to_string
 * ----------------------------
 *   Copy all device data to a passed string.
 *
 *   dev: Concerning device
 *	 string: String in which data will be copied to. Must have size equal to 200.
 *
 *   returns: Nothing
 */
void dev_to_string( const device_t *dev, char * string ) {
	char buffer[200];
	uint8_t len;
	// Name
	if (!strcmp(dev->name,"")) {
		len = sprintf(buffer, "%s, ", unnamed);
	} else {
		len = len = sprintf(buffer, "%s, ", dev->name);
	}
	// Battery
	len += sprintf(buffer + len, "%u, ", dev->battery);
	len += sprintf(buffer + len, "%s, ", status[dev->status]);
	len += sprintf(buffer + len, "%d, ", dev->signal_strength);
	uint16_t i;
	for(i = 0; i < MAX_DATA_SIZE; ++i ) {
		len += sprintf(buffer + len, "%d ", dev->data_buffer[i]);
	}
	len += sprintf(buffer + len, "\n");
	memcpy(string, buffer, sizeof(buffer));
};



