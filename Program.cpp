#include "Program.h"



Program::Program()
{
	if (this->lcd == NULL)
	{
		lcd = new LiquidCrystal(12, 11, 10, 5, 4, 3, 2);
		lcd->begin(16, 2);
	}

	data.countLoop = EEPROM.read(0);
	//////////////////////////////////////////
	pinMode(dirpin, OUTPUT);
	pinMode(steppin, OUTPUT);
	pinMode(sensor, INPUT);
	digitalWrite(dirpin, HIGH); // Set the direction.
	//////////////////////////////////////////

	reinitMenu();
}

Program::~Program()
{
	
}

void Program::reinit()
{
	// Button Down
	if (analogRead(A0) == 1023)
	{
		this->menuDown();
		delay(delayTime);
		EEPROM.write(0, data.countLoop);
	}

	// Button Up
	if (analogRead(A1) == 1023)
	{
		this->menuUp();
		delay(delayTime);
	}

	// Button Left
	if (analogRead(A2) == 1023)
	{
		this->currentItemDowm();
		delay(delayTime);
	}

	// Button Right
	if (analogRead(A3) == 1023)
	{
		this->currentItemUp();
		delay(delayTime);
	}

	// Start engine
	if (analogRead(A4) == 1023)
	{
		manageStepMotor(false);
	}

	if (digitalRead(sensor) == HIGH)
	{
		manageStepMotor(true);
	}
	else
	{
		manageStepMotor(false);
	}

	if (this->currentMenuItem != this->prevMenuItem)
	{
		this->prevMenuItem = this->currentMenuItem;
		reinitMenu();
	}
}

void Program::currentItemUp()
{
	if (currentMenuItem == 1)
		data.countLoop++;
	if (currentMenuItem == 2)
		data.countStep++;
	if (currentMenuItem == 3)
		data.countDelay++;

	reinitMenu();
}

void Program::currentItemDowm()
{
	if (currentMenuItem == 1)
		data.countLoop = data.countLoop != 0 ? data.countLoop - 1 : data.countLoop;
	if (currentMenuItem == 2)
		data.countStep = data.countStep != 0 ? data.countStep - 1 : data.countStep;
	if (currentMenuItem == 3)
		data.countDelay = data.countDelay != 0 ? data.countDelay - 1 : data.countDelay;

	reinitMenu();
}

void Program::menuDown()
{
	prevMenuItem = currentMenuItem;
	if (currentMenuItem != menuItemCount)
		currentMenuItem++;
	else
		currentMenuItem = 1;
}

void Program::menuUp()
{
	prevMenuItem = currentMenuItem;
	this->lcdLine2 = this->s[currentMenuItem - 1];

	if (currentMenuItem != 1)
		currentMenuItem--;
	else
		currentMenuItem = menuItemCount;

	this->lcdLine1 = this->s[currentMenuItem - 1];
}

void Program::show()
{
	this->lcd->clear();
	this->lcd->setCursor(0, 0);
	this->lcd->print(this->lcdLine1);
	this->lcd->setCursor(0, 1);
	this->lcd->print(this->lcdLine2);
}

void Program::reinitMenu()
{
	this->lcdLine1 = this->s[currentMenuItem - 1];
	if (currentMenuItem == menuItemCount)
		this->lcdLine2 = this->s[0];
	else
		this->lcdLine2 = this->s[currentMenuItem];

	this->lcdLine1 = String("* ") + this->lcdLine1 + String(": ");
	this->lcdLine2 = String("  ") + this->lcdLine2 + String(": ");

	if (this->currentMenuItem == 1)
	{
		this->lcdLine1 += String(data.countLoop);
		this->lcdLine2 += String(data.countStep);
	}

	if (this->currentMenuItem == 2)
	{
		this->lcdLine1 += String(data.countStep);
		this->lcdLine2 += String(data.countDelay);
	}

	if (this->currentMenuItem == 3)
	{
		this->lcdLine1 += String(data.countDelay);
		this->lcdLine2 += String(data.commonCount);
	}

	if (this->currentMenuItem == 4)
	{
		this->lcdLine1 += String(data.commonCount);
		this->lcdLine2 += String(data.countLoop);
	}

	this->show();
}


void Program::manageStepMotor(bool isStep)
{
	if (isStep)
	{
		for (int t = 0; t < data.countLoop; t++)
		{
			//delay(1500);
			//digitalWrite(enable, LOW);
			for (long j = 0; j < data.countStep; j++) // Iterate for 4000 microsteps.
			{
				digitalWrite(steppin, LOW); // This LOW to HIGH change is what creates the
				delayMicroseconds(data.countDelay);
				digitalWrite(steppin, HIGH);
				delayMicroseconds(data.countDelay); // This delay time is close to top speed for this
			} // particular motor. Any faster the motor stalls.
			//digitalWrite(enable, LOW);
		}
	}
	else
	{
		for (long i = 0; i < 2; i++)
		{
			digitalWrite(steppin, LOW); // This LOW to HIGH change is what creates the
			delayMicroseconds(data.countDelay);
			digitalWrite(steppin, HIGH);
			delayMicroseconds(data.countDelay); // This delay time is close to top speed for this
		} // particular motor. Any faster the motor stalls
	}
}