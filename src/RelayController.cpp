#include"RelayController.h"
#include"Arduino.h"

int Index = 0;
int Note = 0;
Relay::Relay(int pin[], int n)
{
	for (int i = 0; i < n; i++) {
		pinMode(pin[i], OUTPUT);
		_pin[i] = pin[i];
	}
}
void Relay::set(unsigned int index, unsigned int note){
	Index = index;
	Note = note;
		
}
void Relay::sing() {
	unsigned long time = micros();
	unsigned long preTime = time;
	unsigned long preTime2 = time;
	while (!Serial.available()) {
		time = micros();
		if (time - preTime2 < Note / 2) {
			digitalWrite(_pin[index - 1], HIGH);
			digitalWrite(_pin[index + 5], HIGH);
		}
		else if(time - preTime2 < Note){
			digitalWrite(_pin[index - 1], LOW);
			digitalWrite(_pin[index + 5], LOW);
		}else{
			preTime2 = time;
		}
	}
}
void Relay::rest(int msec) {
	long time = millis();
	long preTime = time;
	for (; time - preTime < msec;) {
		time = millis();
		for (int i = 0; i < 10; i++) {
			digitalWrite(_pin[i], LOW);
		}
	}
}