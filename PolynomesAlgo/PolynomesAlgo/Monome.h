#pragma once
#include <iostream>

using namespace std;

class Monome
{
	//valeur, exposant, suivant
public:
	Monome(int value, int exposant);
	void AddMonomes(Monome* toAdd);

	int value;
	int exposant;
	Monome* next;
};

