//
// Created by Jacob Hallman on 21/05/16.
//

#include "gregorian.hpp"

namespace lab2 {
	using namespace std;

	// Constructors
	Gregorian::Gregorian() : Date() {
		this->julian_day_number = calc_julian_day_number(year(), month(), day());
	}

	Gregorian::Gregorian(int year, int month, int day) : Date(year, month, day) { // Call Date constructor with initialization list
		if(!valid_date(year, month, day)) {
			throw(std::invalid_argument("Invalid date"));
		} else {
			this->julian_day_number =  calc_julian_day_number(year, month, day);
			from_jdn_to_date();
		}
	}

	// Copy
	Gregorian::Gregorian (const Date& date) {
		//cout << "Gregorian copy" << endl;
		this->julian_day_number = date.julian_day();
		from_jdn_to_date();
	}


	Gregorian::~Gregorian() {
		cout << "Destructor" << endl;
		//delete this;
		// TODO
	}
	// Overload
	Gregorian Gregorian::operator++(int) {
		//cout << "Postfix increment" << endl;
		Gregorian tmp(*this);
		Date::operator++(); // prefix-increment this instance
		return tmp;   // return value before increment
	}
	Gregorian Gregorian::operator--(int) {
		Gregorian tmp(*this);
		Date::operator++(); // prefix-increment this instance
		return tmp;   // return value before increment
	}

	bool Gregorian::is_leap_year(int year) const {
		if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
			return true;
		return false;
	}

	void Gregorian::from_jdn_to_date() {
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

		int f = julian_day_number + j + (((4 * julian_day_number + B) / 146097) * 3) / 4 + C;
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

	int Gregorian::calc_julian_day_number(int year, int month, int day) {
		int a = (14 - month) / 12;
		int y = year + 4800 - a;
		int m = month + 12*a- 3;
		int JDN = day + (153*m + 2) / 5 + 365*y + y/4 - y/100 + y/400 - 32045;
		return JDN;
	}
}


