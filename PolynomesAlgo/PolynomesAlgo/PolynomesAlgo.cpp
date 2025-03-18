#include <iostream>
#include "Monome.h"
#include "Polynome.h"

int main()
{
    Polynome* P = new Polynome();
    Polynome* Q = new Polynome();

    Monome* a = new Monome(2, 1);
    Monome* b = new Monome(4, 0);
    Monome* c = new Monome(5, 8);
    Monome* d = new Monome(9, 3);
    Monome* e = new Monome(1, 3);

    Monome* f = new Monome(8, 5);
    Monome* g = new Monome(3, 1);
    Monome* h = new Monome(9, 9);
    Monome* i = new Monome(4, 1);
    Monome* j = new Monome(2, 0);

    P->Add(a);
    P->Add(b);
    P->Add(c);
    P->Add(d);
    P->Add(e);

    Q->Add(f);
    Q->Add(g);
    Q->Add(h);
    Q->Add(i);
    Q->Add(j);

    P->DisplayPolynome();
    Q->DisplayPolynome();
    P->AddPolynomes(Q);
    P->DisplayPolynome();
}