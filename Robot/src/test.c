#include <stdio.h>
#include "robolib.h"

int main()
{
	init_robot();

	int val = sensor_get_color_value();
	printf("value: %d\n", val);
	move_forward();
	move_left();
	move_forward();
	move_backward();
	move_left();
	move_forward();

	uninit_robot();
	return 0;
}