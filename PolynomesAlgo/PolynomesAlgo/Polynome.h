#pragma once
#include "Monome.h"
#include <iostream>

using namespace std;

class Polynome
{
private:
	void AddToEndOfList(Monome* newMonome);
	void AddAfterMonome(Monome* monome, Monome* toAdd);
	void InputMonome();
	int  GetIntInput();
	void FreeSpace(Monome* prev, Monome* current);
public:
	Polynome();
	void DisplayPolynome();
	void Add(Monome* newMonome);
	void InputPolynome();
	Polynome* AddPolynomes(Polynome* other);
	Polynome* MultiplyPolynomes(Polynome* other);

	Monome* head;
};

