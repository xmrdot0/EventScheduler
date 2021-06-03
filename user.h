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

    stack<event> doneEvents;
    string userName, password;
    void update_menu(event& e);
 

public:
    vector<event> events;
    void addEvent(event e);
    void deleteEvent(event e);
    void updateEvent(event e);
    void displayDoneEvents();
    void displayEvents();
    void setName(string name);
    void setPassword(string password);
    string getName();
    string getPassword();

    void checkDoneEvents();
    void checkReminders();
};
#endif