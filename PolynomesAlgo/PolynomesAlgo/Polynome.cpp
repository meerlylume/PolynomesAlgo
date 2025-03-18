#include "Polynome.h"
#include <iostream>
#include <list>
#include <sstream>

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

void Polynome::AddPolynomes(Polynome* other) {
    Monome* z = other->head;

    while (z != nullptr) {
        Add(z);
        z = z->next;
    }
}

void Polynome::InputMonome() {
    //Handle both x and x^ to account for user error

    cout << "Enter a monome: ";
    string input;
    cin >> input;
    cout << endl;

    //Declare vars
    int value       = 0;
    int exposant    = 0;
    bool doingValue = true;
    string temp     = "";

    //Parse through and get values

    //HANDLE MONKEY TEST
    for (int i = 0; i < input.length(); i++)
    {
        cout << i << " / " << input.length() << " : " << input[i] << endl;
        // Found + or -
        if (input[i] == '+' || input[i] == '-') { //HANDLE * AND /
            cout << "Found + or - " << endl;
            // If input[0]
            if (i == 0 || input[i - 1] == 'x') {
                temp += input[i];
            }
            // Any other case
            else {
                // Add what's in temp so you can start up the next addition
                if (doingValue) value += stoi(temp);
                else         exposant += stoi(temp);

                temp  = "";
                temp += input[i];
            }
        }
        // Found x
        else if (input[i] == 'x') {
            cout << "Found x at " << i << endl;
            if (!doingValue) {
                cout << "Exposant cannot have an x" << endl;
                return;
            }
            else {
                cout << "Setting value to temp: " << temp << endl;
                value     += stoi(temp);
                temp       = "";
                doingValue = false;
                cout << "Now doing exposants " << endl;
                cout << endl;
            }
        }
        else {
            temp += input[i];
            cout << "Adding " << input[i] << " to temp." << endl;
        }
    }

    if (temp == "") exposant  = 0;
    else            exposant += stoi(temp);

    //Create monome with the parsed values and add it to the polynome
    Monome* newNode = new Monome(value, exposant);
    Add(newNode);
    DisplayPolynome();
}