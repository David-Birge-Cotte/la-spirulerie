#ifndef DATA_SAVE_LOAD_H
#define DATA_SAVE_LOAD_H

#include "DataTypes.h"
#include <EEPROM.h>

namespace DataSaveLoad
{
	// The numbers are indexes of each data in EEPROM
	// it needs to take in in account each data memory size in bytes
	enum EEPROM_INDEX
	{
		INITIALIZED				= 0,	// bool
		CURRENT_MODE_NB			= 1,	// uint8_t
		BOOT_NB 				= 2,	// uint64_t
		THERMOMETER_ADJUSTEMENT	= 10,	// float
		HEATING_PERCENTAGE		= 14,	// uint8_t
		SCREENSAVE				= 15,	// bool
		CUSTOM_MODE				= 16	// ModeParameters (struct of 7 bytes ? just put it as last element..)
	};

	void		InitEEPROM();
	void		Clear();

	uint8_t		Load(int index);
	void		Write(int index, uint8_t data);

	void		SetDeviceInitialized(bool initialized);
	bool		ReadDeviceInitialized();

	void		SetCurrentMode(uint8_t mode_nb);
	uint8_t		ReadCurrentMode();

	void		SetBootNb(uint64_t boot_nb);
	uint64_t	ReadBootNb();

	void		SetThermometerAdjustement(float adjustement);
	float		ReadThermometerAdjustement();

	void		SetCurrentHeatingPercentage(uint8_t heating_percentage);
	uint8_t		ReadCurrentHeatingPercentage();

	void		SetCanScreenSave(bool canScreenSave);
	bool		ReadCanScreenSave();

	void			SetCustomMode(ModeParameters mode);
	ModeParameters	ReadCustomMode();
}

#endif