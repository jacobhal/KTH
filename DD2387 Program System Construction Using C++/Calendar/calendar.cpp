//
// Created by Jacob Hallman on 26/05/16.
//


using namespace std;

namespace lab2 {

    template <typename T>
    Calendar<T>::Calendar() : current(), events(){};

    template <typename T>
    template <typename T2>
    Calendar<T>::Calendar(const Calendar<T2>& calendar) {

        std::vector<Event<T2>> c_events = calendar.getEvents();
        for (int i = 0; i < (int)c_events.size(); ++i) {
            Event<T> e = c_events[i];
            events.push_back(e);
        }

        current = calendar.getCurrentDate();
    }

    template <typename T>
    Calendar<T>::~Calendar() {};

    // Functions
    template <typename T>
    T Calendar<T>::getCurrentDate() const {
        return current;
    }

    template <typename T>
    std::vector<Event<T>> Calendar<T>::getEvents() const {
        return events;
    }

    template <typename T>
    bool Calendar<T>::set_date(int y, int m, int d) {
        try {
            T(y, m, d);
        }
        catch (const std::invalid_argument& ia) {
            return false;
        }

        current = T(y,m,d);

        return true;
    }

    // Find event
    template <typename T>
    bool Calendar<T>::find_event(Event<T>& e) {
        for (auto current_event = events.begin(); current_event != events.end(); ++current_event) {
            if (*current_event == e) {
                return true;
            }
        }
        return false;
    };

    // Remove events

    template <typename T>
    bool Calendar<T>::remove_event(Event<T>& event) {
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
        try {
            T(current.year(), current.month(), current.day());
        }
        catch (const std::invalid_argument& ia) {
            return false;
        }

        Event<T> t(name, current.year(), current.month(), current.day());
        return remove_event(t);
    }

    template <typename T>
    bool Calendar<T>::remove_event(std::string name, int day) {
        try {
            T(current.year(), current.month(), day);
        }
        catch (const std::invalid_argument& ia) {
            return false;
        }

        Event<T> t(name, current.year(), current.month(), day);
        return remove_event(t);
    }

    template <typename T>
    bool Calendar<T>::remove_event(std::string name, int day, int month) {
        try {
            T(current.year(), month, day);
        }
        catch (const std::invalid_argument& ia) {
            return false;
        }

        Event<T> t(name, current.year(), month, day);
        return remove_event(t);
    }

    template <typename T>
    bool Calendar<T>::remove_event(std::string name, int day, int month, int year) {
        try {
            T(year, month, day);
        }
        catch (const std::invalid_argument& ia) {
            return false;
        }

        Event<T> t(name, year, month, day);
        return remove_event(t);
    }

    // Add events

    template <typename T>
    bool Calendar<T>::add_event(std::string event_name) {
        try {
            T(current.year(), current.month(), current.day());
        }
        catch (const std::invalid_argument& ia) {
            return false;
        }

        Event<T> e(event_name, current.year(), current.month(), current.day());
        if (!find_event(e)) {
            events.push_back(e);
            return true;
        }
        return false;
    }

    template <typename T>
    bool Calendar<T>::add_event(std::string event_name, int day) {
        try {
            T(current.year(), current.month(), day);
        }
        catch (const std::invalid_argument& ia) {
            return false;
        }

        Event<T> e(event_name, current.year(), current.month(), day);
        if (!find_event(e)) {
            events.push_back(e);
            return true;
        }
        return false;
    }

    template <typename T>
    bool Calendar<T>::add_event(std::string event_name, int day, int month) {
        try {
            T(current.year(), month, day);
        }
        catch (const std::invalid_argument& ia) {
            return false;
        }

        Event<T> e(event_name, current.year(), month, day);
        if (!find_event(e)) {
            events.push_back(e);
            return true;
        }
        return false;
    }

    template <typename T>
    bool Calendar<T>::add_event(std::string event_name, int day, int month, int year) {
        try {
            T(year, month, day);
        }
        catch (const std::invalid_argument& ia) {
            return false;
        }

        Event<T> e(event_name, year, month, day);
        if (!find_event(e)) {
            events.push_back(e);
            return true;
        }
        return false;
    }

}


