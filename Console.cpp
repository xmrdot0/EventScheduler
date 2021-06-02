#define _CRT_NONSTDC_NO_DEPRECATE
#define _CRT_SECURE_NO_DEPRECATE 
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Console.h"
#include "user.h"
#include "event.h"
#include <vector>
#include "dateTimeGenerator.cpp"
using namespace std;

Console::Console(vector<user> &users)
{
    this->users = users;
    landingPage();
}

void Console::Login()
{
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;
    // check the user name and password in the users datastructure
    //else print "the username or password is incorrect please try again"
    //this->user = usr
    driver();
}

void Console::driver()
{
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
            exit = true;
            break;
        }
        cout << "\n***Successfull!***\n";
        // check all events for completed -check
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
         << "4. Display events" << endl
         << "5. Exit" << endl;
    cout << "Enter Your Choice: ";

    cin >> input;
    while (input < 1 || input > 5)
    {
        cout << "Invalid input please try again" << endl;
        cin >> input;
    }
    return input;
}

void Console::Register()
{
    string username, password;
    cout << "Enter a username: ";
    cin >> username;
    cout << "Enter a password: ";
    cin >> password;
    // create new user
    cout << "\n\t***Registration Successfull***" << endl;
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
    string name, place;
    int day, month, year, hours, minutes;
    cout << "\n---Enter EVENT details---\n";

    cout << "Enter event name: ";
    getline(cin, name);
    //cin >> name;
    cin.ignore();
    cout << "Enter event place: ";
    getline(cin, place);
    cin.ignore();
    //cin >> place;
    cout << endl;

    event e;
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
            e.setStartDate(day, month, year, minutes, hours);
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
            e.setEndDate(day, month, year, minutes, hours);
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
            e.setReminder(day, month, year, minutes, hours);
            if (dateTimeGenerator::compTime(e.getReminderDate(), e.getEndDate()) != -1) //bug here, reminder date can be greater than end date???
            {
                cout << "\n***(INVALID!)reminder date greater than or equal endDate***" << endl;
                continue;
            }
            else
            {
                break;
            }
        }
    }
    //call @yehia's checker function, if true:
    this->usr.addEvent(e);
}

bool canBeAdded(event newEvent, vector<event> events) {
    dateTimeGenerator T;
    for (int i=0; i< events.size(); i++)
    {
        if (T.compTime(newEvent.getStartDate(),events[i].getEndDate()) == 1)
            return true;
        else if (T.compTime(newEvent.getEndDate(), events[i].getStartDate()) == -1)
            return true;
        return false;

    }
}


bool Console::check_date(int day, int month, int year, int minutes, int hours)
{
    int currYr = dateTimeGenerator::getYear();
    int currD = dateTimeGenerator::getDay();
    int currMon = dateTimeGenerator::getMonth();

    if (
        (year < currYr) || (month > 12) || (month < 1) || (day < 1) || (day > 31) ||
        ((year == currYr) && (month == currMon) && (day < currD)) ||
        ((year == currYr) && (month < currMon)) || (minutes < 0) || (hours < 0))
        return 0;

    return 1;
}
void Console::del_event() {}

void Console::disp_event() { this->usr.displayEvents(); }

void Console::update_event() {
    event e;
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
} // TODO:: youssef ayman

Console::~Console() {}