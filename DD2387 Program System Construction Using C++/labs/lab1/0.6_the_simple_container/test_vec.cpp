#include <iostream>
#include <stdexcept>
#include "kth_cprog_simple_container.hpp"     // inkludera din headerfil h�r

using namespace std;

int main()
{
    // N�gra saker som ska fungera:
    //UIntVector a(7);           // initiering med 7 element
    //UIntVector b(a);           // kopieringskonstruktor 
    //UIntVector c = a;          // kopieringskonstruktor 

/*
    UIntVector balle = {1, 2, 3};
    UIntVector cock(0);
    balle = cock;

    for(int i = 0; i < cock.size(); ++i) {
        cout << "cock[" << i << "]" << cock[i] << endl;
    }

     for(int i = 0; i < balle.size(); ++i) {
        cout << "balle[" << i << "]" << balle[i] << endl;
    }
*/
    // Upprepar testsekvensen p� kattis s� gott som m�jligt
    UIntVector a = {1, 2, 3};
    //UIntVector b(10);
    cout << "a" << ".size(): " << a.size() << endl;
    UIntVector c(0);
    a = c;
    /*
    for(int i = 0; i < a.size(); ++i) {
        cout << "WTF" << endl;
        if(a[i] == c[i]) {
            cout << "Samma" << endl;
        }
    }
    */
    //b = a;
    cout << "a" << ".size(): " << a.size() << endl;
    //cout << "b" << ".size(): " << b.size() << endl;
    cout << "c" << ".size(): " << c.size() << endl;
    /*
    a[0] = 10;
    b[1] = 11;
    c[2] = 12;
    cout << "a[0]" << a[0] << endl << "b[1]" << b[1] << endl << "c[2]" << c[2] << endl;
    */
    a.reset();
    cout << "a" << ".size(): " << a.size() << endl;
    //c = std::move(a); // Orsakar minnesl�cka

    cout << "c" << ".size(): " << c.size() << endl;
    cout << "a" << ".size(): " << a.size() << " SKA NU VARA 0" << endl;


    /*


    cout << "i_l.size(): " << i_l.size() << endl;
 
    UIntVector tmp = std::move(i_l);
    for(int i = 0; i < tmp.size(); ++i) {
        cout << "tmp[" << i << "]: " << tmp[i] << endl;
    }
    cout << "tmp.size(): " << tmp.size() << endl;
    cout << "i_l.size(): " << i_l.size() << endl; // Seems to work?
    if(i_l.size() == 0) {
        cout << "DEN �R JU 0" << endl;
    }
    */
    
/*
    a = b;                 // tilldelning genom kopiering
    a[5] = 7;              // tilldelning till element

    const UIntVector e(10);    // konstant objekt med 10 element

    int i = e[5];          // const int oper[](int) const k�rs
    i = a[0];              // vektorn �r nollindexerad
    i = a[5];              // int oper[](int) k�rs

    
    a[5]++;                // �ka v�rdet till 8


    try {
        i = e[10];             // f�rs�ker h�mta element som ligger utanf�r e
    } catch (std::out_of_range e) {
        std::cout << e.what() << std::endl;
    }

    UIntVector abc = {1, 2, 3};
    */
#if 0
    // Diverse saker att testa
    e[5] = 3;              // fel: (kompilerar ej) tilldelning till const
    b = b;                 // hmm: se till att inte minnet som skall beh�llas frig�rs
#endif


    return 0;
}
