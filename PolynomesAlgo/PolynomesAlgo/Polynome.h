#pragma once
#include "Monome.h"
#include <iostream>

using namespace std;

class Polynome
{
private:
	void AddToEndOfList(Monome* newMonome);
	void AddAfterMonome(Monome* monome, Monome* toAdd);
public:
	Polynome();
	void DisplayPolynome();
	void Add(Monome* newMonome);

	Monome* head;
};

