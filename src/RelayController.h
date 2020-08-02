#pragma once
#include "Arduino.h"

class Relay
{
public:
	Relay(int pin[], int n);
	void sing(unsigned int NoteList[]);
	void set(unsigned int index, unsigned int note)
	void rest(int msec);
private:
	int _pin[10];
	int _tmp;
	int Index;
	int Note;
};