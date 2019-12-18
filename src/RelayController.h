#pragma once
#include "Arduino.h"

class Relay
{
public:
	Relay(int pin[], int n);
	void sing(unsigned int part1, unsigned int ompu, unsigned int tmp);
	void sing(unsigned int part1, unsigned int part2, unsigned int ompu, unsigned int tmp);
	void sing(unsigned int part1, unsigned int part2, unsigned int part3, unsigned int part4, unsigned int ompu, unsigned int tmp);
	void sing(unsigned int part1, unsigned int part2, unsigned int part3, unsigned int part4, unsigned int part5, unsigned int ompu, unsigned int tmp);
	void sing(unsigned int Onkai1, unsigned int Onkai2, unsigned int Onkai3, unsigned int Onkai4, unsigned int Onkai5, unsigned int Onkai6, unsigned int Onkai7, unsigned int Onkai8, unsigned int Onkai9, unsigned int Onkai10, unsigned int Ompu, unsigned int tmp);
	void rest(int msec);
private:
	int _pin[10];
	int _tmp;
};