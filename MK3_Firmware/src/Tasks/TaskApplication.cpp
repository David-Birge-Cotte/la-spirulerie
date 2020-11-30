#include "Tasks/TaskApplication.h"

void InitApplication()
{
	TaskHandle_t task_handle = Application::singleton->applicationTask;
	xTaskCreate(
		ApplicationTask, "main program", 8192, NULL, 2, &task_handle);
}

void ApplicationTask(void *parameter)
{
	Application::singleton->Init();

	for (;;)
	{
		Application::singleton->Update();
	}
}