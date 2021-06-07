#ifndef __Event__
#define __Event__

#include <string>
#include <vector>
#include <stack>
#include "event.h"
using namespace std;
class user
{
    // event1: 25/1/2021 - *27/1/2021
    // event2: *26/1/2022 - 27/1/2022

    // event2: *26/1/2022 - 27/1/2022
    // event1: 25/1/2021 - *27/1/2021

    string userName, password;
 
public:
    vector<event> events;
    stack<event> doneEvents;
    void addEvent(event e);
    void deleteEvent(int idx);
    void updateEvent(event &e);
    void displayDoneEvents(stack<event> s);
    void displayEvents();
    void setName(string name);
    void setPassword(string password);
    string getName();
    string getPassword();

    void checkDoneEvents();
    void checkReminders();
};
#endif