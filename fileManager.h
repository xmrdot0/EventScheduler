#ifndef __fManager__
#define __fManager__

#include <vector>
#include <string>
#include "event.h"
#include "user.h"
using namespace std;

class fileManager
{
public:
    bool dirExists(string dirName_in);
    string openF(string userName);
    static void readEvents(vector<event> &events, string userName);
    static void writeEvents(vector<event> &events, string userName);
    static void writeUsers(vector<user> users);
    static void readUsers(vector<user> &users);
};
#endif