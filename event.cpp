#define _CRT_NONSTDC_NO_DEPRECATE
#define _CRT_SECURE_NO_DEPRECATE 
#define _CRT_SECURE_NO_WARNINGS
#include "event.h"
#include <iostream>
#include "Console.h"
#include "dateTimeGenerator.cpp"
using namespace std;

tm event::saveDate(int day, int month, int year, int hour, int minutes)
{
    tm timeinfo;
    timeinfo.tm_year = year;
    timeinfo.tm_mon = month;
    timeinfo.tm_mday = day;
    timeinfo.tm_hour = hour;
    timeinfo.tm_min = minutes;
    return timeinfo;
}
void event::setName(string name)
{
    this->name = name;
}

void event::setStartDate(int day, int month, int  year, int  hour, int minutes)
{
       this->startDate = saveDate(day, month, year, hour, minutes);
}

void event::setEndDate(int day, int month, int  year, int  hour, int minutes)
{
   
    this->endDate = saveDate(day, month, year, hour, minutes);
}

void event::setReminder(int day, int month, int  year, int  hour, int minutes)
{
    this->reminderDate = saveDate(day, month, year, hour, minutes);
}

void event::setDone(int done)
{
    this->done = done;
}

void event::setPlace(string place)
{
    this->place = place;
}

tm event::getStartDate()
{
    return this->startDate;
}

tm event::getReminderDate()
{
    return this->reminderDate;
}

tm event::getEndDate()
{
    return this->endDate;
}

string event::getName()
{
    return this->name;
}

string event::getPlace()
{
    return this->place;
}

bool event::getDone()
{
    if (dateTimeGenerator::compTime(this->endDate, dateTimeGenerator::getDateTime()) == -1)
        this->done = true;
    return this->done;
}
bool event::getReminded()
{
    return this->reminded;
}
bool event::operator==(const event& e) const
{
    return (this->place == e.place && this->name == e.name);
}
void event::setReminded()
{
    this->reminded = true;
}
void event::getInfo()
{
    cout << "Event: " << this->getName() << endl;
    cout << "Place: " << this->getPlace() << endl;
    
    cout << "Start Date: " << this->getStartDate().tm_mday << "/" << this->getStartDate().tm_mon << "/" << this->getStartDate().tm_year << endl;
    cout << "Start Time: " << this->getStartDate().tm_hour << ":" << this->getStartDate().tm_min << endl;
    
    cout << "End Date: " << this->getEndDate().tm_mday << "/" << this->getEndDate().tm_mon << "/" << this->getEndDate().tm_year << endl;
    cout << "End Time: " << this->getEndDate().tm_hour << ":" << this->getEndDate().tm_min << endl;

    cout << "Reminder Date: " << this->getReminderDate().tm_mday << "/" << this->getReminderDate().tm_mon << "/" << this->getReminderDate().tm_year << endl;
    cout << "Reminder Time: " << this->getReminderDate().tm_hour << ":" << this->getReminderDate().tm_min << endl;
}