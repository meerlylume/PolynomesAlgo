#pragma once
#include <iostream>

using namespace std;

class Monome
{
	//valeur, exposant, suivant
public:
	Monome(float value, float exposant);
	Monome* PrimitiveMonome();

	float value;
	float exposant;
	Monome* next;
};

