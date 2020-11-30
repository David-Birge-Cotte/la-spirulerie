#include "DataSaveLoad.h"
#include "App.h"

namespace DataSaveLoad
{
	void		InitEEPROM()
	{
		EEPROM.begin(1024);
	}

	void		Clear()
	{
		ModeParameters mode; // default constructor

		SetDeviceInitialized(false);
		SetCurrentMode(0);
		SetBootNb(0);
		SetThermometerAdjustement(0.0f);
		SetCurrentHeatingPercentage(MAX_PERCENTAGE_HEATER);
		SetCanScreenSave(false);
		SetCustomMode(mode);
	}

	uint8_t		Load(int index)
	{
		return (EEPROM.read(index));
	}

	void		Write(int index, uint8_t data)
	{
		EEPROM.write(index, data);
	}

	void		SetDeviceInitialized(bool initialized)
	{
		EEPROM.writeBool(INITIALIZED, !initialized);
		EEPROM.commit(); // Push changes to EEPROM
	}

	bool		ReadDeviceInitialized()
	{
		return (!EEPROM.readBool(INITIALIZED));
	}

	void		SetBootNb(uint64_t boot_nb)
	{
		EEPROM.writeULong64(BOOT_NB, boot_nb);
		EEPROM.commit(); // Push changes to EEPROM
	}

	uint64_t	ReadBootNb()
	{
		return (EEPROM.readULong64(BOOT_NB));
	}

	void		SetThermometerAdjustement(float adjustement)
	{
		EEPROM.writeFloat(THERMOMETER_ADJUSTEMENT, adjustement);
		EEPROM.commit(); // Push changes to EEPROM
	}

	float		ReadThermometerAdjustement()
	{
		return (EEPROM.readFloat(THERMOMETER_ADJUSTEMENT));
	}

	void		SetCurrentHeatingPercentage(uint8_t heating_percentage)
	{
		EEPROM.writeByte(HEATING_PERCENTAGE, heating_percentage);
		EEPROM.commit(); // Push changes to EEPROM
	}

	uint8_t		ReadCurrentHeatingPercentage()
	{
		return (EEPROM.read(HEATING_PERCENTAGE));
	}

	void		SetCanScreenSave(bool canScreenSave)
	{
		EEPROM.writeBool(SCREENSAVE, canScreenSave);
		EEPROM.commit(); // Push changes to EEPROM
	}

	bool		ReadCanScreenSave()
	{
		return (EEPROM.readBool(SCREENSAVE));
	}

	void		SetCurrentMode(uint8_t mode_nb)
	{
		EEPROM.writeByte(CURRENT_MODE_NB, mode_nb);
		EEPROM.commit(); // Push changes to EEPROM
	}

	uint8_t		ReadCurrentMode()
	{
		return (EEPROM.readByte(CURRENT_MODE_NB));
	}

	void		SetCustomMode(ModeParameters mode)
	{
		EEPROM.put(CUSTOM_MODE, mode);
		EEPROM.commit();
	}

	ModeParameters	ReadCustomMode()
	{
		ModeParameters mode;
		EEPROM.get(CUSTOM_MODE, mode);

		return (mode);
	}
}
