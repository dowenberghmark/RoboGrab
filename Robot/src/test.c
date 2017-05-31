#include <stdio.h>
#include "robolib.h"

int main()
{
	init_robot();
	move_forward();
	move_right();
	move_backward();
	move_left();
	uninit_robot();
	return 0;
}