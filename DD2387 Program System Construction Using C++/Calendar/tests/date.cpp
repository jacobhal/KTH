//
// Created by Jacob Hallman on 22/05/16.
//
#include "date.hpp"
#include "kattistime.h"
#include <iostream>
#include <time.h>

using namespace std;

namespace lab2 {

    //Default contructor
    Date::Date(){

        ////////////////////////////////////////////////////////////
        // Sätt tiden. OBS skicka inte nedanstående kod till kattis
        time_t mytime;
#if 0
        time(&mytime);
        set_k_time(mytime);
#endif
        ////////////////////////////////////////////////////////////

        // För att få nuvarande tid

        k_time(&mytime);


        // För att få ut datum lokalt

        struct tm* t = gmtime(&mytime);
        y = t->tm_year + 1900;
        m = t->tm_mon + 1;      // månaderna och dagarna
        d = t->tm_mday;         // indexerade från ETT

    }

    Date::Date(int y, int m, int d) {
        this->y = y;
        this->m = m;
        this->d = d;
    }

    Date::~Date() {
        //cout << "Date destructor" << endl;
        // TODO
    }

    // Assignment
    Date & Date::operator=(const Date & date) {
        this->julian_day_number = date.julian_day_number;
        from_jdn_to_date();
        return *this;
    }

    // Operators
    int Date::operator-(const Date& rhs) const{
        return this->julian_day_number - rhs.julian_day_number;;
    }

    Date& Date::operator-=(const int rhs) {
        julian_day_number -= rhs;
        from_jdn_to_date();
        return *this;
    }
    Date& Date::operator+=(const int rhs) {
        julian_day_number += rhs;
        from_jdn_to_date();
        return *this;
    }

    Date& Date::operator++() {
        //cout << "Prefix increment" << endl;
        julian_day_number++;
        from_jdn_to_date();
        return *this;
    }
    Date& Date::operator--() {
        julian_day_number--;
        from_jdn_to_date();
        return *this;
    }

    unsigned int Date::days_this_month() const {
        if(month() == 2 && is_leap_year(year())) {
            return 29;
        }
        static int monthDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        return monthDays[month()-1];
    }

    int Date::calc_julian_day_number(int year, int month, int day) {
		int a = (14 - month) / 12;
		int y = year + 4800 - a;
		int m = month + 12*a- 3;
		int JDN = day + (153*m + 2) / 5 + 365*y + y/4 - y/100 + y/400 - 32045;
		return JDN;
	}


    bool Date::valid_date(int year, int month, int day) const {
        if(year <= 1858 || year >= 2558
           || month <= 0 || month > months_per_year()
           ||  day <= 0 || day > days_this_month()) {
            return false;
        }
        return true;
    }

    std::ostream& operator<<(std::ostream& os, const Date& dt)
    {
        os << dt.y << '-' << dt.m << '-' << dt.d;
        return os;
    }


    /*
     * Mandatory Functions
     */

    int Date::year() const { return this->y; }; // Returns the current year
    unsigned int Date::month() const { return this->m; }; // Returns the number associated with the current month ([1,n]).
    unsigned int Date::day() const { return this->d; }; // Returns the number associated with the current day in the current month ([1,n]).

    /*
     * Returns the number associated with the current weekday ([1,n]).
     * Day of the week numbers: Mon = 1, Tue = 2, Wed = 3, Thu = 4, Fri = 5, Sat = 6, Sun = 7.
     * Source: https://en.wikipedia.org/wiki/Julian_day#Calculation
     */
    unsigned int Date::week_day() const {
        return (julian_day_number % 7) + 1;
    }

    std::string Date::week_day_name() const {
        //  Static so that once the variable has been initialized, it remains in memory until the end of the program.
        static std::string weekdays [7] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
        return weekdays[week_day()-1];
    } // Returns the name of the current weekday.
    std::string Date::month_name() const {
        static std::string months [12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October"
        , "November", "December"};
        return months[month()-1];
    } // Returns the name of the current month.

    void Date::add_year (int n) {
        this->y += n;
        if(!valid_date(year(), month(), day())) {
            this->d = days_this_month();
        }
        this->julian_day_number = calc_julian_day_number(year(), month(), day());
    }

    void Date::add_month (int n) {

        // Negative
        if(n < 0)
        {
            int tmp = month();
            this->m = tmp - abs(n) > 0 ? tmp - abs(n) : 12 - abs(n + tmp) % 12;
            if(n + tmp <= 0) {
                this->y -= (1 + floor(abs(n + tmp)/12));
            }
        } else {
            int months = abs(n) + month();
            if(months % 12 != 0)
                this->m = months % 12;
            else
                this->m = 12;

            if(months > 12 && months % 12 != 0) {
                this->y += months / 12;
            } else if (months > 12) {
                this->y += months / 12 - 1;
            }
        }

        if(!valid_date(year(), month(), day())) {
            this->d = days_this_month();
        }

        this->julian_day_number = calc_julian_day_number(year(), month(), day());
    }
}

