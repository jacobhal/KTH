namespace lab2 {
	class Date {
	public:
		// TODO: Vilka ska vara "pure virtual"?

		// Dessa obligatoriska ska antagligen vara virtual.
		virtual int year() =0; // Returns the current year
		virtual unsigned int month() =0; // Returns the number associated with the current month ([1,n]).
		virtual unsigned int day() =0; // Returns the number associated with the current day in the current month ([1,n]).
		virtual unsigned int week_day() =0; // Returns the number associated with the current weekday ([1,n]).
		virtual unsigned int days_per_week() =0; // Returns the number of days in a week.
		virtual unsigned int days_this_month() =0; // Returns the number of days in the current month.
		virtual std::string week_day_name() =0; // Returns the name of the current weekday.
		virtual std::string month_name() =0; // Returns the name of the current month.
		virtual unspecified add_year (int n = 1) =0; // Increments the current year by n.
		virtual unspecified add_month (int n = 1) =0; // Increments the current month by n.
		virtual int mod_julian_day() =0; // This function shall return the MJD representation of the current date.
	};
}