#include "User.h"
#include <iostream>
#include<string>
#include<sstream>
#include<fstream>
#include"questions.h"

#include <limits>
using namespace std;


int last_id = 0;
map<string, Users> UserData;
int SignUp() {

    Users new_user;
    string temp;
    cout << "Enter user name.(No Spaces): ";
    while (true) {
        cin >> temp;
        auto uniqueuser = UserData.find(temp);
        if (uniqueuser == UserData.end()) {
            new_user.user_name = temp;
            break;
        }
        else {
            cout << "user name already exsist. Enter another one\n";
            cout << "Enter user name.(No Spaces): ";
        }

    }

    cout << "Enter password: ";
    cin >> new_user.password;
    cout << "Enter name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, new_user.name);
    cout << "Enter email: ";
    cin >> new_user.email;
    new_user.id = last_id + 1;
    last_id = new_user.id;
    

   
    bool value;

    value = get_valid_int("Allow anonymous questions?(0 or 1): ", 0, 1);
    new_user.anonymous = value;


    UserData[temp] = new_user;
    return new_user.id;

}

int login() {
    string UserName, password;
    cout << "Enter user name & password: ";
    cin >> UserName >> password;
   
    auto it = UserData.find(UserName);
    if (it != UserData.end()) {
        if (password == it->second.password) {
            cout << "Login successful. Welcome " << it->second.name << "!\n";
            return it->second.id;
        }
        else {
            cout << "User Data is wrong. Check user name or password\n";

        }

    }
    else {
        cout << "User is not found\n";
    }
    return -1;

}

void LoadData() {
    ifstream in("users.txt");
    if (in.fail()) {
        cerr << "Warning: couldn't open file, starting with empty data.\n";
        return;
    }
    UserData.clear();
   
    string line;
    while (getline(in, line)) {
        Users u2;
        if (line.empty())
            continue;
        istringstream iss(line);
        string field;
        getline(iss, field, '|'); 
        u2.id = stoi(field);
        getline(iss, field, '|');
        u2.user_name = field;
        getline(iss, field, '|'); 
        u2.password =field;
        getline(iss, field, '|'); 
        u2.name= field;
        getline(iss, field, '|');
        u2.email =field;
        getline(iss, field, '|');
        u2.anonymous = stoi(field);

        UserData[u2.user_name] = u2;
        last_id = max(last_id, u2.id);

    }
    in.close();
}

void SaveData() {
    ofstream out("users.txt");
    if (out.fail()) {
        cerr << "Warning: couldn't open file.\n";
        return;
    }
    for (pair<string, Users> x : UserData) {
        out << x.second.id << "|" << x.second.user_name << "|" << x.second.password << "|" << x.second.name << "|" << x.second.email << "|" << x.second.anonymous << endl;
    }

    out.close();
}
void list_users() {
    for (auto& u : UserData) {
        cout << "ID: " << u.second.id << "    Name: " << u.second.name << endl;
    }
}
