#pragma once
#include "Monome.h"
#include <list>
#include <iostream>

using namespace std;

class Polynome
{
private:
	void AddToEndOfList(Monome* newMonome);
	void AddAfterMonome(Monome* monome, Monome* toAdd);
	void InputMonome();
	float GetFloatInput();
	int GetIntInput();
	void FreeSpace(Monome* prev, Monome* current);
public:
	Polynome();
	~Polynome();
	void DisplayPolynome();
	void DisplayPolynomes(list<Polynome*> polynomes);
	void Add(Monome* newMonome);
	void InputPolynome();
	Polynome* AddPolynomes(Polynome* other);
	Polynome* SubstractPolynomes(Polynome* other);
	Polynome* MultiplyPolynomes(Polynome* other);
	Polynome* DerivePolynome();
	Polynome* Primitive();
	Polynome* Duplicate();

	Monome* head;
};

