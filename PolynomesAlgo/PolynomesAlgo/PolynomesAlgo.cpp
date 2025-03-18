#include <iostream>
#include <list>
#include <sstream>
#include "Monome.h"
#include "Polynome.h"
#include "Polist.h"

using namespace std;

int main()
{
    Polist* polist = new Polist();

    Polynome* R = new Polynome();
    polist->head = R;
    R->InputPolynome();
}