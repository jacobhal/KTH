//
// Created by Jacob Hallman on 21/05/16.
//

#ifndef CALENDAR_GREGORIAN_H
#define CALENDAR_GREGORIAN_H

#include "date.hpp"

namespace lab2 {
    class Gregorian : public Date{
    private:
        bool is_leap_year(int year) const;

        // Functions
        void from_jdn_to_date();
        int calc_julian_day_number(int year, int month, int day);
    public:
        //Gregorian * clone() const { return new Gregorian(*this); };

        using Date::operator++;
        using Date::operator--;
        // Constructors
        Gregorian();
        Gregorian(int year, int month, int day);
        Gregorian(const Date & date);
        ~Gregorian();

  
        // Overload operators
        Gregorian operator++(int);
        Gregorian operator--(int);
    };
}

#endif //CALENDAR_GREGORIAN_H
