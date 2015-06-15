#include "LiquidCrystal.h"
#include "Arduino.h"
//#include "EEPROM\EEPROM.h"
#include "EEPROM.h"

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