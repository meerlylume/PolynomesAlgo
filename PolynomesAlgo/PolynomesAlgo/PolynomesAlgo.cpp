#include <iostream>
#include <list>
#include <sstream>
#include "Monome.h"
#include "Polynome.h"

using namespace std;

int main() {
    list<Polynome*> polynomes; // Stores the polynomials created by the user
    bool running = true;
    char choice;


    while (running) {
        cout << "\n==== Main Menu ====\n";
        cout << "1 - Create a new polynomial\n";
        cout << "2 - Display existing polynomials\n";
        cout << "3 - Add two polynomials\n";
        cout << "4 - Subtract two polynomials\n";
        cout << "5 - Multiply two polynomials\n";
        cout << "6 - Calculate the derivative of a polynomial\n";
        cout << "7 - Calculate the integral of a polynomial\n";
        cout << "8 - Delete one or more polynomials\n";
        cout << "9 - Quit\n";
        cout << "Your choice: ";

        cin >> choice;
        cin.ignore();


        switch (choice) {
        case '1': 
        {
            Polynome* p = new Polynome();
            p->InputPolynome();
            polynomes.push_back(p);
            cout << "Polynomial added!" << endl;
            break;
        }
        case '2': 
        {
            int i = 1;
            for (Polynome* p : polynomes) {
                cout << "Polynomial " << i++ << " : ";
                p->DisplayPolynome();
            }
            break;
        }
        case '3':
        case '4':
        case '5': 
        {
            if (polynomes.size() < 2) {
                cout << "You need at least 2 polynomials to perform this operation." << endl;
                break;
            }

            int i = 1;
            for (Polynome* p : polynomes) {
                cout << "Polynomial " << i++ << " : ";
                p->DisplayPolynome();
            }

            int p1, p2;
            bool validInput = false;
            while (!validInput) {
                cout << "Choose two polynomials (1 to " << polynomes.size() << ") : ";
                cin >> p1 >> p2;

                if (cin.fail() || p1 < 1 || p2 < 1 || p1 > polynomes.size() || p2 > polynomes.size()) {
                    cout << "Invalid input. Please choose two different valid indices within the range (1 to " << polynomes.size() << ")." << endl;
                    cin.clear(); 
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                }
                else {
                    validInput = true; 
                }
            }

            auto it1 = next(polynomes.begin(), p1 - 1);
            auto it2 = next(polynomes.begin(), p2 - 1);

            Polynome* res;
            if (choice == 3) {
                res = (*it1)->AddPolynomes(*it2);
                res->DisplayPolynome();
            }
            else if (choice == 4) {
                res = (*it1)->SubstractPolynomes(*it2);
                res->DisplayPolynome();
            }
            else {
                res = (*it1)->MultiplyPolynomes(*it2);
                res->DisplayPolynome();
            }

            polynomes.push_back(res);
            cout << "Result added to the list of polynomials." << endl;
            break;
        }
        case '6':
        case '7': 
        {
            if (polynomes.empty()) {
                cout << "No polynomial available." << endl;
                break;
            }

            int i = 1;
            for (Polynome* p : polynomes) {
                cout << "Polynomial " << i++ << " : ";
                p->DisplayPolynome();
            }
            int p;
            bool validInput = false;
            while (!validInput) {
                cout << "Choose a polynomial (1 to " << polynomes.size() << ") : ";
                cin >> p ;

                
                if (cin.fail() || p < 1 || p > polynomes.size()) {
                    cout << "Invalid input. Please choose a different valid indice within the range (1 to " << polynomes.size() << ")." << endl;
                    cin.clear(); 
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                }
                else {
                    validInput = true; 
                }
            }

            auto it = next(polynomes.begin(), p - 1);
            Polynome* res = (choice == 6) ? (*it)->DerivePolynome() : (*it)->Primitive();
            res->DisplayPolynome();
            polynomes.push_back(res);
            break;
        }
        case '8':
        {
            if (polynomes.empty()) {
                cout << "There are no polynomials to delete." << endl;
                break;
            }

            bool continuer = true;
            while (continuer) {
                cout << "\nExisting polynomials: " << endl;
                int i = 1;
                for (Polynome* p : polynomes) {
                    cout << "Polynomial " << i++ << " : ";
                    p->DisplayPolynome();
                }

                int p;
                bool validInput = false;

                while (!validInput) {
                    cout << "Enter the number of the polynomial to delete (or 0 to stop): ";
                    cin >> p;

                    if (p == 0) {
                        validInput = true; 
                        continuer = false; 
                        break;
                    }

                    else if (cin.fail() || p < 1 || p > polynomes.size()) {
                        cout << "Invalid input. Please choose a valid index within the range (1 to " << polynomes.size() << ")." << endl;
                        cin.clear(); 
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                    }
                    else {
                        validInput = true; 
                    }
                }

                
                if (validInput && p != 0) {
                    auto it = next(polynomes.begin(), p - 1);
                    delete* it; 
                    polynomes.erase(it); 
                    cout << "Polynomial successfully deleted!" << endl;
                }
            }
            break;
        }
        case '9':
            cout << "Goodbye!" << endl;
            running = false;
            break;
        default:
            cout << "Invalid option, please try again." << endl;
            cin >> choice;
            break;
        }
    }

    return 0;
}
