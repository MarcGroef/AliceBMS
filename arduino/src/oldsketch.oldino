//Battery voltage checker
//Minimim accepted voltage : 10.8V for 1 minute
#define DEBUG
#define N_BATTERIES 2

float minimumVoltage = 10.8;

typedef struct _Battery
{
  float offset;
  float voltage;
  bool timerStarted;
  int startTime;
  int measurePin;
  bool alarming;
} Battery;

Battery battery[N_BATTERIES];

void setup()
{
   pinMode(10, OUTPUT);
   Serial.begin(9600);
   battery[0].timerStarted = false;
   battery[0].measurePin = 0;
   battery[0].alarming = false;
   battery[0].offset = -0;
   battery[1].timerStarted = false;
   battery[1].measurePin = 5;
   battery[1].alarming = false;
   battery[1].offset = 0;
}

int getExecutionSeconds()
{
   return millis() / 1000;
}



float readVolts(int analogPin)
{
   float analog = (float)analogRead(analogPin) * 5.0 / 1024.;
   float rest2 = 9.82;//megaOhm
   float restTotal = 29.6; //megaOhm
   return analog * (restTotal / rest2) ;
}

void alarm()
{
  analogWrite(10, 220);
  Serial.println("Alarm is playing");
}

void shutdown()
{
   //Serial.println("sending shutdown command");
}

bool shouldShutDown()
{
  for (int battIdx = 0; battIdx != N_BATTERIES; ++battIdx)
  {
    float timeElapsed = getExecutionSeconds() - battery[battIdx].startTime;
    if (timeElapsed > 0)
      return true;
  }
  return false;
}

bool batteriesAreAlarming()
{
  for (int battIdx = 0; battIdx != N_BATTERIES; ++battIdx)
     if(battery[battIdx].alarming)
        return true;
  return false;
}

void checkBattery(int battIdx)
{
  float voltage;
  //for (int check = 0; check != 10; ++check)
  delay(500);
  voltage = readVolts(battery[battIdx].measurePin) + battery[battIdx].offset;
  Serial.print(voltage);
  Serial.print(", ");
  //Serial.println(battIdx);
   
   if(voltage < minimumVoltage)
   {
      battery[battIdx].alarming = true;
      if(battery[battIdx].timerStarted == false)
      {
         battery[battIdx].startTime = getExecutionSeconds();
         battery[battIdx].timerStarted = true;
      }
   }
   else
   {
      battery[battIdx].timerStarted = false;
      battery[battIdx].alarming = false;
   }
}

void loop()
{
   for (int battIdx = 0; battIdx != N_BATTERIES; ++battIdx)
   {
     checkBattery(battIdx);
   }
   Serial.println('\n');
   if (batteriesAreAlarming())
     alarm();
   else
     analogWrite(10,0);
   if (shouldShutDown())
     shutdown();
}
