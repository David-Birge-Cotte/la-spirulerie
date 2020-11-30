#include "Tasks/TaskAudioEngine.h"

TaskHandle_t InitAudio()
{
	TaskHandle_t	handle;

	#ifdef SERIAL_DEBUG
		Serial.println("- Audio Engine init ..");
	#endif

	pinMode(PIN_DACBUZZER, OUTPUT);
	ledcSetup(PWMC_DAC, 2000, 8);
	ledcAttachPin(PIN_DACBUZZER, PWMC_DAC);

	xTaskCreate(
		AudioEngineTask, "audio engine", 2048, NULL, 1, &handle);

	return (handle);
}

void PlayNote(note_t note, uint8_t octave, uint32_t time)
{
	ledcWriteNote(PWMC_DAC, note, octave);
	delay(time);
	ledcWrite(PWMC_DAC, 0);
}

void AudioEngineTask(void *parameter)
{
	QueueHandle_t	queue = Application::singleton->audioQueue;

	for (;;)
	{
		Melodies melody;
		xQueueReceive(queue, &melody, portMAX_DELAY);

		if (melody == Melodies::BOOT)
		{
			PlayNote(note_t::NOTE_A, 4, 150);
			PlayNote(note_t::NOTE_B, 4, 150);
			PlayNote(note_t::NOTE_Cs, 5, 150);
			PlayNote(note_t::NOTE_E, 5, 150);
			PlayNote(note_t::NOTE_A, 5, 150);
			PlayNote(note_t::NOTE_B, 5, 150);
			PlayNote(note_t::NOTE_A, 5, 150);
			PlayNote(note_t::NOTE_E, 5, 150);
			PlayNote(note_t::NOTE_A, 5, 300);
		}
		if (melody == Melodies::VALID)
		{
			PlayNote(note_t::NOTE_E, 4, 40);
			PlayNote(note_t::NOTE_Gs, 5, 50);
		}
		if (melody == Melodies::ERROR)
		{
			PlayNote(note_t::NOTE_A, 4, 100);
			PlayNote(note_t::NOTE_Gs, 4, 200);
		}
	}
}