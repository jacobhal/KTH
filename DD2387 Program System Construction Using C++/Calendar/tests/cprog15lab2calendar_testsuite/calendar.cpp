//
// Created by Jacob Hallman on 26/05/16.
//

#include "src/calendar.hpp"
#include "src/date.hpp"
#include "src/gregorian.hpp"
#include "src/julian.hpp"

using namespace std;

namespace lab2 {

    template <typename T>
    Calendar<T>::Calendar() : current(), events() {};

    template <typename T>
    Calendar<T>::Calendar(const Calendar<T> & calendar) :
              events(calendar.events), current(calendar.current)
    {}

    template <typename T>
    Calendar<T>::~Calendar() {};

    // Functions
    template <typename T>
    bool Calendar<T>::set_date(int y, int m, int d) {
        if(y <= 1858 || y >= 2558 ||
                m > 12 || m < 1 ||
                d < 0 || d > 31 ||
                y < 0)
        {
            return false;
        }

        current = T(y,m,d);

        //current(y, m, d);

        return true;
    }

    // Find event
    template <typename T>
    bool Calendar<T>::find_event(Event& e) {
        for (auto current_event = events.begin(); current_event != events.end(); ++current_event) {
            if (*current_event == e) {
                return true;
            }
        }
        return false;
    };

    // Remove events

    template <typename T>
    bool Calendar<T>::remove_event(Event& event) {
        for(auto current_event = events.begin(); current_event != events.end(); ++current_event) {
            if(*current_event == event) {
                events.erase(current_event);
                return true;
            }
        }
        return false;
    };

    template <typename T>
    bool Calendar<T>::remove_event(std::string name) {
        Event t(name, current.year(), current.month(), current.day());
        return remove_event(t);
    }

    template <typename T>
    bool Calendar<T>::remove_event(std::string name, int day) {
        Event t(name, current.year(), current.month(), day);
        return remove_event(t);
    }

    template <typename T>
    bool Calendar<T>::remove_event(std::string name, int day, int month) {
        Event t(name, current.year(), month, day);
        return remove_event(t);
    }

    template <typename T>
    bool Calendar<T>::remove_event(std::string name, int day, int month, int year) {
        Event t(name, year, month, day);
        return remove_event(t);
    }

    // Add events

    template <typename T>
    bool Calendar<T>::add_event(std::string event_name) {
        Event e(event_name, current.year(), current.month(), current.day());
        if (!find_event(e)) {
            events.push_back(e);
            return true;
        }
        return false;
    }

    template <typename T>
    bool Calendar<T>::add_event(std::string event_name, int day) {
        Event e(event_name, current.year(), current.month(), day);
        if (!find_event(e)) {
            events.push_back(e);
            return true;
        }
        return false;
    }

    template <typename T>
    bool Calendar<T>::add_event(std::string event_name, int day, int month) {
        Event e(event_name, current.year(), month, day);
        if (!find_event(e)) {
            events.push_back(e);
            return true;
        }
        return false;
    }

    template <typename T>
    bool Calendar<T>::add_event(std::string event_name, int day, int month, int year) {
        Event e(event_name, year, month, day);
        if (!find_event(e)) {
            events.push_back(e);
            return true;
        }
        return false;
    }

    /*
    template <typename T>
    std::ostream& Calendar<T>::operator<< (std::ostream &cout, const Calendar<T> &c) {

    }
     */

}