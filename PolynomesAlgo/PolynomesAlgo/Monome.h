#pragma once
#include <iostream>

using namespace std;

class Monome
{
	//valeur, exposant, suivant
public:
	Monome(float value, int exposant);
	Monome* PrimitiveMonome();
	Monome* DeriveMonome();

	float value;
	int exposant;
	Monome* next;
};

