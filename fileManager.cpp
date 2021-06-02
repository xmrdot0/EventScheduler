#ifndef __fManager__
#define __fManager__
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE 
#define _CRT_NONSTDC_NO_DEPRECATE
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "event.h"
#include "user.h"
#include <windows.h>
#include <direct.h>
using namespace std;

class fileManager
{
public:
    static bool dirExists(string dirName_in)
    {
        //checks if directory exists
        DWORD ftyp = GetFileAttributesA(dirName_in.c_str());
        if (ftyp == INVALID_FILE_ATTRIBUTES)
            return false;

        if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
            return true;

        return false;
    }
    static string openF(string userName)
    {
        //returns new directory if it doesnt exist
        string dirName = "Events\\";
        if (!dirExists(dirName))
        {
            const char *cstr = dirName.c_str();
            mkdir(cstr);
        }
        dirName.append(userName);
        if (!dirExists(dirName))
        {
            const char *cstr = dirName.c_str();
            mkdir(cstr);
        }
        return dirName;
    }
    static void readEvents(vector<event> &events, string userName)
    {
        ifstream file;
        string fileName = openF(userName).append("\\events.txt");
        file.open(fileName, ios::in);
        event currentEvent;
        int flag = 0;
        while (!file.eof())
        {

            string tmp;

            //getline(file, tmp);
            file >> tmp;
            if (tmp == "")
                break;
            currentEvent.setName(tmp);

            string tmp2;

            //getline(file,tmp2);
            file >> tmp2;
            currentEvent.setPlace(tmp2);

            int tmp3;
            file >> tmp2;
            currentEvent.setDone(tmp3);

            int day, month, year, hour, minutes;

            file >> day >> month >> year >> hour >> minutes;
            currentEvent.setStartDate(day, month, year, hour, minutes);

            file >> day >> month >> year >> hour >> minutes;
            currentEvent.setEndDate(day, month, year, hour, minutes);

            file >> day >> month >> year >> hour >> minutes;
            currentEvent.setReminder(day, month, year, hour, minutes);

            events.push_back(currentEvent);
        }
        file.close();
    };
    static void writeEvents(vector<event> &events, string userName)
    {
        ofstream file;

        string fileName = openF(userName).append("\\events.txt");
        file.open(fileName, ios::out);

        int flag = 0;
        for (event e : events)
        {
            tm startDate = e.getStartDate();
            tm endDate = e.getEndDate();
            tm reminder = e.getReminderDate();

            file << e.getName() << endl
                 << e.getPlace() << endl
                 << e.getDone() << endl
                 << startDate.tm_mday << " " << startDate.tm_mon << " " << startDate.tm_year << " " << startDate.tm_hour << " " << startDate.tm_min << endl
                 << endDate.tm_mday << " " << endDate.tm_mon << " " << endDate.tm_year << " " << endDate.tm_hour << " " << endDate.tm_min << endl
                 << reminder.tm_mday << " " << reminder.tm_mon << " " << reminder.tm_year << " " << reminder.tm_hour << " " << reminder.tm_min;
            if (flag < events.size() - 1)
                file << endl;
            flag++;
        }
        file.close();
    };

    static void readUsers(vector<user> &users)
    {
        ifstream file("users.txt", ios::in);
        if (file.fail())
        {
            return;
        }
        user u;
        while (!file.eof())
        {
            string username, password;
            file >> username >> password;
            u.setName(username);
            u.setPassword(password);
            users.push_back(u);
        }
        file.close();
    }
    static void writeUsers(vector<user> users)
    {
        ofstream file;
        file.open("users.txt", ios::out);
        int flag = 0;
        for (user u : users)
        {
            file << u.getName() << endl
                 << u.getPassword();
            if (flag < users.size() - 1)
                file << endl;
            flag++;
        }
        file.close();
    }
};
#endif