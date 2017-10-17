#include<stdint.h>
#include<stdio.h>
#include "device.h"

int main(int argc, char *argv) {

	data_t data_input[MAX_DATA_SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
										1, 2, 3, 4, 5, 6, 7, 8, 9, 20,
										1, 2, 3, 4, 5, 6, 7, 8, 9, 30,
										1, 2, 3, 4, 5, 6, 7, 8, 9, 40,
										1, 2, 3, 4, 5, 6, 7, 8, 9, 50};
	data_t *data_out;

	dev_create_new(my_dev);
	dev_set_name(&my_dev, "MyDevice");
	dev_set_data(&my_dev, data_input);
	dev_set_battery(&my_dev, 100);
	dev_set_signal(&my_dev, 255);
	data_out = dev_get_data(&my_dev);
	dev_show(&my_dev);
	
	dev_create_new(my_other_dev);
	dev_show(&my_other_dev);
	
	return 0;
}