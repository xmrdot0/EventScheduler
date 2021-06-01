#ifndef __console__
#define __console__
#include <vector>
#include "user.h"

using namespace std;

class Console
{
public:
    user usr;
    vector<user> users;
  //  void update_menu(event& e);

public:
    Console(vector<user> &users);
    ~Console();
    void Login();
    void driver();
    int mainMenu();
    void Register();
    void landingPage();
    void add_event();
    void del_event();
    void disp_event();
    void update_event();
    bool check_date(int day, int month, int year, int minutes, int hours);
};
#endif