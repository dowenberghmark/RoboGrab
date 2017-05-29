#include <stdio.h>
#include "brick.h"
#include "robolib.h"

// PRIVATE ====================================================================
int init_motor()
{
	if(tacho_is_plugged(MOTOR_LEFT_PORT | MOTOR_RIGHT_PORT, LEGO_EV3_L_MOTOR)) 
	{
		tacho_set_stop_action(MOTOR_LEFT_PORT | MOTOR_RIGHT_PORT, TACHO_BRAKE);
		return 1;
	}
	return 0;
}

int init_color_sensor()
{
	if(sensor_is_plugged(SENSOR_COLOR_PORT, LEGO_EV3_COLOR))
	{
		color_set_mode_col_reflect(SENSOR_COLOR_PORT);
		return 1;
	}
	return 0;
}

int sensor_color_value()
{
	return sensor_get_value(0, SENSOR_COLOR_PORT, 0);
}

void motor_set_speed(POOL_T pool, int speed)
{
	tacho_set_duty_cycle_sp(pool, speed);
}

void motor_start()
{
	tacho_run_direct(MOTOR_LEFT_PORT | MOTOR_RIGHT_PORT);
}

void motor_wait(int duration)
{
	sleep_ms(duration);
}

void motor_stop()
{
	tacho_stop(MOTOR_LEFT_PORT | MOTOR_RIGHT_PORT);
}

// PUBLIC ====================================================================
int init_robot()
{
	brick_init();
	init_motor();
	init_color_sensor();
	return 0;
}

void uninit_robot()
{
	brick_uninit();
}

void move_forward()
{
	motor_set_speed(MOTOR_LEFT_PORT | MOTOR_RIGHT_PORT, -MOTOR_SPEED_NORMAL);
	motor_start();
	motor_wait(MOTOR_MOVE_DURATION);
	motor_stop();
}

void move_backward()
{
	motor_set_speed(MOTOR_LEFT_PORT | MOTOR_RIGHT_PORT, MOTOR_SPEED_NORMAL);
	motor_start();
	motor_wait(MOTOR_MOVE_DURATION);
	motor_stop();
}

void move_right()
{
	motor_set_speed(MOTOR_LEFT_PORT, MOTOR_SPEED_SLOW);
	motor_set_speed(MOTOR_RIGHT_PORT, MOTOR_SPEED_NORMAL);
	motor_start();
	motor_wait(MOTOR_TURN_DURATION);
	motor_stop();
}

void move_left()
{
	motor_set_speed(MOTOR_LEFT_PORT, MOTOR_SPEED_NORMAL);
	motor_set_speed(MOTOR_RIGHT_PORT, MOTOR_SPEED_SLOW);
	motor_start();
	motor_wait(MOTOR_TURN_DURATION);
	motor_stop();
}