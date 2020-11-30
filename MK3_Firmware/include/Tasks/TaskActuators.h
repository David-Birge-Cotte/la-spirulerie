#ifndef TASK_ACTUATORS_H
#define TASK_ACTUATORS_H

#include <Arduino.h>
#include "App.h"

#define PWM_FREQ_IO			40000		// 40 khz
#define PWM_RESOLUTION_BITS	10
#define PWM_MAX_RESOLUTION	1023

// data container for PWM output
struct	ActuatorPWMAction
{
	uint8_t 	channel;
	float		percentage;
	uint32_t	speed;
};

// Entry point
TaskHandle_t	InitActuators();

// RTOS tasks
void	ActuatorTask(void *parameter);
void	Task_IO_A(void *parameter);
void	Task_IO_B(void *parameter);
void	Task_IO_C(void *parameter);
void	Task_IO_D(void *parameter);
//void	Task_Brightness(void *parameter);

// Functions
void	ChannelTaskFunc(uint8_t channel, QueueHandle_t queue);
void	InitPWM(uint8_t channel, double frequency, uint8_t pin);
void	PWM_Write(uint8_t channel, uint16_t duty);
void	PWM_Fade(uint8_t channel, uint16_t from_duty, uint16_t to_duty, uint32_t ms);

#endif