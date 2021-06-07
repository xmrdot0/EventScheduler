#define _CRT_NONSTDC_NO_DEPRECATE
#define _CRT_SECURE_NO_DEPRECATE 
#define _CRT_SECURE_NO_WARNINGS
#include "user.h"
#include "event.h"
#include "dateTimeGenerator.cpp"
#include <iostream>
using namespace std;

void user::addEvent(event e) {
    this->events.push_back(e);
}
void user::deleteEvent(int idx) {
    this->events.erase(this->events.begin() + idx);
}

string user::getName() { return this->userName; }
string user::getPassword() { return this->password; }

void user::setName(string name) { this->userName = name; }
void user::setPassword(string password) { this->password = password; }

void user::updateEvent(event &e) {
    int c;
    cout << "Options: \n";
    cout << "1: Update The Name" << endl << "2: Update The Place" << endl
        << "3: Update The Start Date" << endl
        << "4: Update The End date" << endl
        << "5: Update The Reminder date" << endl;
    cout << "Please Enter Your choice: \n";
    cin >> c;
    while (c < 1 || c > 5)
    {
        cout << "Invalid choice please try again" << endl;
        cout << "Enter Your Choice: ";
        cin >> c;
    }

    string name;
    int day, month, year, hour, minutes;
    switch (c)
    {

    case 1:
        cout << "Enter The New name" << endl;
        cin >> name;
        e.setName(name);
        cout << "Updated..." << endl;
        break;
    case 2:
        cout << "Enter The New Place" << endl;
        cin >> name;
        e.setPlace(name);
        cout << "Updated..." << endl;
        break;
    case 3:
        cout << "Enter The day: ";
        cin >> day;
        cout << "Enter The Month: ";
        cin >> month;
        cout << "Enter The Year: ";
        cin >> year;
        cout << "Enter The Hour: ";
        cin >> hour;
        cout << "Enter The Minute: ";
        cin >> minutes;
        e.setStartDate(day, month, year, hour, minutes);
        cout << "Updated..." << endl;
        break;
    case 4:
        cout << "Enter The day: ";
        cin >> day;
        cout << "Enter The Month: ";
        cin >> month;
        cout << "Enter The Year: ";
        cin >> year;
        cout << "Enter The Hour: ";
        cin >> hour;
        cout << "Enter The Minute: ";
        cin >> minutes;
        cout << "Updated..." << endl;
        e.setEndDate(day, month, year, hour, minutes);
        break;
    case 5:
        cout << "Enter The day: ";
        cin >> day;
        cout << "Enter The Month: ";
        cin >> month;
        cout << "Enter The Year: ";
        cin >> year;
        cout << "Enter The Hour: ";
        cin >> hour;
        cout << "Enter The Minute: ";
        cin >> minutes;
        e.setStartDate(day, month, year, hour, minutes);
        cout << "Updated..." << endl;
        break;

    }
}

void user::displayEvents() {
    for (event ev : this->events)
    {
        ev.getInfo();
        cout << endl;
    }
}

void user::displayDoneEvents(stack<event> s)
{
    if (s.empty())
        cout << "EMPTY";
    while (!s.empty())
    {
        event e = s.top();
        e.getInfo();
        cout << endl;
        s.pop();
    }
}

void user::checkReminders()
{
    for (int i = 0; i < this->events.size(); i++) {

        if (this->events[i].getReminded() && (dateTimeGenerator::compTime(this->events[i].getReminderDate(), dateTimeGenerator::getDateTime()) != 1)
            && (dateTimeGenerator::compTime(this->events[i].getStartDate(), dateTimeGenerator::getDateTime()) != -1))
        {
            this->events[i].setReminded();
            cout << "\n***REMINDER!***\n";
            this->events[i].getInfo();
        }
    }
}
void user::checkDoneEvents()
{
    for (int i = 0; i < this->events.size(); i++) {
        if (this->events[i].getDone()) {
            this->doneEvents.push(this->events[i]);
            events.erase(this->events.begin() + i);
        }
    }
}
