#include "battery.h"


Battery::Battery(int measurePin, float thresholdVoltage, float secondResistor, float totalResistance, int maxAlarmTime)
:
	d_timerStarted(false),
	d_startTime(0),
	d_maxAlarmTime(maxAlarmTime),
	d_measurePin(measurePin),
	d_voltage(0),
	d_thresholdVoltage(thresholdVoltage),
	d_secondResistor(secondResistor),
	d_totalResistance(totalResistance)
{
}

bool Battery::alarming()
{
	return d_timerStarted;
}

bool Battery::danger()
{
	return secondsElapsed() > d_maxAlarmTime;
}

float Battery::voltage()
{
	delay(500);
	float readVoltage = (float)analogRead(d_measurePin) * 5.0 / 1024.;
	float battVoltage = readVoltage * (d_totalResistance / d_secondResistor) ;
	if (battVoltage < d_thresholdVoltage && !d_timerStarted)
		startTimer();
	if (battVoltage >= d_thresholdVoltage)
		stopTimer();
	return battVoltage;
}

void Battery::startTimer()
{
	d_timerStarted = true;
	d_startTime = time();
}

void Battery::stopTimer()
{
	d_timerStarted = false;
	d_startTime = 0;
}

float Battery::secondsElapsed()
{	
	return time() - d_startTime;
}

float Battery::time()
{
	return millis() / 1000;
}