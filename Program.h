#pragma once

#include "WString.h"
#include "LiquidCrystal.h"
#include "Arduino.h"

class Program
{
public:
	Program();
	~Program();
	void reinit();
	void Stepping();

	unsigned int countLoop = 10;
	unsigned int countStep = 500;
	unsigned int countDelay = 200;
	unsigned int commonCount = 5;
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

	void show();
	void reinitMenu();
	void menuDown();
	void menuUp();
	void currentItemUp();
	void currentItemDowm();

	const String s[menuItemCount] =
	{
		"Loop  ",
		"Step  ",
		"Delay ",
		"Common"
	};
};

