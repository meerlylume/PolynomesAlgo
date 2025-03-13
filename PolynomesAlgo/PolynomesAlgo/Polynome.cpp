#include "Polynome.h"#include "Polynome.h"
#include <iostream>

using namespace std;

Polynome::Polynome() {

}

void Polynome::Add(Monome* newMonome) {
    if (head == nullptr) {
        head = newMonome;
        return;
    }

    if (head->exposant == newMonome->exposant) {
        head->value += newMonome->value; //change later to factorise into Monome (?)
        return;
    }
    if (head->exposant > newMonome->exposant) {
        newMonome->next = head;
        head = newMonome;
        return;
    }

    Monome* a = head;
    Monome* prev = nullptr;
    while (a->next != nullptr && a->exposant < newMonome->exposant - 1) {
        prev = a;
        a = a->next;
    }

    if (a->exposant == newMonome->exposant) {
        a->value += newMonome->value;
        return;
    }

    if (a->next != nullptr) {
        if (a->next->exposant == newMonome->exposant) {
            a->next->value += newMonome->value;
        }
        else {
            AddAfterMonome(a, newMonome);
        }
    }
    else {
        if (a->exposant > newMonome->exposant) {
            AddAfterMonome(prev, newMonome);
            return;
        }
        AddToEndOfList(newMonome);
    }
}

void Polynome::AddToEndOfList(Monome* newMonome) {
    Monome* a = head;

    while (a->next != nullptr) { a = a->next; }

    a->next = newMonome;
}

void Polynome::AddAfterMonome(Monome* monome, Monome* toAdd) {
    toAdd->next = monome->next;
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