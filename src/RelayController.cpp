#include"RelayController.h"
#include"Arduino.h"

Relay::Relay(int pin[], int n)
{
	for (int i = 0; i < n; i++) {
		pinMode(pin[i], OUTPUT);
		_pin[i] = pin[i];
	}
}
void Relay::sing(unsigned int part1, unsigned int ompu, unsigned int tmp) {
	sing(part1, part1, ompu, tmp);
}
void Relay::sing(unsigned int part1, unsigned int part2, unsigned int ompu, unsigned int tmp) {
	sing(part1, part2, part1, part2, ompu, tmp);
}
void Relay::sing(unsigned int part1, unsigned int part2, unsigned int part3, unsigned int part4, unsigned int ompu, unsigned int tmp) {
	sing(part1, part2, part3, part4, part1, part2, part3, part4, part1, part2, ompu, tmp);
}
void Relay::sing(unsigned int part1, unsigned int part2, unsigned int part3, unsigned int part4, unsigned int part5, unsigned int ompu, unsigned int tmp) {
	sing(part1, part2, part3, part4, part5, part1, part2, part3, part4, part5, ompu, tmp);
}
void Relay::sing(unsigned int Onkai1, unsigned int Onkai2, unsigned int Onkai3, unsigned int Onkai4, unsigned int Onkai5, unsigned int Onkai6, unsigned int Onkai7, unsigned int Onkai8, unsigned int Onkai9, unsigned int Onkai10, unsigned int Ompu, unsigned int tmp) {
	_tmp = tmp;
	long msecon = 0;
	switch (Ompu) {
	case 32:
		msecon = (long)60 * (long)1000 / (long)_tmp / (long)8;
		break;
	case 16:
		msecon = (long)60 * (long)1000 / (long)_tmp / (long)4;
		break;
	case 12:
		msecon = (long)60 * (long)1000 / (long)_tmp / (long)3;
		break;
	case 8:
		msecon = (long)60 * (long)1000 / (long)_tmp / (long)2;
		break;
	case 4:
		msecon = (long)60 * (long)1000 / (long)_tmp;
		break;
	case 45:
		msecon = (long)60 * (long)1000 / (long)_tmp / (long)3 * (long)2;
		break;
	case 2:
		msecon = (long)60 * (long)1000 / (long)_tmp * (long)2;
		break;
	case 1:
		msecon = (long)60 * (long)1000 / (long)_tmp * (long)4;
		break;
	}
	unsigned long time = micros();
	unsigned long preTime = time;
	unsigned long preTime2 = time;
	unsigned long preTime3 = time;
	unsigned long preTime4 = time;
	unsigned long preTime5 = time;
	unsigned long preTime6 = time;
	unsigned long preTime7 = time;
	unsigned long preTime8 = time;
	unsigned long preTime9 = time;
	unsigned long preTime10 = time;
	unsigned long preTime11 = time;
	for (; time - preTime < msecon * 1000;) {
		time = micros();
		if (time - preTime2 < Onkai1 / 2) {
			digitalWrite(_pin[0], HIGH);
		}
		else if(time - preTime2 < Onkai1){
			digitalWrite(_pin[0], LOW);
		}else{
			preTime2 = time;
		}
		if (time - preTime3 < Onkai2 / 2) {
			digitalWrite(_pin[1], HIGH);
		}
		else if(time - preTime3 < Onkai2){
			digitalWrite(_pin[1], LOW);
		}else{
			preTime3 = time;
		}
		if (time - preTime4 < Onkai3 / 2) {
			digitalWrite(_pin[2], HIGH);
		}
		else if(time - preTime4 < Onkai3){
			digitalWrite(_pin[2], LOW);
		}else{
			preTime4 = time;
		}
		if (time - preTime5 < Onkai4 / 2) {
			digitalWrite(_pin[3], HIGH);
		}
		else if(time - preTime5 < Onkai4){
			digitalWrite(_pin[3], LOW);
		}else{
			preTime5 = time;
		}
		if (time - preTime6 < Onkai5 / 2) {
			digitalWrite(_pin[4], HIGH);
		}
		else if(time - preTime6 < Onkai5){
			digitalWrite(_pin[4], LOW);
		}else{
			preTime6 = time;
		}
		if (time - preTime7 < Onkai6 / 2) {
			digitalWrite(_pin[5], HIGH);
		}else if(time - preTime7 < Onkai6){
			digitalWrite(_pin[5], LOW);
		}else{
			preTime7 = time;
		}
		if (time - preTime8 < Onkai7 / 2) {
			digitalWrite(_pin[6], HIGH);
		}
		else if(time - preTime8 < Onkai7){
			digitalWrite(_pin[6], LOW);
		}else{
			preTime8 = time;
		}
		if (time - preTime9 < Onkai8 / 2) {
			digitalWrite(_pin[7], HIGH);
		}
		else if(time - preTime9 < Onkai8){
			digitalWrite(_pin[7], LOW);
		}else{
			preTime9 = time;
		}
		if (time - preTime10 < Onkai9 / 2) {
			digitalWrite(_pin[8], HIGH);
		}
		else if(time - preTime10 < Onkai9){
			digitalWrite(_pin[8], LOW);
		}else{
			preTime10 = time;
		}
		if (time - preTime11 < Onkai10 / 2) {
			digitalWrite(_pin[9], HIGH);
		}
		else if(time - preTime11 < Onkai10){
			digitalWrite(_pin[9], LOW);
		}else{
			preTime11 = time;
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