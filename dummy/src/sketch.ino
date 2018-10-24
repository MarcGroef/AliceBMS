

void setup()
{
	Serial.begin(9600);
}

void loop()
{
	int shutdownSig = 0;
	if (analogRead(13) < 500)
		shutdownSig = 1;
	else
		shutdownSig = 0;
		
	Serial.print(11.25);
	Serial.print(' ');
	Serial.print(11.25);
	Serial.print(' ');
	Serial.println(shutdownSig);
	delay(5000);
}

