#include<stdint.h>
#include<stdio.h>
#include "device.h"

int main(int argc, char *argv) {

	data_t data_input[MAX_DATA_SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
										1, 2, 3, 4, 5, 6, 7, 8, 9, 20,
										1, 2, 3, 4, 5, 6, 7, 8, 9, 30,
										1, 2, 3, 4, 5, 6, 7, 8, 9, 40,
										1, 2, 3, 4, 5, 6, 7, 8, 9, 50};

	// Create and set data from first device
	dev_create_new(my_dev);
	dev_set_name(&my_dev, "MyDevice");
	dev_set_status(&my_dev, CONNECTED);
	dev_set_battery(&my_dev, 100);
	dev_set_signal(&my_dev, 255);
	dev_set_data(&my_dev, data_input);
	// Show device data
	dev_show(&my_dev);
	
	// Create another device 
	dev_create_new(my_other_dev);
	// Copy all data from first to second device
	dev_copy(&my_other_dev, &my_dev);
	// Then change its name and status
	dev_set_name(&my_other_dev, "MyNewDevice");
	dev_set_status(&my_other_dev, DISCONNECTED);
	dev_show(&my_other_dev);
	
	// Creating last device and stringfying it (in empty state)
	char my_string[200];
	dev_create_new(my_last_dev);
	dev_show(&my_last_dev);
	dev_to_string(&my_last_dev, my_string);
	printf("\nResult from stringfying before filling data: \n%s", my_string);
	
	// Now filling it with some data and stringfying again	
	dev_set_name(&my_last_dev, "MyLastDevice");
	dev_set_status(&my_last_dev, CONNECTED);
	dev_set_battery(&my_last_dev, 79);
	dev_set_signal(&my_last_dev, 127);
	dev_set_data(&my_last_dev, data_input);
	dev_to_string(&my_last_dev, my_string);
	printf("\nResult from stringfying after it: \n%s", my_string);
	
	return 0;
}