#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <vector>

#include "TimeCode.h"

using namespace std;


// Extracts the UTC time from one CSV line.
// Example:
// Fri Aug 07, 2020 05:12 UTC becomes: 05:12:00

bool parse_line(const string& line, TimeCode& result)
{
    // Look for HH:MM followed by " UTC"
    regex timePattern(R"(\b([01][0-9]|2[0-3]):([0-5][0-9])\s+UTC\b)");

    smatch match;

    if (!regex_search(line, match, timePattern))
        return false;

    unsigned int hours = stoi(match[1].str());
    unsigned int minutes = stoi(match[2].str());

    // The CSV does not give seconds, so use 0 seconds.
    unsigned int seconds = 0;

    result = TimeCode(hours, minutes, seconds);

    return true;
}


int main()
{
    ifstream file("Space_Corrected.csv");

    if (!file)
    {
        cerr << "Error: Could not open Space_Corrected.csv" << endl;
        return 1;
    }

    vector<TimeCode> times;

    string line;

    // Skip the header row.
    getline(file, line);

    while (getline(file, line))
    {
        TimeCode time;

        if (parse_line(line, time))
        {
            times.push_back(time);
        }
    }

    cout << times.size() << " data points." << endl;

    if (times.empty())
    {
        cerr << "Error: No launch times were found." << endl;
        return 1;
    }

    // Add all launch times together.
    TimeCode total;

    for (const TimeCode& time : times)
    {
        total = total + time;
    }

    // Calculate the average.
    TimeCode average = total / times.size();

    cout << "AVERAGE: " << average.ToString() << endl;

    return 0;
}