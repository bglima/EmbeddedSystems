#include<stdint.h>
#include<stdio.h>
#include "device.h"

int main(int argc, char *argv) {

	char dev_name[MAX_NAME_SIZE] = "DevBG";
	char temp_name[MAX_NAME_SIZE] = "";
	
	dev_create_new(my_dev);
	if ( dev_set_name(&my_dev, dev_name) ) {
		printf("Name set successfully.\n");
	} else {
		printf("Error: empty names or larger than %d are not valid.\n", MAX_NAME_SIZE);
	};
	dev_get_name(&my_dev, temp_name);
	printf("Name got from device: %s\n", temp_name);
	
	return 0;
}