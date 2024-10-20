#include "TimerSystem.h"

Time GetTime()
{
    struct tm newtime;
    char am_pm[] = "AM";
    __time64_t long_time;
    char timebuf[26];
    errno_t err;
    bool _isAfternoon = false;

    // Get time as 64-bit integer.
    _time64(&long_time);
    // Convert to local time.
    err = _localtime64_s(&newtime, &long_time);
    if (err)
    {
        printf("Invalid argument to _localtime64_s.");
        exit(1);
    }
    if (newtime.tm_hour > 12)        // Set up extension.
    {
        strcpy_s(am_pm, sizeof(am_pm), "PM");
        _isAfternoon = true;
    }
    if (newtime.tm_hour > 12)        // Convert from 24-hour
        newtime.tm_hour -= 12;        // to 12-hour clock.
    if (newtime.tm_hour == 0)        // Set hour to 12 if midnight.
        newtime.tm_hour = 12;

    // Convert to an ASCII representation.
    err = asctime_s(timebuf, 26, &newtime);
    if (err)
    {
        printf("Invalid argument to asctime_s.");
        exit(1);
    }
    const string& _hour = { timebuf[11], timebuf[12] };
    const string& _minutes = { timebuf[14], timebuf[15] };
    const string& _seconds = { timebuf[17], timebuf[18] };

    int _finalHour = stoi(_hour);
    _finalHour += _isAfternoon ? 12 : 0;
    return Time({ _finalHour, stoi(_minutes), stoi(_seconds) });
}
