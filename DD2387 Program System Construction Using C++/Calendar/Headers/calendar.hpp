//
// Created by Jacob Hallman on 26/05/16.
//

#ifndef CALENDAR_CALENDAR_H
#define CALENDAR_CALENDAR_H

#include <string>
#include <vector>
#include "date.hpp"
#include "gregorian.hpp"
#include "julian.hpp"

namespace lab2 {
    template<typename DateType>
    struct Event {

        std::string name;
        DateType date;

        Event(std::string en, int y, int m, int d)
                : name(en), date(y, m, d) {};

        template<typename CopyDate>
        Event<DateType>(Event<CopyDate>& event) {
            this->name = event.name;
            this->date = event.date;
        };

        bool operator==(const Event<DateType> & event) {
            return (this->name == event.name &&
                    this->date == event.date);
        };

    };

    template<typename DateType>
    class Calendar{
    public:

        bool set_date(int y, int m, int d);
        bool add_event (std::string event_name, int day, int month, int year);
        bool add_event (std::string event_name, int day, int month);
        bool add_event (std::string event_name, int day);
        bool add_event (std::string event_name);
        bool remove_event(Event<DateType>& event);
        bool remove_event (std::string event_name, int day, int month, int year);
        bool remove_event (std::string event_name, int day, int month);
        bool remove_event (std::string event_name, int day);
        bool remove_event (std::string event_name);

        bool find_event(Event<DateType>& e);

        DateType getCurrentDate() const;
        std::vector<Event<DateType>> getEvents() const;

        friend std::ostream& operator<< (std::ostream &cout, const Calendar<DateType>&c) {
            //std::cout << c.current.year() << "-" << c.current.month() << "-" << c.current.day() << std::endl;
            //std::cout << c.current << std::endl;
            cout << "BEGIN:" << "VCALENDAR" << std::endl;
            cout << "VERSION:" << 2.0 << std::endl;
            cout << "PRODID:" << "// Snälla funka" << std::endl;


            for (int i = 0; i < c.events.size(); ++i) {
                // TODO: Only print events greater than current date
                DateType d(c.current);
                //std::cout << d << std::endl;
                if (c.events[i].date >= d) {
                    std::string y = std::to_string(c.events[i].date.year());
                    std::string m = std::to_string(c.events[i].date.month());
                    std::string d = std::to_string(c.events[i].date.day());

                    //std::string y1 = s.substr(2, 2);
                    if (c.events[i].date.month() < 10) {
                        m = "0" + m;
                    }
                    if (c.events[i].date.day() < 10) {
                        d = "0" + d;
                    }

                    cout << "BEGIN:" << "VEVENT" << "\n"
                    << "DTSTART:" << y << m << d << "\n"
                    << "DTEND:" << y << m << d << "\n"
                    << "SUMMARY:" << c.events[i].name << "\n"
                    << "UID:" << y << "-" << m << "-" << d << "\n"
                    << "END:" << "VEVENT" << "\n";
                }
            }

            cout << "END:" << "VCALENDAR" << "\n";
            return cout;
        };

        Calendar();

        template<typename CopyDate>
        Calendar(const Calendar<CopyDate>&);

        ~Calendar();



    private:
        DateType current;
        std::vector<Event<DateType>> events;
    };

}
#include "../calendar.cpp"

#endif //CALENDAR_CALENDAR_H
