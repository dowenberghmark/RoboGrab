#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "brick.h"
#include "robolib.h"

int prev_align_dir = 0;
POOL_T MOTOR_LEFT_PORT;
POOL_T MOTOR_RIGHT_PORT; 
POOL_T MOTOR_LIFT_PORT; 
POOL_T SENSOR_COLOR_PORT;
POOL_T SENSOR_TOUCH_PORT;

int MOTOR_SPEED;
int MOTOR_MOVE_DURATION;
int MOTOR_TURN_DURATION;

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

int read_config()
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
   			else if(strcmp(key, "SENSOR_TOUCH_PORT") == 0)
   			{
   				SENSOR_TOUCH_PORT = config_get_port(value);
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
   		}

  		fclose(file);
        return 0;
    }

    printf("Cannot open config file. Please check config/robot.conf\n");
    return -1;
}

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

void motor_wait(int duration)
{
	sleep_ms(duration);
}

void motor_stop()
{
	tacho_stop(MOTOR_LEFT_PORT | MOTOR_RIGHT_PORT);
}

void motor_align_path()
{
	int val = sensor_get_color_value();
	if(val > 10)
	{
		if(prev_align_dir == 0)
		{
			// right
			motor_set_speed(MOTOR_LEFT_PORT, -MOTOR_SPEED);
			motor_set_speed(MOTOR_RIGHT_PORT, MOTOR_SPEED);
			motor_start();
			motor_wait(100);
			motor_stop();
			prev_align_dir = 1;
		}
		else
		{
			// left
			motor_set_speed(MOTOR_LEFT_PORT, MOTOR_SPEED);
			motor_set_speed(MOTOR_RIGHT_PORT, -MOTOR_SPEED);
			motor_start();
			motor_wait(100);
			motor_stop();
			prev_align_dir = 0;
		}
	}
}

// PUBLIC ====================================================================
int init_robot()
{
	read_config();
	printf("%d %d %d\n", MOTOR_SPEED, MOTOR_MOVE_DURATION, MOTOR_TURN_DURATION);
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
	motor_set_speed(MOTOR_LEFT_PORT | MOTOR_RIGHT_PORT, -MOTOR_SPEED);
	motor_start();
	motor_wait(MOTOR_MOVE_DURATION);
	motor_stop();
}

void move_backward()
{
	motor_set_speed(MOTOR_LEFT_PORT | MOTOR_RIGHT_PORT, MOTOR_SPEED);
	motor_start();
	motor_wait(MOTOR_MOVE_DURATION);
	motor_stop();
}

void move_right()
{
	motor_set_speed(MOTOR_LEFT_PORT, -MOTOR_SPEED);
	motor_set_speed(MOTOR_RIGHT_PORT, MOTOR_SPEED);
	motor_start();
	motor_wait(MOTOR_TURN_DURATION);
	motor_stop();
}

void move_left()
{
	motor_set_speed(MOTOR_LEFT_PORT, MOTOR_SPEED);
	motor_set_speed(MOTOR_RIGHT_PORT, -MOTOR_SPEED);
	motor_start();
	motor_wait(MOTOR_TURN_DURATION);
	motor_stop();
}