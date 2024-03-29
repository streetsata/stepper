#pragma once

#include "WString.h"
#include "LiquidCrystal.h"
#include "Arduino.h"
#include "EEPROM.h"

struct EEPROM_DATA
{
	unsigned int countLoop = 10;
	unsigned int countStep = 500;
	unsigned int countDelay = 200;
	unsigned int commonCount = 0;
};

class Program
{
public:
	Program();
	~Program();
	void reinit();
private:
	static const int menuItemCount = 4;
	static const int delayTime = 500;

	LiquidCrystal* lcd = NULL;

	String lcdLine1 = "";
	String lcdLine2 = "";

	bool buttonLeft = 0;
	bool buttonRight = 0;
	bool buttonUp = 0;
	bool buttonDown = 0;
	bool buttonStart = 0;
	bool buttonSelect = 0;

	int prevMenuItem = 0;
	int currentMenuItem = 1;

	EEPROM_DATA data;

	//////////////////////////////////////////
	int dirpin = 6;
	int steppin = 7;
	int enable = 8;
	int sensor = 2;
	//////////////////////////////////////////

	void show();
	void reinitMenu();
	void menuDown();
	void menuUp();
	void currentItemUp();
	void currentItemDowm();
	void manageStepMotor(bool isStep);

	const String s[menuItemCount] =
	{
		"Loop  ",
		"Step  ",
		"Delay ",
		"Common"
	};
};

