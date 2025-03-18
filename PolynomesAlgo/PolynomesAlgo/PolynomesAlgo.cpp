#include <iostream>
#include <list>
#include <sstream>
#include "Monome.h"
#include "Polynome.h"

using namespace std;

int main()
{
    Polynome* P = new Polynome();
    Polynome* Q = new Polynome();

    Monome* a = new Monome(3, 0);
    Monome* b = new Monome(2, 1);
    Monome* c = new Monome(3, 3);

    Monome* f = new Monome(2, 1);
    Monome* g = new Monome(3, 3);

    P->Add(a);
    P->Add(b);
    P->Add(c);

    Q->Add(f);
    Q->Add(g);

    P->DisplayPolynome();
    Q->DisplayPolynome();
    P->SubstractPolynomes(Q);
    P->DisplayPolynome();

    //Polynome* R = new Polynome();
    //R->InputPolynome();
}