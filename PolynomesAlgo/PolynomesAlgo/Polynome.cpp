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

Polynome* Polynome::AddPolynomes(Polynome* other) {
    Polynome* resultat = new Polynome();

    if (head == nullptr && other->head != nullptr) {
        resultat->head = other->head;
        cout << "Résultat de l'addition: ";
        DisplayPolynome();
        return resultat;
    }
    else if (other->head == nullptr && head != nullptr) {
        other->head = head;
        cout << "Résultat de l'addition: ";
        DisplayPolynome();
        return resultat;
    }
    else if (head == nullptr && other->head == nullptr) {
        cout << "Les deux polynomes sont vides." << endl;
        return resultat;
    }

    Monome* a = other->head;
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

    delete a;
    resultat->DisplayPolynome();
    return resultat;
    
}

Polynome* Polynome::MultiplyPolynomes(Polynome* other) {
    Polynome* resultat = new Polynome();

    if (head != nullptr && other->head == nullptr) {
        cout << "Le deuxième polynome est vide" << endl;
        return resultat;
    } else if (head == nullptr && other->head != nullptr) {
        cout << "Le premier polynome est vide" << endl;
        return resultat;
    } else if (head == nullptr && other->head == nullptr) {
        cout << "Les deux polynomes est vide" << endl;
        return resultat;
    }

    Monome* a = head;
    Monome* b = other->head;
    int value;
    int exposant;

    while (a != nullptr) {
        while (b != nullptr) {
            value = a->value * b->value;
            exposant = a->exposant + b->exposant;

            Monome* c = new Monome(value, exposant);
            resultat->Add(c);

            b = b->next;
        }

        a = a->next;
        b = other->head;
    }
    resultat->DisplayPolynome();
    return resultat;
}

