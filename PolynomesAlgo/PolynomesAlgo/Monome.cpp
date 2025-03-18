#include "Monome.h"
#include <iostream>

using namespace std;

Monome::Monome(float value, float exposant) : value(value), exposant(exposant) {

}

Monome* Monome::PrimitiveMonome() {
	float value = 0;
	float exposant = 0;

	exposant = this->exposant + 1;
	value = this->value / exposant;

	Monome* primitive = new Monome(value, exposant);
	return primitive;
}
