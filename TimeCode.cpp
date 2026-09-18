#include "TimeCode.h"
#include <stdexcept>
#include <string>

using namespace std;


// Constructor
TimeCode::TimeCode(unsigned int hr, unsigned int min, long long unsigned int sec)
{
    // Store the entire TimeCode as total seconds.
    // This automatically handles rollover for large minutes/seconds.
    t = ComponentsToSeconds(hr, min, sec);
}


// Copy constructor
TimeCode::TimeCode(const TimeCode& tc)
{
    t = tc.t;
}


// Set hours
void TimeCode::SetHours(unsigned int hours)
{
    unsigned int currentHours;
    unsigned int currentMinutes;
    unsigned int currentSeconds;

    // Get the current minutes and seconds so only hours changes.
    GetComponents(currentHours, currentMinutes, currentSeconds);

    t = ComponentsToSeconds(hours, currentMinutes, currentSeconds);
}


// Set minutes
void TimeCode::SetMinutes(unsigned int minutes)
{
    // Minutes cannot be 60 or greater.
    if (minutes > 59)
    {
        throw invalid_argument("Minutes must be between 0 and 59.");
    }

    unsigned int currentHours;
    unsigned int currentMinutes;
    unsigned int currentSeconds;

    // Get the current hours and seconds so only minutes changes.
    GetComponents(currentHours, currentMinutes, currentSeconds);

    t = ComponentsToSeconds(currentHours, minutes, currentSeconds);
}


// Set seconds
void TimeCode::SetSeconds(long long unsigned int seconds)
{
    // Seconds cannot be 60 or greater.
    if (seconds > 59)
    {
        throw invalid_argument("Seconds must be between 0 and 59.");
    }

    unsigned int currentHours;
    unsigned int currentMinutes;
    unsigned int currentSeconds;

    // Get the current hours and minutes so only seconds changes.
    GetComponents(currentHours, currentMinutes, currentSeconds);

    t = ComponentsToSeconds(currentHours, currentMinutes, seconds);
}


// Reset TimeCode
void TimeCode::reset()
{
    t = 0;
}


// Get hours
unsigned int TimeCode::GetHours() const
{
    unsigned int hours;
    unsigned int minutes;
    unsigned int seconds;

    GetComponents(hours, minutes, seconds);

    return hours;
}


// Get minutes
unsigned int TimeCode::GetMinutes() const
{
    unsigned int hours;
    unsigned int minutes;
    unsigned int seconds;

    GetComponents(hours, minutes, seconds);

    return minutes;
}

// Get seconds
unsigned int TimeCode::GetSeconds() const
{
    unsigned int hours;
    unsigned int minutes;
    unsigned int seconds;

    GetComponents(hours, minutes, seconds);

    return seconds;
}

// Return total seconds
long long unsigned int TimeCode::GetTimeCodeAsSeconds() const
{
    return t;
}

// Convert total seconds into hours, minutes, seconds
void TimeCode::GetComponents(unsigned int& hr, unsigned int& min, unsigned int& sec) const
{
    // 1 hour = 3600 seconds.
    hr = t / 3600;

    // Find the seconds remaining after removing the hours.
    unsigned long long int remainder = t % 3600;

    // 1 minute = 60 seconds.
    min = remainder / 60;

    // Whatever remains is the seconds.
    sec = remainder % 60;
}


// Convert hours, minutes, seconds into total seconds
long long unsigned int TimeCode::ComponentsToSeconds(unsigned int hr, unsigned int min, long long unsigned int sec) {
    // Do not restrict minutes or seconds here.
    // The assignment allows rollover in the constructor.
    //
    // Example:
    // 3 hours, 71 minutes, 3801 seconds
    // is converted into total seconds first.

    return (static_cast<unsigned long long int>(hr) * 3600) + (static_cast<unsigned long long int>(min) * 60) + sec;
}

// Convert TimeCode to "hours:minutes:seconds"
string TimeCode::ToString() const
{
    unsigned int hours;
    unsigned int minutes;
    unsigned int seconds;

    GetComponents(hours, minutes, seconds);

    return to_string(hours) + ":" + to_string(minutes) + ":" + to_string(seconds);
}

// Addition
TimeCode TimeCode::operator+(const TimeCode& other) const
{
    TimeCode result;

    result.t = t + other.t;

    return result;
}

// Subtraction
TimeCode TimeCode::operator-(const TimeCode& other) const
{
    // TimeCodes cannot be negative.
    if (other.t > t)
    {
        throw invalid_argument("TimeCode cannot be negative.");
    }

    TimeCode result;

    result.t = t - other.t;

    return result;
}

// Multiplication
TimeCode TimeCode::operator*(double a) const
{
    // A negative TimeCode is not allowed.
    if (a < 0)
    {
        throw invalid_argument("TimeCode cannot be negative.");
    }

    TimeCode result;

    result.t = static_cast<unsigned long long int>(t * a);

    return result;
}

// Division
TimeCode TimeCode::operator/(double a) const
{
    // Division by zero is not allowed.
    if (a <= 0)
    {
        throw invalid_argument(
            "Cannot divide TimeCode by zero or a negative number.");
    }

    TimeCode result;

    result.t = static_cast<unsigned long long int>(t / a);

    return result;
}

// Equality
bool TimeCode::operator==(const TimeCode& other) const
{
    return t == other.t;
}

// Not equal
bool TimeCode::operator!=(const TimeCode& other) const
{
    return t != other.t;
}

// Less than
bool TimeCode::operator<(const TimeCode& other) const
{
    return t < other.t;
}

// Less than or equal
bool TimeCode::operator<=(const TimeCode& other) const
{
    return t <= other.t;
}

// Greater than
bool TimeCode::operator>(const TimeCode& other) const
{
    return t > other.t;
}

// Greater than or equal
bool TimeCode::operator>=(const TimeCode& other) const
{
    return t >= other.t;
}