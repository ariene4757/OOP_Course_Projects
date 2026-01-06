#ifndef USER_H
#define USER_H
using namespace std;
#include <string>
#include <map>


struct Users {
    int id;
    bool anonymous;
    string user_name, name, password, email;
};


extern int last_id;
extern map<string, Users> UserData;


int SignUp();
int login();
void LoadData();
void SaveData();
void list_users();

#endif

