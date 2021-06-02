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

    //read for our main user only? save processing power
    /* for (user usr : users) //@yehia
         fileManager::readEvents(usr.events, usr.getName());*/

    //main program
    Console c(users);

    //save data
    fileManager::writeUsers(users);
    // for (user usr : users)
    //     fileManager::writeEvents(usr.<events>, usr.getName());
}