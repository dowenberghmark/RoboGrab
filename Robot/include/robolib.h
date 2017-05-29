#ifndef ROBOLIB_INCLUDED_H
#define ROBOLIB_INCLUDED_H

#define MOTOR_LEFT_PORT OUTB
#define MOTOR_RIGHT_PORT OUTC
#define SENSOR_COLOR_PORT IN1

#define MOTOR_SPEED_NORMAL 50
#define MOTOR_SPEED_SLOW 10
#define MOTOR_MOVE_DURATION 1000
#define MOTOR_TURN_DURATION 1300

int init_robot();
void uninit_robor();
void move_forward();
void move_backward();
void move_left();
void move_right();

#endif