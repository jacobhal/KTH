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
    class Calendar{
    public:
        struct Event {

            Event(std::string en, int y, int m, int d)
                    : name(en), y(y), m(m), d(d) {}
            Event(int y, int m, int d)
                    : y(y), m(m), d(d) {}

            bool operator==(const Event & event) {
                return (this->name == event.name &&
                        this->y == event.y &&
                        this->m == event.m &&
                        this->d == event.d);
            };

            std::string name;
            int y;
            int m;
            int d;
        };

        bool set_date(int y, int m, int d);
        bool add_event (std::string event_name, int day, int month, int year);
        bool add_event (std::string event_name, int day, int month);
        bool add_event (std::string event_name, int day);
        bool add_event (std::string event_name);
        bool remove_event(Event& event);
        bool remove_event (std::string event_name, int day, int month, int year);
        bool remove_event (std::string event_name, int day, int month);
        bool remove_event (std::string event_name, int day);
        bool remove_event (std::string event_name);

        bool find_event(Event& e);

        friend std::ostream& operator<< (std::ostream &cout, const Calendar &c) {
            //std::cout << c.current.year() << "-" << c.current.month() << "-" << c.current.day() << std::endl;
            //std::cout << c.current << std::endl;
            cout << "BEGIN:" << "VCALENDAR" << std::endl;
            cout << "VERSION:" << 2.0 << std::endl;
            cout << "PRODID:" << "// Snälla funka" << std::endl;


            for (int i = 0; i < c.events.size(); ++i) {
                cout << "BEGIN:"	<< "VEVENT"			<< "\n"
                << "SUMMARY:"	<< c.events[i].name << "\n"
                << "UID:"		<< c.events[i].y	<< "-" << c.events[i].m << "-" << c.events[i].d << "\n"
                << "END:"		<< "VEVENT"			<< "\n";
            }

            cout << "END:" << "VCALENDAR" << "\n";
            return cout;
        };

        Calendar();
        Calendar(const Calendar&);
        ~Calendar();

    private:
        DateType current;
        std::vector<Event> events;
    };

}
#include "../calendar.cpp"

#endif //CALENDAR_CALENDAR_H


