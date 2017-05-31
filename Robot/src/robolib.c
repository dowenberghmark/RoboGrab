#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "brick.h"
#include "robolib.h"

POOL_T MOTOR_LEFT_PORT;
POOL_T MOTOR_RIGHT_PORT; 
POOL_T MOTOR_LIFT_PORT; 
POOL_T SENSOR_COLOR_PORT;
POOL_T SENSOR_ULTRASONIC_PORT;

int MOTOR_SPEED;
int MOTOR_MOVE_DURATION;
int MOTOR_TURN_DURATION;
int MOTOR_ALIGN_TRY;
int MOTOR_LAST_ALIGN_TRY_DURATION;
int SENSOR_COLOR_THRESHOLD_BLACK;
int SENSOR_COLOR_THRESHOLD_RED;
int	MOTOR_LIFT_DURATION;
int SENSOR_ULTRASONIC_TOUCH_DIS;
int MOTOR_ALIGN_PATH_TURN_DURATION;

int prev_align_dir = 0;
int prev_color_value = 0;
bool is_on_node = false;
bool carry_package = false;
bool reach_dropzone = false;

// PRIVATE ====================================================================
POOL_T config_get_port(char *value)
{
	if(strcmp(value, "OUTA") == 0)
	{
		return OUTA;
	}
	else if(strcmp(value, "OUTB") == 0)
	{
		return OUTB;
	}
	else if(strcmp(value, "OUTC") == 0)
	{
		return OUTC;
	}
	else if(strcmp(value, "OUTD") == 0)
	{
		return OUTD;
	}
	else if(strcmp(value, "IN1") == 0)
	{
		return IN1;
	}
	else if(strcmp(value, "IN2") == 0)
	{
		return IN2;
	}
	else if(strcmp(value, "IN3") == 0)
	{
		return IN3;
	}
	else if(strcmp(value, "IN4") == 0)
	{
		return IN4;
	}
}

// For simplicity, just else if. Recommend a table though
bool read_config()
{
	FILE* file;
	if(file = fopen("../config/robot.conf", "r"))
	{
		char line[80];
		while (fgets(line, sizeof(line), file)) {
			char key[30];
			char value[10];

			sscanf(line, "%s %s", key, value);

			if(strcmp(key, "MOTOR_LEFT_PORT") == 0)
			{
				MOTOR_LEFT_PORT = config_get_port(value);
			}
			else if(strcmp(key, "MOTOR_RIGHT_PORT") == 0)
			{
				MOTOR_RIGHT_PORT = config_get_port(value);
			}
			else if(strcmp(key, "MOTOR_LIFT_PORT") == 0)
			{
				MOTOR_LIFT_PORT = config_get_port(value);
			}
			else if(strcmp(key, "SENSOR_COLOR_PORT") == 0)
			{
				SENSOR_COLOR_PORT = config_get_port(value);
			}
			else if(strcmp(key, "SENSOR_ULTRASONIC_PORT") == 0)
			{
				SENSOR_ULTRASONIC_PORT = config_get_port(value);
			}
			else if(strcmp(key, "MOTOR_SPEED") == 0)
			{
				MOTOR_SPEED = atoi(value);
			}
			else if(strcmp(key, "MOTOR_MOVE_DURATION") == 0)
			{
				MOTOR_MOVE_DURATION = atoi(value);
			}
			else if(strcmp(key, "MOTOR_TURN_DURATION") == 0)
			{
				MOTOR_TURN_DURATION = atoi(value);
			}
			else if(strcmp(key, "MOTOR_ALIGN_TRY") == 0)
			{
				MOTOR_ALIGN_TRY = atoi(value);
			}
			else if(strcmp(key, "MOTOR_LAST_ALIGN_TRY_DURATION") == 0)
			{
				MOTOR_LAST_ALIGN_TRY_DURATION = atoi(value);
			}
			else if(strcmp(key, "SENSOR_COLOR_THRESHOLD_BLACK") == 0)
			{
				SENSOR_COLOR_THRESHOLD_BLACK = atoi(value);
			}
			else if(strcmp(key, "SENSOR_COLOR_THRESHOLD_RED") == 0)
			{
				SENSOR_COLOR_THRESHOLD_RED = atoi(value);
			}
			else if(strcmp(key, "MOTOR_LIFT_DURATION") == 0)
			{
				MOTOR_LIFT_DURATION = atoi(value);
			}
			else if(strcmp(key, "SENSOR_ULTRASONIC_TOUCH_DIS") == 0)
			{
				SENSOR_ULTRASONIC_TOUCH_DIS = atoi(value);
			}
			else if(strcmp(key, "MOTOR_ALIGN_PATH_TURN_DURATION") == 0)
			{
				MOTOR_ALIGN_PATH_TURN_DURATION = atoi(value);
			}
		}

		fclose(file);
		return true;
	}

	printf("Cannot open config file. Please check config/robot.conf\n");
	return false;
}

