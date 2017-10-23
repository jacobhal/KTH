//
// Created by Jacob Hallman on 21/05/16.
//

#include "julian.hpp"

namespace lab2 {
    using namespace std;

    Julian::Julian() : Date() {
        // Convert from gregorian date to jdn and then set the date as a julian one
        this->julian_day_number = Date::calc_julian_day_number(year(), month(), day());
        from_jdn_to_date();
        //cout << "Julian day number i default konstruktor i julian: " << julian_day_number << endl;
    }

    Julian::Julian(int year, int month, int day) : Date(year, month, day) { // Call Date constructor with initialization list
        if(!valid_date(year, month, day)) {
            throw(std::invalid_argument("Invalid date"));
        } else {
            this->julian_day_number = calc_julian_day_number(year, month, day);
            //cout << "Julian day number i parameteriserad konstruktor: " << julian_day_number << endl;
            from_jdn_to_date();
        }
    }

    // Copy
    Julian::Julian (const Date& date) {
        //cout << "Julian copy" << endl;
        this->julian_day_number = date.julian_day();
        from_jdn_to_date();
    }

    Julian::~Julian() {
        cout << "Destructor" << endl;
        //delete this;
        // TODO
    }

    // Overload increment and decrement operators
    Julian Julian::operator++(int) {
        //cout << "Postfix increment" << endl;
        Julian tmp(*this);
        Date::operator++(); // prefix-increment this instance
        return tmp;   // return value before increment
    };
    Julian Julian::operator--(int) {
        Julian tmp(*this);
        Date::operator--(); // prefix-increment this instance
        return tmp;   // return value before increment
    }


    void Julian::from_jdn_to_date() {
        int y = 4716;
        int j = 1401;
        int m = 2;
        int n = 12;
        int r = 4;
        int p = 1461;
        int v = 3;
        int u = 5;
        int s = 153;
        int w = 2;
        int B = 274277;
        int C = -38;

        int f = julian_day_number + j;
        int e = r * f + v;
        int g = e % p / r;
        int h = u * g + w;
        int D = (h % s) / u + 1;
        int M = ((h / s + m) % n) + 1;
        int Y = (e / p) - y + (n + m - M) / n;

        this->y = Y;
        this->m = M;
        this->d = D;
    }

    int Julian::calc_julian_day_number(int year, int month, int day) {
        int a = (14 - month) / 12;
        int y = year + 4800 - a;
        int m = month + 12*a- 3;
        int JDN = day + (153*m + 2) / 5 + 365*y + y/4 - 32083;
        return JDN;
    }
}

