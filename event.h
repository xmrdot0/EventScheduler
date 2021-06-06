#ifndef __event__
#define __event__
#include <string>
#include <ctime>

using namespace std;
class event
{
    string name, place;
    bool done;
    bool reminded;

    struct tm startDate;
    struct tm endDate;
    struct tm reminderDate;
   

public:
    event()
    {
        done = false;
        reminded = false;
    }
    tm saveDate(int day, int month, int year, int hour, int minutes);

    //setters
    void setName(string name);
    void setStartDate(int day ,int month ,int  year,int  hour , int minutes);
    void setEndDate (int day, int month, int  year, int  hour, int minutes);
    void setReminder(int day, int month, int  year, int  hour, int minutes);
    void setPlace(string place);
    void setDone(int done);
    void setReminded();

    //getters
    tm getStartDate();
    tm getEndDate();
    tm getReminderDate();
    string getPlace();
    string getName();
    void getInfo();
    bool getDone();
    bool getReminded();
    bool operator== (const event& e)const;
};
#endif