bool init_motor()
{
	if(tacho_is_plugged(MOTOR_LEFT_PORT | MOTOR_RIGHT_PORT, LEGO_EV3_L_MOTOR)) 
	{
		tacho_set_stop_action(MOTOR_LEFT_PORT | MOTOR_RIGHT_PORT, TACHO_BRAKE);
		return true;
	}
	return false;
}

bool init_color_sensor()
{
	if(sensor_is_plugged(SENSOR_COLOR_PORT, LEGO_EV3_COLOR))
	{
		color_set_mode_col_reflect(SENSOR_COLOR_PORT);
		return true;
	}
	return false;
}

bool init_ultrasonic_sensor()
{
	if(sensor_is_plugged(SENSOR_ULTRASONIC_PORT, LEGO_EV3_US))
	{
		us_set_mode_us_dist_cm(SENSOR_ULTRASONIC_PORT);
		return true;
	}
	return false;
}

bool init_motor_lift()
{
	if(sensor_is_plugged(MOTOR_LIFT_PORT, LEGO_EV3_L_MOTOR))
	{
		tacho_set_stop_action(MOTOR_LIFT_PORT, TACHO_BRAKE);
		return true;
	}
	return false;
}

bool sensor_touch_pressed()
{
	return sensor_get_value(0, SENSOR_ULTRASONIC_PORT, 0) < SENSOR_ULTRASONIC_TOUCH_DIS;
}

int sensor_get_color_value()
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

void robot_wait(int duration)
{
	sleep_ms(duration);
}

void motor_stop()
{
	tacho_stop(MOTOR_LEFT_PORT | MOTOR_RIGHT_PORT);
}

void motor_lift_start()
{
	tacho_run_direct(MOTOR_LIFT_PORT);
}

void motor_lift_stop()
{
	tacho_stop(MOTOR_LIFT_PORT);
}

void motor_lift_up()
{
	motor_set_speed(MOTOR_LIFT_PORT, -MOTOR_SPEED);
	motor_lift_start();
	robot_wait(MOTOR_LIFT_DURATION);
	motor_lift_stop();
}

void motor_lift_down()
{
	motor_set_speed(MOTOR_LIFT_PORT, MOTOR_SPEED);
	motor_lift_start();
	robot_wait(MOTOR_LIFT_DURATION);
	motor_lift_stop();
}

void motor_align_path(int color)
{
	if(color >= prev_color_value)
	{
		prev_align_dir = 1 - prev_align_dir;
	}

	printf("prevcolor: %d dir: %d\n", prev_color_value, prev_align_dir);

	if(prev_align_dir == 0)
	{
		// right
		motor_set_speed(MOTOR_LEFT_PORT, -MOTOR_SPEED);
		motor_set_speed(MOTOR_RIGHT_PORT, MOTOR_SPEED);
	}
	else
	{
		// left
		motor_set_speed(MOTOR_LEFT_PORT, MOTOR_SPEED);
		motor_set_speed(MOTOR_RIGHT_PORT, -MOTOR_SPEED);
	}

	robot_wait(MOTOR_ALIGN_PATH_TURN_DURATION);
	motor_set_speed(MOTOR_LEFT_PORT | MOTOR_RIGHT_PORT, -MOTOR_SPEED);
	robot_wait(MOTOR_LAST_ALIGN_TRY_DURATION);
}

bool sensor_color_on_node(int value)
{
	return value >= (SENSOR_COLOR_THRESHOLD_RED - 2) && value <= SENSOR_COLOR_THRESHOLD_RED;
}

bool sensor_color_on_path(int value)
{
	return value <= SENSOR_COLOR_THRESHOLD_BLACK;
}

bool sensor_color_on_wrong_path(int value)
{
	return value > SENSOR_COLOR_THRESHOLD_RED || (value > SENSOR_COLOR_THRESHOLD_BLACK && value < (SENSOR_COLOR_THRESHOLD_RED - 2));
}

// PUBLIC ====================================================================
int init_robot()
{
	read_config();
	brick_init();
	init_motor();
	init_color_sensor();
	init_ultrasonic_sensor();
	init_motor_lift();
	return 0;
}

void uninit_robot()
{
	brick_uninit();
}

