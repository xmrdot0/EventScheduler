#define _CRT_NONSTDC_NO_DEPRECATE
#define _CRT_SECURE_NO_DEPRECATE 
#define _CRT_SECURE_NO_WARNINGS
#include "user.h"
#include "event.h"
#include "dateTimeGenerator.cpp"
#include <iostream>
#include <algorithm>
using namespace std;

void user::addEvent(event e) {
    this->events.push_back(e);
}

void user::deleteEvent(event e) {}
 

void user::updateEvent(event e) {
   bool found = true;
   for (int i=0 ; i<events.size() ; i++)
   {
       if (events[i]==e)
          this->update_menu(events[i]);
      
     else
       found=false;
   }
   if (!found)
   cout<<"Sorry... This event doesn't exist !"<<endl;

}
bool sortComparator(event e1, event e2, bool start = 1) {
    if (start)
    {
        if (dateTimeGenerator::compTime(e1.getStartDate(), e2.getStartDate()) == 1)
            return 0;
        return 1;
    }
    else {
        if (dateTimeGenerator::compTime(e1.getReminderDate(), e2.getReminderDate()) == 1)
            return 0;
    }
}

void user::displayEvents() {
    cout << "\nUNSORTED:\n";
    for (event ev : this->events)
    {
        ev.getInfo();
    }
    cout << "\nSORTED:\n";
    sort(this->events.begin(), this->events.end(), &sortComparator);
    for (event ev : this->events)
    {
        ev.getInfo();
    }
}

string user::getName() { return this->userName; }
string user::getPassword() { return this->password; }

void user::setName(string name) { this->userName = name; }
void user::setPassword(string password) { this->password = password; }
void user::displayDoneEvents() {}

void user::checkReminders()
{
    for (event ev : this->events)
    {
        if (!ev.getReminded() && (dateTimeGenerator::compTime(ev.getReminderDate(), dateTimeGenerator::getDateTime()) == 0))
        {
            cout << "\n***REMINDER!***\n";
            ev.getInfo();
            ev.setReminded();
        }
    }
} 

void user:: update_menu(event &e){
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
      
        string name ;
        int day, month,  year,  hour, minutes;
    switch (c)
    {
        
    case 1:
        cout<<"Enter The New name"<<endl;
        cin>>name;
        e.setName(name);
        cout << "Updated..." << endl;
        break;
    case 2:
        cout<<"Enter The New Place"<<endl;
        cin>>name;
        e.setPlace(name);
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
       e.setStartDate( day,  month, year, hour, minutes);
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
        e.setEndDate(day, month,  year, hour,minutes);
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
        e.setStartDate(day, month, year, hour, minutes);
        cout << "Updated..." << endl;
        break;   

    }
}
 
// @yehia's checker(parameters)