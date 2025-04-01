#include "Polynome.h"
#include <iostream>
#include <list>
#include <sstream>
#include <cstdlib>

using namespace std;

Polynome::Polynome() {

}

Polynome::~Polynome() {
    Monome* current = head;
    while (current != nullptr) {
        Monome* next = current->next;
        delete current; // Libère la mémoire du monôme actuel
        current = next;
        cout << "deleting" << endl;
    }
    head = nullptr; // Évite d'avoir un pointeur dangling
}

void Polynome::Add(Monome* newMonome) {
    if (newMonome->value == 0) {
        free(newMonome);
        return;
    }

    if (head == nullptr) {
        head = newMonome;
        return;
    }

    if (head->exposant == newMonome->exposant) {
        head->value += newMonome->value;
        if (head->value == 0) {
            Monome* toDel = head;
            head = head->next;
            free(toDel);
        }
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
        FreeSpace(prev, a);
        return;
    }

    if (a->next != nullptr) {
        if (a->next->exposant == newMonome->exposant) {
            a->next->value += newMonome->value;
            FreeSpace(a, a->next);
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

void Polynome::FreeSpace(Monome* prev, Monome* current) {
    if (current->value == 0)
    {
        prev->next = current->next;
        free(current);
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

        if (a->exposant == 0 && a->exposant != 1)
            cout << a->value;
        else if (a->exposant != 0 && a->exposant == 1)
            cout << a->value << "x";
        else cout << a->value << "x^" << a->exposant;

        if (a->next != nullptr && a->next->value > 0) cout << " + ";
        else if (a->next != nullptr && a->next->value < 0) cout << " ";

        a = a->next;
    }

    cout << endl;
}

void Polynome::InputMonome() {
    float value    = 0;
    float exposant = 0;
    float input    = 0;

    cout << "Enter a coefficient: ";
    value    = GetFloatInput();

    cout << "Enter an exposant: ";
    exposant = GetFloatInput();

    if (value == 0) {
        return;
    }

    Monome* newNode = new Monome(value, exposant);
    Add(newNode);
    DisplayPolynome();
}

float Polynome::GetFloatInput() {
    bool isValid = false;
    float input;

    while (!isValid) {
        cin >> input;
        if (!cin) {
            cout << "Not an float. Try again " << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else {
            isValid = true;
            return input;
        }
    }
}

void Polynome::InputPolynome() {
    cout << endl;
    InputMonome();
    cout << "Continue? Y/N ";
    char answer;
    cin >> answer;
    switch (toupper(answer))
    {
    default:
        return;
        break;
    case 'Y':
        InputPolynome();
        break;
    case 'N':
        break;
    }
}

Polynome* Polynome::AddPolynomes(Polynome* other) {
    Polynome* resultat = new Polynome();

    if (head == nullptr && other->head != nullptr) {
        resultat->head = other->head;
        cout << "Addition results: ";
        DisplayPolynome();
        return resultat;
    }
    else if (other->head == nullptr && head != nullptr) {
        other->head = head;
        cout << "Addition results: ";
        DisplayPolynome();
        return resultat;
    }
    else if (head == nullptr && other->head == nullptr) {
        cout << "Both polynomes are empty." << endl;
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
    return resultat;
    
}

Polynome* Polynome::MultiplyPolynomes(Polynome* other) {
    Polynome* resultat = new Polynome();

    if (head != nullptr && other->head == nullptr) {
        cout << "The second polynome is empty." << endl;
        return resultat;
    } else if (head == nullptr && other->head != nullptr) {
        cout << "The first polynome is empty." << endl;
        return resultat;
    } else if (head == nullptr && other->head == nullptr) {
        cout << "Both polynomes are empty." << endl;
        return resultat;
    }

    Monome* a = head;
    Monome* b = other->head;
    float value;
    float exposant;

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
    return resultat;
}

Polynome* Polynome::DerivePolynome() {
    Polynome* DerivedPolynome = new Polynome();

    Monome* a = head;

    while (a != nullptr) { 
        Monome* b = a->DeriveMonome();
        if (b->value != 0) DerivedPolynome->Add(b);
        a = a->next;
    }
    return DerivedPolynome;
}

Polynome* Polynome::SubstractPolynomes(Polynome* other) {
    Polynome* resultat = new Polynome();

    if (head == nullptr && other->head != nullptr) {
        resultat->head = other->head;
        cout << "Substract results: ";
        return resultat;
    }
    else if (other->head == nullptr && head != nullptr) {
        other->head = head;
        cout << "Substract results: ";
        return resultat;
    }
    else if (head == nullptr && other->head == nullptr) {
        cout << "Both polynomes are empty." << endl;
        return resultat;
    }

    Monome* a = head;
    while (a != nullptr) {
        Monome* copy = new Monome(a->value, a->exposant);
        resultat->Add(copy);
        a = a->next;
    }
     a = other->head;
    while (a != nullptr) {
        Monome* copy = new Monome(a->value * -1, a->exposant);
        resultat->Add(copy);
        a = a->next;
    }

    delete a;
    return resultat;
}

Polynome* Polynome::Primitive() {
    Polynome* resultat = new Polynome();

    Monome* a = head;
    while (a != nullptr) {
        Monome* primitiveMonome = a->PrimitiveMonome();
        resultat->Add(primitiveMonome);
        a = a->next;
    }
    return resultat;
}

Polynome* Polynome::Duplicate() {
    Polynome* copy = this;
    return copy;
}

void Polynome::DisplayPolynomes(list<Polynome*> polynomes) {
    int i = 1;
    for (Polynome* p : polynomes) {
        cout << "polynome " << i++ << " : ";
        p->DisplayPolynome();
    }
}