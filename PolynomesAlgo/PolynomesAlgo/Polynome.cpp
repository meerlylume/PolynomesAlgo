#include "Polynome.h"
#include <iostream>
#include <list>
#include <sstream>
#include <cstdlib>

using namespace std;

Polynome::Polynome() {

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
        head->value += newMonome->value; //change later to factorise into Monome (?)
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
        if (a->next != nullptr) cout << a->value << "x^" << a->exposant << " + ";
        else cout << a->value << "x^" << a->exposant;
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
        Menu();
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
        Menu();
        break;
    }
}

void Polynome::Menu() {
    cout << "What will you do ? " << endl;
    cout << "A - Add a new Monome " << endl;
    cout << "B - Derive your Polynome " << endl;
    cout << "X - Exit " << endl;

    char answer;
    cin >> answer;
    switch (toupper(answer))
    {
    default:
        Menu();
        break;
    case 'A':
        InputPolynome();
        break;
    case 'B':
        DerivePolynome();
        break;
    case 'X':
        return;
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
    resultat->DisplayPolynome();
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
    resultat->DisplayPolynome();
    return resultat;
}

void Polynome::DerivePolynome() {
    Polynome* DerivedPolynome = new Polynome();

    Monome* a = head;

    while (a != nullptr) { 
        Monome* b = a->DeriveMonome();
        if (b->value != 0) DerivedPolynome->Add(b);
        a = a->next;
    }

    head = DerivedPolynome->head;

    DisplayPolynome();
    Menu();
}

Polynome* Polynome::SubstractPolynomes(Polynome* other) {
    Monome* z = other->head;

    while (z != nullptr) {
        z->value *= -1;
        Add(z);
        z = z->next;
    }

    return this;
}

Polynome* Polynome::Primitive() {
    Polynome* resultat = new Polynome();

    Monome* a = head;
    while (a != nullptr) {
        Monome* primitiveMonome = a->PrimitiveMonome();
        resultat->Add(primitiveMonome);
        cout << primitiveMonome->value << "||" << primitiveMonome->exposant << endl;
        a = a->next;
    }
    resultat->DisplayPolynome();
    return resultat;
}

Polynome* Polynome::Duplicate() {
    Polynome* copy = this;
    return copy;
}