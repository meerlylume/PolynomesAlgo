#include <iostream>
#include <list>
#include <sstream>
#include "Monome.h"
#include "Polynome.h"

using namespace std;

int main()
{
    /*
    Polynome* P = new Polynome();
    Polynome* Q = new Polynome();

    Monome* a = new Monome(3, 0);
    Monome* b = new Monome(-4, 1);
    Monome* c = new Monome(4, 2);
    Monome* d = new Monome(-7, 3);

    Monome* f = new Monome(4, 0);
    Monome* g = new Monome(-4, 2);
    Monome* h = new Monome(7, 3);
    Monome* i = new Monome(5, 4);

    P->Add(a);
    P->Add(b);
    P->Add(c);
    P->Add(d);

    Q->Add(f);
    Q->Add(g);
    Q->Add(h);
    Q->Add(i);

    P->DisplayPolynome();
    Q->DisplayPolynome();
    P->AddPolynomes(Q);
    P->DisplayPolynome();
    */

    Polynome* R = new Polynome();
    R->InputPolynome();
}