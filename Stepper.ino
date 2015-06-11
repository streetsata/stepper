#include "LiquidCrystal.h"
#include "Arduino.h"

#include "Program.h"

Program* program = NULL;

void setup()
{
	program = new Program();
}

void loop()
{
	program->reinit();
}
