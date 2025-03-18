#include "Polynome.h"#include "Polynome.h"
#include <iostream>

using namespace std;

Polynome::Polynome() {

}

void Polynome::Add(Monome* newMonome) {
    if (newMonome->value == 0) {
        return;
    }

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
            FreeSpace(prev, a);
        }
        else if ( a->next != nullptr && newMonome->exposant == a->next->exposant) {
            a->next->value += newMonome->value;
            FreeSpace(a, a->next);
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

void Polynome::FreeSpace(Monome* prev, Monome* current) {
    if (current->value == 0)
    {
        prev->next = current->next;
        delete current;
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

Polynome* Polynome::AddPolynomes(Polynome* p) {
    Polynome* resultat = new Polynome();

    if (head == nullptr && p->head != nullptr) {
        resultat->head = p->head;
        cout << "Résultat de l'addition: ";
        DisplayPolynome();
        return resultat;
    }
    else if (p->head == nullptr && head != nullptr) {
        p->head = head;
        cout << "Résultat de l'addition: ";
        DisplayPolynome();
        return resultat;
    }
    else if (head == nullptr && p->head == nullptr) {
        cout << "Les deux polynomes sont vides." << endl;
        return resultat;
    }

    Monome* a = p->head;
    while (a != nullptr) {
        Monome* copy = new Monome(a->value, a->exposant);
        resultat->Add(copy);
        a = a->next;
    }
    a = head;
    while (a != nullptr) {
        Monome* copy = new Monome(a->value, a->exposant);
        resultat->Add(copy);
        a = a->next;
    }

    resultat->DisplayPolynome();
    return resultat;
    
}