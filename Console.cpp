#define _CRT_NONSTDC_NO_DEPRECATE
#define _CRT_SECURE_NO_DEPRECATE 
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Console.h"
#include "user.h"
#include "event.h"
#include <vector>
#include <algorithm>
#include "dateTimeGenerator.cpp"
#include "fileManager.cpp"

using namespace std;
bool sortComparator(event e1, event e2) {
    if (dateTimeGenerator::compTime(e1.getStartDate(), e2.getStartDate()) == 1)
        return 0;
    return 1;
}   
bool sortbyReminderComparator(event e1, event e2) {
    if (dateTimeGenerator::compTime(e1.getReminderDate(), e2.getReminderDate()) == 1)
        return 0;
    return 1;
}
bool canBeAdded(event newEvent, vector<event> events) {

    if (events.empty())
    {
        return true;
    }
    for (int i = 0; i < events.size(); i++)
    {
        if (dateTimeGenerator::compTime(newEvent.getStartDate(), events[i].getEndDate()) == 1)
            return true;
        else if (dateTimeGenerator::compTime(newEvent.getEndDate(), events[i].getStartDate()) == -1)
            return true;
    }
    return false;
}
Console::Console(vector<user> &users)
{
    this->users = users;
    landingPage();
}

void Console::Login()
{
    bool success = false;
    while (true) {
        string username, password;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;

        for (user u : users) {
            if (u.getName() == username && u.getPassword() == password)
            {
                success = true;
                this->usr = u;
                break;
            }
        }
        if (success) {
            break;
        }
        else {
            cout << "\n***Incorrect user name or password! please try again***" << endl;
        }
    }
    cout << "\n\t***Login Successfull***" << endl;
    driver();
}

void Console::driver()
{
    fileManager::writeUsers(this->users);
    fileManager::readEvents(this->usr.events, usr.getName());
    bool exit = false;
    while (!exit)
    {
        switch (Console::mainMenu())
        {
        case 1:
            add_event();
            break;
        case 2:
            update_event();
            break;
        case 3:
            del_event();
            break;
        case 4:
            disp_event();
            break;
        case 5:
            disp_done_event();
            break;
        case 6:
            exit = true;
            break;
        }
        this->usr.checkDoneEvents();
        this->usr.checkReminders();
    }
}
int Console::mainMenu()
{
    int input;
    cout << endl
         << "Options:" << endl;
    cout << "1. Add Event" << endl
         << "2. Update event" << endl
         << "3. Delete event" << endl
         << "4. Display upcoming events" << endl
         << "5. Display done events" << endl 
         << "6. Exit" << endl;
    cout << "Enter Your Choice: ";

    cin >> input;
    while (input < 1 || input > 6)
    {
        cout << "Invalid input please try again" << endl;
        cin >> input;
    }
    return input;
}

void Console::Register()
{
    string username, password;
    while (true) {
        cout << "Enter a username: ";
        cin >> username;
        cout << "Enter a password: ";
        cin >> password;

        bool found = false;
        for (user u : this->users) {
            if (u.getName() == username)
            {
                found = true;
                cout << "\n***User name already exists! please pick another one ***" << endl;
                break;
            }
        }
        if (!found) {
            break;
        }
    }
    cout << "\n\t***Registration Successfull***" << endl;
    this->usr.setName(username);
    this->usr.setPassword(password);
    this->users.push_back(usr);
    driver();
}
void Console::landingPage()
{
    int input;

    cout << "\n============================================ WELCOME ============================================" << endl;

    cout << "\nOptions:" << endl;
    cout << "1. Login" << endl
         << "2. Register" << endl
         << "3. Exit" << endl;

    cout << "Enter Your Choice: ";
    cin >> input;
    while (input < 1 || input > 3)
    {
        cout << "Invalid choice please try again" << endl;
        cout << "Enter Your Choice: ";
        cin >> input;
    }
    switch (input)
    {
    case 1:
        Login();
        break;
    case 2:
        Register();
        break;
    case 3:
        break;
    }
}

