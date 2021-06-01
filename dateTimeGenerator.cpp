#ifndef __dateTime__
#define __dateTime__
#define _CRT_NONSTDC_NO_DEPRECATE
#define _CRT_SECURE_NO_DEPRECATE 
#define _CRT_SECURE_NO_WARNINGS
//#include "dateTimeGenerator.h"
#include <ctime>
#include <iostream>
using namespace std;

class dateTimeGenerator
{
public:
    static tm getDateTime()
    {
        tm timeInfo;
        timeInfo.tm_hour = getHour();
        timeInfo.tm_min = getMin();
        timeInfo.tm_sec = getSec();
        timeInfo.tm_mon = getMonth();
        timeInfo.tm_year = getYear();
        timeInfo.tm_mday = getDay();

        return timeInfo;
    }
    static int getHour()
    {
        time_t now = time(0);
        tm *ltm = localtime(&now);
        return ltm->tm_hour;
    }
    static int getMin()
    {
        time_t now = time(0);
        tm *ltm = localtime(&now);
        return ltm->tm_min;
    }
    static int getSec()
    {
        time_t now = time(0);
        tm *ltm = localtime(&now);
        return ltm->tm_sec;
    }
    static int getDay()
    {
        time_t now = time(0);
        tm *ltm = localtime(&now);
        return ltm->tm_mday;
    }
    static int getMonth()
    {
        time_t now = time(0);
        tm *ltm = localtime(&now);
        return ltm->tm_mon + 1;
    }
    static int getYear()
    {
        time_t now = time(0);
        tm *ltm = localtime(&now);
        return 1900 + ltm->tm_year;
    }
    static int compTime(tm t1, tm t2)
    {
        if (t1.tm_year < t2.tm_year)
            return -1;
        else if (t1.tm_year > t2.tm_year)
            return 1;

        else if (t1.tm_mon < t2.tm_mon)
            return -1;
        else if (t1.tm_mon > t2.tm_mon)
            return 1;

        else if (t1.tm_mday < t2.tm_mday)
            return -1;
        else if (t1.tm_mday > t2.tm_mday)
            return 1;

        else if (t1.tm_hour < t2.tm_hour)
            return -1;
        else if (t1.tm_hour > t2.tm_hour)
            return 1;

        else if (t1.tm_min < t2.tm_min)
            return -1;
        else if (t1.tm_min > t2.tm_min)
            return 1;

        return 0;
    }
};
#endif