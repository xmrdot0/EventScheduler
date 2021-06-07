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
    //sort by start date
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
        getline(cin,username);
        cout << "Enter password: ";
        cin >> password;
        getline(cin, password);
        int i;
        for (i=0 ; i < users.size(); i++) {
            if (users[i].getName() == username && users[i].getPassword() == password)
            {
                success = true;
                this->usr = users[i];
                break;
            }
        }
        if (success) {
            now = i;
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
    fileManager::readEvents(this->users[now].events, users[now].getName());
    bool exit = false;
    while (!exit)
    {
        switch (Console::mainMenu())
        {
        case 1:
            add_event();
            break;
        case 2:
            updateEvent();
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
            break;
        case 7:
            exit = true;
            break;
        }
   
        this->users[now].checkDoneEvents();
        this->users[now].checkReminders();
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
        << "6. Refresh" << endl
        << "7. Exit" << endl;
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
        cout << "Enter Name: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;
       

        int i;
        bool found = false;
        for ( i = 0; i<this->users.size() ; i++) {
            if (users[i].getName() == username)
            {
                found = true;
                cout << "\n***User name already exists! please pick another one ***" << endl;
                break;
            }
        }
        if (!found) {
            now = i;
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
    sort(this->users[now].events.begin(), this->users[now].events.end(), sortComparator);
    if (canBeAdded(e, this->users[now].events))
    {
        this->users[now].addEvent(e);
   //     this->users[now] = usr;
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
void Console::disp_done_event() {
    if (this->users[now].doneEvents.empty()) {
        cout << "\nYou do not have any done events!\n";
        return;
    }
   /* this->usr.checkDoneEvents();
    if (this->users[now].doneEvents.empty()) {
        cout << "\nYou do not have any done events!\n";
        return;
    }*/

    this->users[now].displayDoneEvents(this->users[now].doneEvents);
}
void Console::disp_event() { 
    if (this->users[now].events.empty())
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
            sort(this->users[now].events.begin(), this->users[now].events.end(), sortbyReminderComparator);
            break;
        }
        else if (startDate == 0) {
            sort(this->users[now].events.begin(), this->users[now].events.end(), sortComparator);
            break;
        }
    }

    this->users[now].displayEvents();
}

void  Console::updateEvent() {
   
    event e;
        cout << "Please Enter The Event Name" << endl;
        string name; cin >> name;
        e.setName(name);
        cout << "Please Enter The Event Place" << endl;
        string place; cin >> place;
        e.setPlace(place);

    if (this->users[now].events.empty()) {
                cout << "\nYou do not have any events to update!\n";
                return;
            }

       bool found = true;
       for (int i=0 ; i<users[now].events.size() ; i++)
       {
           if (users[now].events[i]==e)
              this->update_menu(users[now].events[i],i);
          
         else
           found=false;
       }
       if (!found)
       cout<<"Sorry... This event doesn't exist !"<<endl;
    
    }

void Console:: update_menu(event &e, int x){
   int c; 
    cout <<"Please Enter Your choice:";
    cout<<"1: Update The Name"<<endl<<"2: Update The Place"<<endl
    <<"3: Update The Start Date"<<endl
    <<"4: Update The End date"<<endl
    <<"5: Update The Reminder date"<<endl;
    cin>>c;
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
        cout<<"Enter The New name"<<endl;
        cin>>name;
        users[now].events[x].setName(name);
        cout << "Updated..." << endl;
        break;
    case 2:
        cout<<"Enter The New Place"<<endl;
        cin>>name;
        users[now].events[x].setPlace(name);
        cout << "Updated..." << endl;
        break;
    case 3:
       cout<<"Enter The day"<<endl;
       cin>>day;
       cout<<"Enter The Month"<<endl;
       cin>>month;
       cout<<"Enter The Year"<<endl;
       cin>>year;
       cout<<"Enter The Hour"<<endl;
       cin>>hour;
       cout<<"Enter The Minute"<<endl;
       cin >> minutes;
       users[now].events[x].setStartDate( day,  month, year, hour, minutes);
       cout << "Updated..." << endl;
        break;
    case 4:
        cout << "Enter The day" << endl;
        cin >> day;
        cout << "Enter The Month" << endl;
        cin >> month;
        cout << "Enter The Year" << endl;
        cin >> year;
        cout << "Enter The Hour" << endl;
        cin >> hour;
        cout << "Enter The Minute" << endl;
        cin >> minutes;
        cout << "Updated..." << endl;
        users[now].events[x].setEndDate(day, month,  year, hour,minutes);
        break;  
    case 5:
        cout << "Enter The day" << endl;
        cin >> day;
        cout << "Enter The Month" << endl;
        cin >> month;
        cout << "Enter The Year" << endl;
        cin >> year;
        cout << "Enter The Hour" << endl;
        cin >> hour;
        cout << "Enter The Minute" << endl;
        cin >> minutes;       
        users[now].events[x].setStartDate(day, month, year, hour, minutes);
        cout << "Updated..." << endl;
        break;   

    }
}






void Console::del_event() {

    event e;
    cout << "Please Enter The Event Name That You Want To Delete:" << endl;
    string name; cin >> name;
    e.setName(name);
    cout << "Please Enter The Event Place That You Want To Delete:" << endl;
    string place; cin >> place;
    e.setPlace(place);

    if (this->users[now].events.empty()) {
        cout << "\nYou do not have any events to Delete!\n";
        return;
    }

    bool found = true;
    for (int i = 0; i < users[now].events.size(); i++)
    {
        if (users[now].events[i] == e)
        {
            users[now].doneEvents.push(users[now].events[i]);
            this->users[now].events.erase(this->users[now].events.begin() + i);
            cout << "Successfully deleted event!" << endl;
            break;
        }
        else
            found = false;
    }
    if (!found)
        cout << "Sorry... This event doesn't exist !" << endl;

}



//void Console::del_event() {
//    if (this->users[now].events.empty()) {
//        cout << "\nYou do not have any events to delete!\n";
//        return;
//    }
//    sort(this->users[now].events.begin(), this->users[now].events.end(), sortComparator);
//    cout << "\nYour Events: \n";
//    for (int i = 0; i < this->users[now].events.size(); i++) {
//        cout << i + 1 << "- ";
//        this->users[now].events[i].getInfo();
//        cout << endl;
//    }
//    cout << "Enter number of event to delete: ";
//    int num;
//    cin >> num;
//    while (num<=0 || num>this->users[now].events.size()) {
//        cout << "Enter valid number: ";
//        cin >> num;
//    }
//    num--;
//    this->users[now].events.erase(this->users[now].events.begin() + num);
//  //  this->users[now] = usr;
//    cout << "Successfully deleted event!" << endl;
//}

Console::~Console() {}