void Console::add_event()
{
    event e;
    string name, place;
    int day, month, year, hours, minutes;
    cout << "\n---Enter EVENT details---\n";

    cout << "Enter event name: ";
    cin >> name;
    e.setName(name);

    cout << "Enter event place: ";
    cin >> place;
    e.setPlace(place);

    cout << endl;
    while (true)
    {

        cout << "---Enter EVENT START DATE---\n";
        cout << "  Enter the day: ";
        cin >> day;
        cout << "  Enter the month: ";
        cin >> month;
        cout << "  Enter the year: ";
        cin >> year;
        cout << "  **Enter time in 24h format** \n";
        cout << "  Enter the hour: ";
        cin >> hours;
        cout << "  Enter the minute: ";
        cin >> minutes;
        if (!check_date(day, month, year, minutes, hours))
        {
            cout << "\n**Incorrect data, try again!**" << endl;
        }
        else
        {
            e.setStartDate(day, month, year, hours, minutes);
            break;
        }
    }
    cout << endl;
    while (true)
    {

        cout << "---Enter EVENT END DATE---\n";
        cout << "  Enter the day: ";
        cin >> day;
        cout << "  Enter the month: ";
        cin >> month;
        cout << "  Enter the year: ";
        cin >> year;
        cout << "  **Enter time in 24h format** \n";
        cout << "  Enter the hour: ";
        cin >> hours;
        cout << "  Enter the minute: ";
        cin >> minutes;

        if (!check_date(day, month, year, minutes, hours))
        {
            cout << "\n**Incorrect data, try again!**" << endl;
        }
        else
        {
            e.setEndDate(day, month, year, hours, minutes);
            if (dateTimeGenerator::compTime(e.getEndDate(), e.getStartDate()) != 1)
            {
                cout << "***(INVALID!)END date smaller than or equal START date***" << endl;
                continue;
            }
            else
            {
                break;
            }
        }
    }
    cout << endl;
    while (true)
    {
        cout << "---Enter EVENT REMINDER DATE---\n";
        cout << "  Enter the day: ";
        cin >> day;
        cout << "  Enter the month: ";
        cin >> month;
        cout << "  Enter the year: ";
        cin >> year;
        cout << "  **Enter time in 24h format** \n";
        cout << "  Enter the hour: ";
        cin >> hours;
        cout << "  Enter the minute: ";
        cin >> minutes;

        if (!check_date(day, month, year, minutes, hours))
        {
            cout << "\n**Incorrect data, try again!**" << endl;
        }
        else
        {
            e.setReminder(day, month, year, hours, minutes);
            if (dateTimeGenerator::compTime(e.getReminderDate(), e.getStartDate()) != -1) 
            {
                cout << "\n***(INVALID!)reminder date greater than or equal startDate***" << endl;
                continue;
            }
            else
            {
                break;
            }
        }
    }
    sort(this->usr.events.begin(), this->usr.events.end(), sortComparator);
    if (canBeAdded(e, this->usr.events))
    {
        this->usr.addEvent(e);
        cout << "Added!" << endl;
    }
    else {
        cout << "***ERROR! conflicting with existing events***";
    }
}


bool Console::check_date(int day, int month, int year, int minutes, int hours)
{
    tm t = dateTimeGenerator::getDateTime();
    int currYr = t.tm_year;
    int currD = t.tm_mday;
    int currMon = t.tm_mon;
    int currHour = t.tm_hour;
    int currMin = t.tm_min;
    if (
        (month > 12) || (month < 1) || (day < 1) || (day > 31) || (minutes < 0) || (hours < 0) || (hours > 24)||
        (year < currYr) || 
        ((year == currYr) && (month < currMon)) ||
        ((year == currYr) && (month == currMon) && (day < currD)) ||
        ((year == currYr) && (month == currMon) && (day == currD) && (hours<currHour)) || 
        ((year == currYr) && (month == currMon) && (day == currD) && (hours == currHour)) && (minutes < currMin)) 
        return 0;

    return 1;
}
void Console::del_event() {
    if (this->usr.events.empty()) {
        cout << "\nYou do not have any events to delete!\n";
        return;
    }
    sort(this->usr.events.begin(), this->usr.events.end(), sortComparator);
    cout << "\nYour Events: \n";
    for (int i = 0; i < this->usr.events.size(); i++) {
        cout << i + 1 << "- ";
        this->usr.events[i].getInfo();
        cout << endl;
    }
    cout << "Enter number of event to delete: ";
    int num;
    cin >> num;
    while (num<=0 || num>this->usr.events.size()) {
        cout << "Enter valid number: ";
        cin >> num;
    }
    num--;
    this->usr.events.erase(this->usr.events.begin() + num);
    cout << "Successfully deleted event!" << endl;
}
void Console::disp_done_event() {
    if (this->usr.events.empty()) {
        cout << "\nYou do not have any done events!\n";
        return;
    }
    this->usr.checkDoneEvents();
    if (this->usr.doneEvents.empty()) {
        cout << "\nYou do not have any done events!\n";
        return;
    }
    this->usr.displayDoneEvents(this->usr.doneEvents);
}
void Console::disp_event() { 
    if (this->usr.events.empty())
    {
        cout << "\nYou do not have any upcoming events!\n";
        return;
    }
    int startDate;
    while (true)
    {
        cout << "Press 0 to sort by start date or 1 to sort by reminder date: ";
        cin >> startDate;
        if (startDate == 1) {
            sort(this->usr.events.begin(), this->usr.events.end(), sortbyReminderComparator);
            break;
        }
        else if (startDate == 0) {
            sort(this->usr.events.begin(), this->usr.events.end(), sortComparator);
            break;
        }
    }

    this->usr.displayEvents();
}

void Console::update_event() {

    if (this->usr.events.empty()) {
        cout << "\nYou do not have any events to update!\n";
        return;
    }
    cout << "Your events: \n";
    for (int i = 0; i < this->usr.events.size(); i++) {
        cout << i + 1 << "- ";
        this->usr.events[i].getInfo();
        cout << endl;
    }
    cout << "Enter number of event to update: ";
    int num;
    cin >> num;
    while (num<0 || num > this->usr.events.size()) {
        cout << "Enter valid number: ";
        cin >> num;
    }
    num--;
    usr.updateEvent(this->usr.events[num]);

   /* event e;
    cout << "Please Enter The Event Name" << endl;
    string name; cin >> name;
    cout << "Please Enter The Event Place" << endl;
    string place; cin >> place;
    cout << "Please Enter The Event Start Date :" << endl;
    cout << "Day:" << endl;
    int day, month, year, hour, minutes;
    cin >> day;
    cout << "Month:" << endl;
    cin >> month;
    cout << "Year" << endl;
    cin >> year;
    cout << "Hour:" << endl;
    cin >> hour;
    cout << "Minutes:" << endl;
    cin >> minutes;
    e.setStartDate(day, month, year, hour, minutes);
    e.setName(name);
    usr.updateEvent(e);
   */
}
Console::~Console() {}