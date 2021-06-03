#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE 
#define _CRT_NONSTDC_NO_DEPRECATE
#include <iostream>
#include <vector>
#include "event.h"
#include "dateTimeGenerator.cpp"
#include "fileManager.cpp"
#include "Console.h"

using namespace std;
int main()
{
    //preprocessing
    vector<user> users;
    fileManager::readUsers(users);

    //main program
    Console c(users);

    cout << "users in main: " << users.size() << endl; // this doesnt work
    cout << "users in console from main: " << c.users.size() << endl;
   
    //save data
    fileManager::writeUsers(c.users);
    fileManager::writeEvents(c.usr.events,c.usr.getName());

}