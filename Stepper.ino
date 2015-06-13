#include "LiquidCrystal.h"
#include "Arduino.h"

#include "Program.h"

Program* program = NULL;
int dirpin = 6;
int steppin = 7;
int enable = 8;
int sensor = 2;

void setup()
{
	pinMode(dirpin, OUTPUT);
	pinMode(steppin, OUTPUT);
	pinMode(sensor, INPUT);

	program = new Program();
}

void loop()
{
	program->reinit();

	digitalWrite(dirpin, HIGH); // Set the direction.
	if (analogRead(A4) == 1023)
	{
		if (digitalRead(sensor) != HIGH)
		{
			for (long i = 0; i < 2; i++)
			{
				digitalWrite(steppin, LOW); // This LOW to HIGH change is what creates the
				delayMicroseconds(program->countDelay);
				digitalWrite(steppin, HIGH);
				delayMicroseconds(program->countDelay); // This delay time is close to top speed for this
			} // particular motor. Any faster the motor stalls
		}
		else
		{
			for (int t = 0; t < program->countLoop; t++)
			{
				steping();
			}
		}
	}
}

void steping()
{
	delay(1500);
	//digitalWrite(enable, LOW);
	for (long j = 0; j<program->countStep; j++) // Iterate for 4000 microsteps.
	{
		digitalWrite(steppin, LOW); // This LOW to HIGH change is what creates the
		delayMicroseconds(program->countDelay);
		digitalWrite(steppin, HIGH);
		delayMicroseconds(program->countDelay); // This delay time is close to top speed for this
	} // particular motor. Any faster the motor stalls.
	//digitalWrite(enable, LOW);
}
