#include <iostream>
#include "kattistime.h"
#include "date.hpp"
//#include "stripper.h"
#include "gregorian.hpp"
#include "julian.hpp"
//#include "calendar.cpp"

#include <iostream>
#include <assert.h>             // assert(b) ger felmeddelande om b falsk
#include <ctime>


using namespace std;

int main() {

    using namespace lab2;


    /*
     * För att använda kattis k_time skapar ni en t_time och anropar k_time med adressen till er t_time-variabel.
     * För att få ut datum lokalt kan ni anropa gmtime.
     */


    /*
    // Innan datumklasser instantieras
    time_t tp;
    time(&tp);
    set_k_time(tp);
    // -----------------------------------------------------------



    Julian tj;                  // ok: defaultkonstruktor ger dagens datum
    Gregorian gtoday;           // ok f�r gregorian ocks�
    cout << gtoday.week_day_name() << endl;
    cout << tj.week_day_name() << endl;

    std::cout << "Idag är det (Gregorian) " << gtoday << std::endl;
    std::cout << "Idag är det (Julian) " << tj << std::endl;
    assert(tj - gtoday == 0);
    //assert(tj - gtoday == 0);
    Gregorian tg(2006, 10, 31);
    Julian tg2(1900, 01, 01);
    //Gregorian(2000, Gregorian::October, 31);
    cout << "Test Greg: " << tg << endl;
    cout << "Test Jul: " << tg2 << endl;


    Date &j = tj;               // �tkomst av funktioner genom Dates interface
    Date &g = tg;
    Date &today = gtoday;

    {
        Julian j1;
        Date & d1 = j1;
        Julian j2(d1);
        Date * dp = &j2;
        Julian j3(*dp);
        //Gregorian g5(dp);
    }


    struct tm *t = gmtime(&tp);
    int year  = t->tm_year + 1900;
    int month = t->tm_mon + 1;      // m�naderna och dagarna
    int day   = t->tm_mday;         // indexerade fr�n ETT

    std::cout << "Testing constructors..." << std::endl;
    assert(today.year() == year &&          // r�tt initierad
           today.month() == month &&
           today.day() == day);
    assert(g.year() == 2006 &&              // r�tt initierad
           g.month() == 10 &&
           g.day() == 31);                  // obs! ettindexerade

    std::cout << "Testing access..." << std::endl;
    assert(g.days_per_week() == 7);         // r�tt antal dagar per vecka
    assert(j.days_per_week() == 7);         // r�tt antal dagar per vecka
    //assert(g.days_this_month() == 31);      // r�tt antal dagar denna m�nad
    assert(g.months_per_year() == 12);      // r�tt antal m�nader per �r
    assert(j.months_per_year() == 12);      // r�tt antal m�nader per �r
    assert(g.week_day() == 2); // r�tt veckodag

    std::cout << "Testing manipulation..." << std::endl;
    ++g;                                    // prefix �kning
    assert(g.week_day() == 3); // r�tt veckodag
    --g;                                    // prefix minskning
    assert(g.week_day() == 2); // r�tt veckodag
    g += 2;                                 // l�gg till tv� dagar
    assert(g.week_day() == 4); // r�tt veckodag
    g -= 3;                     // dra bort tre dagar

    g.add_month();              // l�gg till en m�nad
    g.add_month(-1);            // dra bort en m�nad
    g.add_year(10);             // l�gg till tio �r.

    std::cout << "Testing miscellaneous functions..." << std::endl;
    Julian jj(tj);              // kopieringskonstruktor
    const Gregorian gg;
    gg.year();                  // gg konstant, l�sa g�r bra
    g = gg;                     // tilldelning
    if(g == gg ||               // j�mf�relse
       g != gg ||               // j�mf�relse
       g < gg ||                // j�mf�relse
       g >= gg)                 // j�mf�relse
    {}

    std::cout << "Testing boundary violations";
    Gregorian temp(1900, 1, 1);
    Date &d = temp;

    // loopa �ver dagar och kolla att inga gr�nser �ver/underskrids
    for(int i = 0; i < 100000; ++i, ++d)
    {
        if(!(i % 5000))        // utskrift p� framsteg
        {
            std::cout << ".";
            flush(std::cout);
        }
        int m[] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        if(d.year() >= 1900 &&
           d.month() >= 1 && d.month() <= 12 &&
           d.day() >= 1 && d.day() <= m[d.month() - 1])
        {}
        else
        {
            std::cout << std::endl;
            std::cout << "boundary checks failed: " << std::endl;
            std::cout << d.year() << ", "
            << d.month() << ", "
            << d.day() << std::endl;
            return 1;
        }
    }
    std::cout << std::endl;

    std::cout << "Testing leap years..." << std::endl;
    // testa om skott�ren f�r sekelskiften fungerar som de ska
    for(int y = 1958; y < 2500; y += 100)
    {
        Gregorian temp(y, 2, 28);
        cout << temp << endl;
        Date &e = temp;
        cout << e << endl;
        ++e;
        cout << e << endl;
        // l�gg till en dag
        if((y % 400 == 0 && e.day() == 29) ||  // skottdag (obs! ETTindexerad)
           (y % 400 != 0 && e.day() == 1))     // ej skottdag
        {}
        else
        {
            std::cout << std::endl << "leap day test failed: " << std::endl;
            std::cout << e.year() << ", "
            << e.month() << ", "
            << e.day() << std::endl;
            return 1;
        }
    }

    std::cout << std::endl << "All tests were successful." << std::endl;

    lab2::Date * p1 = new Julian ();
    lab2::Date * p2 = new Gregorian (1900, 1, 1);
    *p1 = *p2;
    std::cout << *p1; // 1899-12-20
    delete p2;
    delete p1;


    std::cout << std::endl << "Testing Calendar" << std::endl;
    Calendar<Gregorian> cal;
    cal.set_date(2000, 12, 2);
    cal.add_event("Basketträning", 4, 12, 2000);

    cal.add_event("Basketträning", 11, 12, 2000);
    cal.add_event("Nyårsfrukost", 1, 1, 2001);
    cal.add_event("Första advent", 1); // år = 2000, månad = 12
    cal.add_event("Vårdagjämning", 20, 3); // år = 2000
    cal.add_event("Julafton", 24, 12);
    cal.add_event("Kalle Anka hälsar god jul", 24); // också på julafton
    cal.add_event("Julafton", 24); // En likadan händelse samma datum ska
// ignoreras och inte sättas in i kalendern
    cal.add_event("Min första cykel", 20, 12, 2000);
    cal.remove_event("Basketträning", 4);

    cout << endl;
    std::cout << cal << endl;

    // OBS! Vårdagjämning och första advent är
// före nuvarande datum och skrivs inte ut
    std::cout << "----------------------------------------" << std::endl;
    cal.remove_event("Vårdagjämning", 20, 3, 2000);
    cal.remove_event("Kalle Anka hälsar god jul", 24, 12, 2000);
    cal.set_date(2000, 11, 2);
    if (!cal.remove_event("Julafton", 24)) {
        std::cout << " cal.remove_event(\"Julafton\", 24) tar inte"<< std::endl << " bort något eftersom aktuell månad är november" << std::endl;
    }
    std::cout << "----------------------------------------" << std::endl;
    std::cout << cal;
     */
/*
    cout << "Testing Prefix..." << endl;
    Julian pref(1999, 2, 15);
    Julian pref2(2005, 8, 16);
    Gregorian greg(1999, 2, 15);
    Gregorian greg2(2005, 8, 16);
    cout << "Printing pref: " << pref.julian_day() << endl;
    cout << "Printing pref2: " << pref2.julian_day() << endl;
    cout << "Printing greg: " << greg.julian_day() << endl;
    cout << "Printing greg2: " << greg2.julian_day() << endl << endl;

    //++pref;
    //++greg;

    cout << "Testing operator-()..." << endl;
    int gg = pref - pref2;
    int gg2 = pref - greg;
    int gg3 = pref - greg2;
    //assert(pref - pref2 == );
    cout << "Printing differences..." << endl;
    cout << gg << endl;
    cout << gg2 << endl;
    cout << gg3 << endl << endl;


    cout << "Testing assignment..." << endl;
    Gregorian y(2006, 8, 1);
    Julian x;
    x = y;
    assert(x.year() == 2006 && x.month() == 7 && x.day() == 19);

*/
    Julian j(2006, 6, 10);
    //Julian j1;
    //Julian j2;
    //Gregorian g1;



    return 0;
 }