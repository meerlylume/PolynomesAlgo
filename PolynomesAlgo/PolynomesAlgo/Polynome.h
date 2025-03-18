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
public:
	Polynome();
	void DisplayPolynome();
	void Add(Monome* newMonome);
	void AddPolynomes(Polynome* other);
	void InputPolynome();

	Monome* head;
};

