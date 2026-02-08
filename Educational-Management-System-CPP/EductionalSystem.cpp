#include<iostream>
#include"System.h"
using namespace std;






int main() {
    try {
        System app;
        app.Run(); 
    }
    catch (const exception& e) {
        cout << "\n\n*****************************************\n";
        cout << "CRITICAL ERROR: " << e.what() << endl;
        cout << "The system stopped safely to prevent data corruption.\n";
        cout << "*****************************************\n";
    }
    catch (...) {
        cout << "Unknown Error occurred!\n";
    }
}