#ifndef TIME_CODE_H
#define TIME_CODE_H

#include <iostream>

using namespace std;

class TimeCode {
    public:
        TimeCode(unsigned int hr = 0, unsigned int min = 0, long long unsigned int sec = 0);

        TimeCode(const TimeCode &tc);

        ~TimeCode(){};

        void SetHours(unsigned int hours);
        void SetMinutes(unsigned int minutes);
        void SetSeconds(long long unsigned int seconds);

        void reset();

        unsigned int GetHours() const;
        unsigned int GetMinutes() const;
        unsigned int GetSeconds() const;

        long long unsigned int GetTimeCodeAsSeconds() const;

        void GetComponents(unsigned int& hr, unsigned int& min, unsigned int& sec) const;

        static long long unsigned int ComponentsToSeconds(unsigned int hr, unsigned int min, long long unsigned int sec);

        string ToString() const;

        TimeCode operator+(const TimeCode& other) const;
        TimeCode operator-(const TimeCode& other) const;
        TimeCode operator*(double a) const;
        TimeCode operator/(double a) const;

        bool operator==(const TimeCode& other) const;
        bool operator!=(const TimeCode& other) const;

        bool operator<(const TimeCode& other) const;
        bool operator<=(const TimeCode& other) const;

        bool operator>(const TimeCode& other) const;
        bool operator>=(const TimeCode& other) const;

    private:
        // The only instance variable allowed by the assignment.
        // It stores the entire TimeCode as total seconds.
        long long unsigned int t;
};

#endif