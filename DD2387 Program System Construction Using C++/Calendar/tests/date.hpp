#ifndef CALENDAR_DATE_H
#define CALENDAR_DATE_H

#include <iostream>
#include <stdexcept>
#include <cmath>

namespace lab2 {
	class Date {
	private:
		virtual bool is_leap_year(int year) const =0;
	protected:
		int y, m, d;
		int julian_day_number;

	public:
		// TODO: Vilka ska vara "pure virtual"?


		Date();
		Date(int, int, int);
		//Date(const Date& date);
		virtual ~Date();

		// Operators
		int operator-(const Date & date) const;
		Date& operator-=(const int rhs);
		Date& operator+=(const int rhs);
		Date& operator=(const Date & date);

		Date& operator++();
		Date& operator--();


		// Comparisons
		inline bool operator< (const Date& d) const {
			return this->julian_day_number < d.julian_day_number;
		}
		inline bool operator> (const Date& d) const {
			return this->julian_day_number > d.julian_day_number;
		}
		inline bool operator<=(const Date& d) const {
			return this->julian_day_number <= d.julian_day_number;
		}
		inline bool operator>=(const Date& d) const {
			return this->julian_day_number >= d.julian_day_number;
		}

		bool operator==(const Date& d) const {
			return this->julian_day_number == d.julian_day_number;
		}

		bool operator!=(const Date& d) const {
			return this->julian_day_number != d.julian_day_number;
		}


		/*
		* Mandatory functions
		*/
		int year() const; // Returns the current year
		unsigned int month() const; // Returns the number associated with the current month ([1,n]).
		unsigned int day() const; // Returns the number associated with the current day in the current month ([1,n]).

		unsigned int week_day() const; // Returns the number associated with the current weekday ([1,n]).
		unsigned int days_this_month() const; // Returns the number of days in the current month.
		std::string week_day_name() const; // Returns the name of the current weekday.
		std::string month_name() const; // Returns the name of the current month.
		void add_year(int n = 1); // Increments the current year by n.
		void add_month(int n = 1); // Increments the current month by n.

		/*
        * Functions implemented here
        */
		// Returns the modified julian date representation for a specific julian day number (0.5 is added to the default value)
		// src: https://en.wikipedia.org/wiki/Julian_day
		int mod_julian_day() const { return (julian_day_number - 2400001); }; // This function shall return the MJD representation of the current date.
		int julian_day() const { return this->julian_day_number; };
		inline unsigned int days_per_week() const { return 7; }; // Inline to speed up
		inline unsigned int months_per_year() const { return 12; }; // Inline to speed up


		/*
        * Own functions
        */
		bool valid_date(int year, int month, int day) const;
		virtual int calc_julian_day_number(int year, int month, int day) =0;
		virtual void from_jdn_to_date() =0;

		friend std::ostream &operator << (std::ostream &cout, const Date &d);
	};


}

#endif
