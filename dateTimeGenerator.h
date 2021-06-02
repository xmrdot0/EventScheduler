//useless header dont include
#ifndef __dateTime__
#define __dateTime__
#define _CRT_NONSTDC_NO_DEPRECATE
#define _CRT_SECURE_NO_DEPRECATE 
#define _CRT_SECURE_NO_WARNINGS
#include <ctime>

class dateTimeGenerator
{
    //used to get current date and time as well as compare them
public:
    static tm getDateTime();
    static int getHour();
    static int getMin();
    static int getSec();
    static int getDay();
    static int getMonth();
    static int getYear();
    static int compTime(tm t1, tm t2);
};
#endif