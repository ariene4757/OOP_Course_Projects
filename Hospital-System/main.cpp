#include<iostream>
using namespace std;
const int MAX_SPECIALIZATION = 20;
const int MAX_QUEUE = 5;

string names[MAX_SPECIALIZATION + 1][MAX_QUEUE];
int statis[MAX_SPECIALIZATION + 1][MAX_QUEUE];
int queue_length[MAX_SPECIALIZATION + 1];

void add_patient() {

    string patient_name;
    int patient_statis, specialization;
    cout << "Enter specialization ,name ,statis: ";
    cin >> specialization >> patient_name >> patient_statis;
    if (specialization < 1 || specialization >20) {
        cout << "Invalid input.\n";
        return;
    }
    if (patient_statis != 0  && patient_statis != 1) {
        cout << "Invalid input.try again\n";
        return;
    }
    if (queue_length[specialization] == MAX_QUEUE) {
        cout << "Sorry we can not accept more patients in this specialization\n";
        return;
    }

    if (patient_statis) {
        for (int i = MAX_QUEUE - 1; i > 0; i--) {
            names[specialization][i] = names[specialization][i - 1];
            statis[specialization][i] = statis[specialization][i - 1];
        }
        names[specialization][0] = patient_name;
        statis[specialization][0] = patient_statis;


    }
    else {
        names[specialization][queue_length[specialization]] = patient_name;
        statis[specialization][queue_length[specialization]] = patient_statis;

    }
    queue_length[specialization]++;

}
void print() {
    cout << "****************************\n";
    for (int i = 1; i < 21; i++) {
        if (queue_length[i] == 0) {
            continue;
        }
        else {
            cout << "There are " << queue_length[i] << " in specialization " << i << endl;
            for (int j = 0; j < queue_length[i]; j++) {

                cout << names[i][j];
                if (statis[i][j] == 1) {
                    cout << " urgent\n";
                }
                else {
                    cout << " regular\n";
                }
            }

        }

    }
}
void get_patient() {
    int spe;
    cout << "Enter specialization: ";
    cin >> spe;
    if (queue_length[spe] == 0) {
        cout << "There are no patients in this specialization\n";
    }
    else {
        cout << names[spe][0] << " please do with the Dr\n";
        for (int i = 0; i < queue_length[spe] - 1; i++) {
            names[spe][i] = names[spe][i + 1];
            statis[spe][i] = statis[spe][i + 1];

        }
        queue_length[spe]--;

    }
}
int main() {
    int choice;
    while (true) {

        cout << "1) Add new patient\n\
2)Print all patients\n\
3)Get next patient\n\
4)Exit\n";
        cout << "Enter your choice:";
        cin >> choice;
        if (choice < 1 || choice >4) {
            cout << "Invalid input!\n Please try again.\n";
            continue;
        }
        if (choice == 1) {
            add_patient();
        }
        else if (choice == 2) {
            print();
        }
        else if (choice == 3) {
            get_patient();
        }
        else {
            cout << "Exiting the program....";
            return 0;
        }

    }
}
