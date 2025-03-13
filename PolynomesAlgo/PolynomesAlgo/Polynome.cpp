#include "Polynome.h"
#include <iostream>

using namespace std;

Polynome::Polynome() {

}

void Polynome::Add(Monome* newMonome) {
	if (head == nullptr) {
		head = newMonome;
		return;
	}

	if (head->exposant == newMonome->exposant) head->value += newMonome->value; //change later to factorise into Monome (?)
	if (head->exposant > newMonome->exposant) {
		newMonome->next = head;
		head = newMonome;
		return;
	}

	Monome* a = head;
	while (a->next != nullptr && a->exposant < newMonome->exposant-1) {
		a = a->next;
	}
	if (a->next != nullptr) { 
		if (a->next->exposant == newMonome->exposant) {
			a->next->value += newMonome->value; //change later to factorise into Monome
			//cout << "a->next->exposant: " << a->next->exposant << " | newMonome->exposant: " << newMonome->exposant << " |||| ";
		}
		else {
			AddAfterMonome(a, newMonome);
			cout << "AddAfterMonome";
		}
	}
	else {
		AddToEndOfList(newMonome);
	}
}

void Polynome::AddToEndOfList(Monome* newMonome) {
	Monome* a = head;

	while (a->next != nullptr) { a = a->next; }

	a->next = newMonome;
}

void Polynome::AddAfterMonome(Monome* monome, Monome* toAdd) {
	toAdd->next  = monome->next;
	monome->next = toAdd;
}

void Polynome::DisplayPolynome() {
	Monome* a = head;
	while (a != nullptr) {
		if (a->next != nullptr) cout << a->value << "x^" << a->exposant << " + ";
		else cout << a->value << "x^" << a->exposant;
		a = a->next;
	}

	cout << endl;
}