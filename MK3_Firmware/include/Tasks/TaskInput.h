#ifndef INPUT_H
#define INPUT_H

#include "App.h"

struct InputData
{
	uint8_t		btnNum;
	int64_t		timing;
};

// Entry point
TaskHandle_t 	InitInputManagement();

// RTOS task
void			InputManagementTask(void *parameter);

#endif