#include "Tasks/TaskInput.h"

TaskHandle_t	InitInputManagement()
{
	TaskHandle_t	handle;

	#ifdef SERIAL_DEBUG
		Serial.println("- Input Management init ..");
	#endif
	pinMode(PIN_BTN_LEFT, INPUT_PULLDOWN);
	pinMode(PIN_BTN_MIDDLE, INPUT_PULLDOWN);
	pinMode(PIN_BTN_RIGHT, INPUT_PULLDOWN);

	xTaskCreate(
		InputManagementTask, "input management", 2048, NULL, 2, &handle);

	return (handle);
}

void		InputManagementTask(void *parameter)
{
	QueueHandle_t	inputQueue = Application::singleton->inputQueue;

	bool LCurrentState = false;
	bool MCurrentState = false;
	bool RCurrentState = false;

	for(;;)
	{
		// TODO -> A REFACTORISER AVANT LA RELEASE !
		if (digitalRead(PIN_BTN_LEFT) && LCurrentState == false)
		{
			LCurrentState = true;
			BtnEvent BtnEvent = { BTN::LEFT, LCurrentState };
			xQueueSend(inputQueue, &BtnEvent, 0);
		}
		else if (!digitalRead(PIN_BTN_LEFT) && LCurrentState == true)
		{
			LCurrentState = false;
			BtnEvent BtnEvent = { BTN::LEFT, LCurrentState };
			xQueueSend(inputQueue, &BtnEvent, 0);
		}
		
		if (digitalRead(PIN_BTN_MIDDLE) && MCurrentState == false)
		{
			MCurrentState = true;
			BtnEvent BtnEvent = { BTN::MIDDLE, MCurrentState };
			xQueueSend(inputQueue, &BtnEvent, 0);
		}
		else if (!digitalRead(PIN_BTN_MIDDLE) && MCurrentState == true)
		{
			MCurrentState = false;
			BtnEvent BtnEvent = { BTN::MIDDLE, MCurrentState };
			xQueueSend(inputQueue, &BtnEvent, 0);
		}

		if (digitalRead(PIN_BTN_RIGHT) && RCurrentState == false)
		{
			RCurrentState = true;
			BtnEvent BtnEvent = { BTN::RIGHT, RCurrentState };
			xQueueSend(inputQueue, &BtnEvent, 0);
		}
		else if (!digitalRead(PIN_BTN_RIGHT) && RCurrentState == true)
		{
			RCurrentState = false;
			BtnEvent BtnEvent = { BTN::RIGHT, RCurrentState };
			xQueueSend(inputQueue, &BtnEvent, 0);
		}

		delay(20); // 20ms
	}
}