void move_forward()
{
	motor_set_speed(MOTOR_LEFT_PORT | MOTOR_RIGHT_PORT, -MOTOR_SPEED);
	motor_start();
	int align_try = 0;
	int color_val = sensor_get_color_value();

	while(1)
	{
		if(carry_package == false && sensor_touch_pressed())
		{
			printf("Touch package\n");
			motor_lift_down();
			carry_package = true;
			break;
		}

		prev_color_value = color_val;
		color_val = sensor_get_color_value();
		printf("color value: %d\n", color_val);
		printf("dis %d\n", sensor_get_value(0, SENSOR_ULTRASONIC_PORT, 0));

		if(sensor_color_on_wrong_path(color_val)){
			is_on_node = false;
			motor_align_path(color_val);

			align_try++;

			if(align_try > MOTOR_ALIGN_TRY)
			{
				motor_set_speed(MOTOR_LEFT_PORT | MOTOR_RIGHT_PORT, MOTOR_SPEED);
				robot_wait(MOTOR_LAST_ALIGN_TRY_DURATION);
				printf("Last try\n");
				break;
			}
		}
		else if(sensor_color_on_node(color_val))
		{
			if(is_on_node == false){
				is_on_node = true;
				printf("On Node\n");
				break;
			}

			motor_set_speed(MOTOR_LEFT_PORT | MOTOR_RIGHT_PORT, -MOTOR_SPEED);
			robot_wait(MOTOR_MOVE_DURATION);
		}
		else if(sensor_color_on_path(color_val)){
			if(align_try > 0)
			{
				motor_set_speed(MOTOR_LEFT_PORT | MOTOR_RIGHT_PORT, -MOTOR_SPEED);
				align_try = 0;
			}

			is_on_node = false;
			robot_wait(MOTOR_MOVE_DURATION);
		}
	}
	printf("Stop %d\n", color_val);
	motor_stop();
}

void move_backward()
{
	motor_set_speed(MOTOR_LEFT_PORT | MOTOR_RIGHT_PORT, MOTOR_SPEED);
	motor_start();
	int align_try = 0;
	int color_val = sensor_get_color_value();

	if(reach_dropzone == true && sensor_touch_pressed())
	{
		printf("Drop package\n");
		motor_lift_up();
		carry_package = false;
		reach_dropzone = false;
	}

	while(1)
	{
		prev_color_value = color_val;
		color_val = sensor_get_color_value();
		printf("color value: %d\n", color_val);

		if(sensor_color_on_wrong_path(color_val)){
			is_on_node = false;
			motor_align_path(color_val);

			motor_set_speed(MOTOR_LEFT_PORT | MOTOR_RIGHT_PORT, MOTOR_SPEED);
			robot_wait(MOTOR_LAST_ALIGN_TRY_DURATION);

			align_try++;

			if(align_try > MOTOR_ALIGN_TRY)
			{
				printf("Last try\n");
				motor_set_speed(MOTOR_LEFT_PORT | MOTOR_RIGHT_PORT, -MOTOR_SPEED);
				robot_wait(MOTOR_LAST_ALIGN_TRY_DURATION);
				break;
			}
		}
		else if(sensor_color_on_node(color_val))
		{
			if(is_on_node == false){
				is_on_node = true;
				break;
			}

			motor_set_speed(MOTOR_LEFT_PORT | MOTOR_RIGHT_PORT, MOTOR_SPEED);
			robot_wait(MOTOR_MOVE_DURATION);
		}
		else if(sensor_color_on_path(color_val)){
			if(align_try > 0)
			{
				motor_set_speed(MOTOR_LEFT_PORT | MOTOR_RIGHT_PORT, MOTOR_SPEED);
				align_try = 0;
			}
			is_on_node = false;
			robot_wait(MOTOR_MOVE_DURATION);
		}
	}
	printf("Stop %d\n", color_val);
	motor_stop();
}

void move_right()
{
	motor_set_speed(MOTOR_LEFT_PORT, -MOTOR_SPEED);
	motor_set_speed(MOTOR_RIGHT_PORT, MOTOR_SPEED);
	motor_start();
	robot_wait(MOTOR_TURN_DURATION);
	motor_stop();
	move_forward();
}

void move_left()
{
	motor_set_speed(MOTOR_LEFT_PORT, MOTOR_SPEED);
	motor_set_speed(MOTOR_RIGHT_PORT, -MOTOR_SPEED);
	motor_start();
	robot_wait(MOTOR_TURN_DURATION);
	motor_stop();
	move_forward();
}