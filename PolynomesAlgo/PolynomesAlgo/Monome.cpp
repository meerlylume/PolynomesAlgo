#include "Monome.h"
#include <iostream>

using namespace std;

Monome::Monome(float value, int exposant) : value(value), exposant(exposant) {

}

Monome* Monome::PrimitiveMonome() {
	float value = 0;
	int exposant = 0;

	exposant = this->exposant + 1;
	value = this->value / exposant;

	Monome* primitive = new Monome(value, exposant);
	return primitive;
}

Monome* Monome::DeriveMonome() {
	float newValue;
	int newExposant;

	newValue    = value * exposant;
	newExposant = exposant - 1;

	Monome* derivedMonome = new Monome(newValue, newExposant);

	return derivedMonome;
}