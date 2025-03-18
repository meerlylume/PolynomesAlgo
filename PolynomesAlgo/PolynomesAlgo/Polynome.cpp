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
    while (a != nullptr && newMonome->exposant > a->exposant) {
        prev = a;
        a = a->next;
    }

    if (a != nullptr) 
    {
        if (newMonome->exposant == a->exposant) {
            a->value += newMonome->value;
        }
        else if ( a->next != nullptr && newMonome->exposant == a->next->exposant) {
            a->next->value += newMonome->value;
        }
        else if (newMonome->exposant > a->exposant) {
            newMonome->next = a->next;
            a->next = newMonome;
        }
        else {
            newMonome->next = a;
            prev->next = newMonome;
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
    toAdd->next = monome->next;
    monome->next = toAdd;
}

void Polynome::DisplayPolynome() {
    if (head == nullptr) {
        cout << "Polynome vide" << endl;
    }

    Monome* a = head;
    while (a != nullptr) {
        if (a->next != nullptr) cout << a->value << "x^" << a->exposant << " + ";
        else cout << a->value << "x^" << a->exposant;
        a = a->next;
    }

    cout << endl;
}

void Polynome::AddPolynomes(Polynome* p) {
    if (head == nullptr && p->head != nullptr) {
        head = p->head;
        cout << "Résultat de l'addition: ";
        DisplayPolynome();
        return;
    }
    else if (p->head == nullptr && head != nullptr) {
        p->head = head;
        cout << "Résultat de l'addition: ";
        DisplayPolynome();
        return;
    }

    /*Polynome* resultat = new Polynome();
    Monome* a = p->head;
    while (a != nullptr) {
        Monome* copy = new Monome(a->value, a->exposant);
        cout << "adding" << endl;
        resultat->Add(copy);
        a = a->next;
    }
    a = head;
    while (a != nullptr) {
        Monome* copy = new Monome(a->value, a->exposant);
        cout << "adding" << endl;
        resultat->Add(copy);
        a = a->next;
    }
    resultat->DisplayPolynome();*/

    Monome* a = p->head;
    while (a != nullptr) {
        Monome* copy = new Monome(a->value, a->exposant);
        Add(copy);
        a = a->next;
    }
    DisplayPolynome();
    
}