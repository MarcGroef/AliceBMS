#ifndef INCLUDED_BATTERY_H_
#define INCLUDED_BATTERY_H_

#include <Arduino.h>

class Battery
{
	bool d_timerStarted;
	int d_startTime;
	int d_maxAlarmTime;
	int d_measurePin;
	float d_voltage;
	float d_thresholdVoltage;
	float d_secondResistor;  //Keep units of these resistances the same. Probably MOhm
	float d_totalResistance;
public:
	Battery(int measurePin, float thresholdVoltage = 10.8, float secondResistor = 9.82, float totalResistance = 29.6, int maxAlarmTime = 60);
	float voltage();
	void startTimer();
	void stopTimer();
	float secondsElapsed();
	bool alarming();
	bool danger();
private:
	float time(); // returns time in seconds
};


#endif