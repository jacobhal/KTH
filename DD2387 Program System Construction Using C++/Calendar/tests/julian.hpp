#ifndef CALENDAR_JULIAN_H
#define CALENDAR_JULIAN_H

#include "date.hpp"

namespace lab2 {
	class Julian : public Date{
	private:
		inline bool is_leap_year(int year) const { return year % 4 == 0; };

	public:
		//Julian * clone() const { return new Julian(*this); };

		using Date::operator++;
		using Date::operator--;
		// Constructors
		Julian();
		Julian(int year, int month, int day);
		Julian(const Date & date);
		~Julian();

		// Functions
		void from_jdn_to_date();
		int calc_julian_day_number(int year, int month, int day);

		// Overload operators
		Julian operator++(int);
		Julian operator--(int);
	};
}
#endif