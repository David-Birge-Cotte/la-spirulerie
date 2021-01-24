#include "Tasks/TaskActuators.h"

TaskHandle_t InitActuators()
{
	TaskHandle_t	handle;

	#ifdef SERIAL_DEBUG
		Serial.println("- Actuators init ..");
	#endif

	xTaskCreate(
		ActuatorTask, "Actuators", 4096, NULL, 1, &handle);

	return (handle);
}

void ActuatorTask(void *parameter)
{
	// Queue of actions coming from Application
	QueueHandle_t	actionQueue = Application::singleton->PWMActionsQueue;

	// Queues to use with PWM tasks
	QueueHandle_t	IOAQueue = xQueueCreate(5, sizeof(ActuatorPWMAction));
	QueueHandle_t	IOBQueue = xQueueCreate(5, sizeof(ActuatorPWMAction));
	QueueHandle_t	IOCQueue = xQueueCreate(5, sizeof(ActuatorPWMAction));
	QueueHandle_t	IODQueue = xQueueCreate(5, sizeof(ActuatorPWMAction));
	//QueueHandle_t	BrightnessQueue = xQueueCreate(5, sizeof(ActuatorPWMAction));

	// Create different tasks for non blocking independant PWM channel control
	xTaskCreate(Task_IO_A, "IO_A", 2048, IOAQueue, 2, NULL);
	xTaskCreate(Task_IO_B, "IO_B", 2048, IOBQueue, 2, NULL);
	xTaskCreate(Task_IO_C, "IO_C", 2048, IOCQueue, 2, NULL);
	xTaskCreate(Task_IO_D, "IO_D", 2048, IODQueue, 2, NULL);
	//xTaskCreate(Task_Brightness, "BRIGHTNESS", 2048, BrightnessQueue, 2, NULL);

	Serial.printf("--> all actuator task started\n");

	for (;;)
	{
		ActuatorPWMAction action;

		// Wait indefinitely to receive an action
		xQueueReceive(actionQueue, &action, portMAX_DELAY);

		// direct actions to specific tasks driving PWM channels
		if (action.channel == PWMC_A)
			xQueueSend(IOAQueue, &action, portMAX_DELAY);
		if (action.channel == PWMC_B)
			xQueueSend(IOBQueue, &action, portMAX_DELAY);
		if (action.channel == PWMC_C)
			xQueueSend(IOCQueue, &action, portMAX_DELAY);
		if (action.channel == PWMC_D)
			xQueueSend(IODQueue, &action, portMAX_DELAY);
		//if (action.channel == PWMC_BRIGHTNESS)
		//	xQueueSend(BrightnessQueue, &action, portMAX_DELAY);
	}
}

void	Task_IO_A(void *parameter)
{
	InitPWM(PWMC_A, PWM_FREQ_IO, PORT_A);
	ChannelTaskFunc(PWMC_A, (QueueHandle_t)parameter);
}

void	Task_IO_B(void *parameter)
{
	InitPWM(PWMC_B, PWM_FREQ_IO, PORT_B);
	ChannelTaskFunc(PWMC_B, (QueueHandle_t)parameter);
}

void	Task_IO_C(void *parameter)
{
	InitPWM(PWMC_C, PWM_FREQ_IO, PORT_C);
	ChannelTaskFunc(PWMC_C, (QueueHandle_t)parameter);
}

void	Task_IO_D(void *parameter)
{
	InitPWM(PWMC_D, PWM_FREQ_IO, PORT_D);
	ChannelTaskFunc(PWMC_D, (QueueHandle_t)parameter);
}

/*void	Task_Brightness(void *parameter)
{
	InitPWM(PWMC_BRIGHTNESS, PWM_FREQ_LCD, PIN_LCDLIGHT);
	ChannelTaskFunc(PWMC_BRIGHTNESS, (QueueHandle_t)parameter);
}*/

// This function is the main loop of the RTOS task for the PWM channel
void	ChannelTaskFunc(uint8_t channel, QueueHandle_t queue)
{
	uint16_t		current_duty = 0;
	uint16_t 		target_duty = 0;

	for (;;)
	{
		ActuatorPWMAction action;
		xQueueReceive(queue, &action, portMAX_DELAY);

		target_duty = action.percentage * (float)PWM_MAX_RESOLUTION / 100.0f;
		PWM_Fade(channel, current_duty, target_duty, action.speed);
		current_duty = target_duty;
	}
}

// Initialize the pin and pwm channel
void	InitPWM(uint8_t channel, double frequency, uint8_t pin)
{
	pinMode(pin, OUTPUT);
	ledcSetup(channel, frequency, PWM_RESOLUTION_BITS);
	ledcAttachPin(pin, channel);
}

// Outputs PWM on selected channel
void	PWM_Write(uint8_t channel, uint16_t duty)
{
	ledcWrite(channel, duty);
}

// Fades the PWM channel to a new value in a specific timing
void	PWM_Fade(uint8_t channel, uint16_t from_duty, uint16_t to_duty, uint32_t ms)
{
	int8_t		sign;
	int16_t		diff;

	if (from_duty == to_duty)
		return;

	sign = (to_duty > from_duty ? 1 : -1);
	diff = (to_duty - from_duty) * sign;

	while (from_duty != to_duty)
	{
		PWM_Write(channel, from_duty);
		from_duty += sign;
		delay(ms / diff);
	}
	PWM_Write(channel, to_duty);
}