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
    Monome* a = head;
    while (a != nullptr) {
        if (a->next != nullptr) cout << a->value << "x^" << a->exposant << " + ";
        else cout << a->value << "x^" << a->exposant;
        a = a->next;
    }

    cout << endl;
}

void Polynome::InputMonome() {
    int value    = 0;
    int exposant = 0;
    int input    = 0;

    cout << "Enter a coefficient: ";
    value    = GetIntInput();

    cout << "Enter an exposant: ";
    exposant = GetIntInput();

    if (value == 0) {
        Menu();
        return;
    }

    Monome* newNode = new Monome(value, exposant);
    Add(newNode);
    DisplayPolynome();
}

int Polynome::GetIntInput() {
    bool isValid = false;
    int input;

    while (!isValid) {
        cin >> input;
        if (!cin) {
            cout << "Not an integer. Try again " << endl;
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

Monome* Polynome::DeriveMonome(Monome* monome) {
    int value;
    int exposant;

    value    = monome->value * monome->exposant;
    exposant = monome->exposant - 1;

    Monome* derivedMonome = new Monome(value, exposant);

    return derivedMonome;
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
        cout << "R�sultat de l'addition: ";
        DisplayPolynome();
        return resultat;
    }
    else if (other->head == nullptr && head != nullptr) {
        other->head = head;
        cout << "R�sultat de l'addition: ";
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
        cout << "Le deuxi�me polynome est vide" << endl;
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

void Polynome::DerivePolynome() {
    Polynome* DerivedPolynome = new Polynome();

    Monome* a = head;

    while (a != nullptr) { 
        Monome* b = DeriveMonome(a);
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
