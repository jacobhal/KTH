namespace lab2 {
	class Gregorian : Julian {
		public:
		int year(); // Returns the current year
		unsigned int month(); // Returns the number associated with the current month ([1,n]).
		unsigned int day(); // Returns the number associated with the current day in the current month ([1,n]).
		unsigned int week_day(); // Returns the number associated with the current weekday ([1,n]).
		unsigned int days_per_week(); // Returns the number of days in a week.
		unsigned int days_this_month(); // Returns the number of days in the current month.
		std::string week_day_name(); // Returns the name of the current weekday.
		std::string month_name(); // Returns the name of the current month.
		unspecified add_year (int n = 1); // Increments the current year by n.
		unspecified add_month (int n = 1); // Increments the current month by n.
		int mod_julian_day(); // This function shall return the MJD representation of the current date.
	};
}




/*
{ Gregorian g (1900, 1,   1);
    Julian    j (1899, 12, 19);
    j == g; // shall yield false
    j++;    // increment ‘j‘ by one day
    j == g; // shall yield true
}
  { Gregorian g (1858, 11, 16);
    Julian    j (g);
    std::cout << j; // shall print 1858-11-4
    std::cout << g; // shall print 1858-11-16
}
  { Date * p1 = new Julian ();
    Date * p2 = new Gregorian ();
    *p1 == *p2; // shall be true
delete p1;
delete p2; }
 */