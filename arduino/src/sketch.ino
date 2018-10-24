//Battery voltage checker
//Minimim accepted voltage : 10.8V for 1 minute


#include "battery.h"

Battery* batt1;
Battery* batt2;

void setup()
{
   pinMode(10, OUTPUT);
   Serial.begin(9600);
   batt1 = new Battery(1);
	batt2 = new Battery(2);
}


void startAlarm()
{
	analogWrite(10, 220);
}

void stopAlarm()
{
	analogWrite(10,0);
}

void stream(float v1, float v2, int shutdown)
{
	Serial.print(v1);
	Serial.print(' ');
	Serial.print(v2);
	Serial.print(' ');
	Serial.println(shutdown);
}


void loop()
{
	float volt1 = batt1->voltage();
	float volt2 = batt2->voltage();
	
	bool alarming = batt1->alarming() || batt2->alarming();
	
	if (alarming)
		startAlarm();
	else
		stopAlarm();
	
	bool danger = batt1->danger() || batt2->danger();
	int dangerSignal = (int) danger;
	stream(volt1, volt2, dangerSignal);
}
