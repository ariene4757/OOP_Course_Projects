#include "SYSTEM.h"
#include "User.h"
#include "Question.h"
#include <sstream>
#include <iostream>
#include <fstream>

using namespace std;

SYSTEM::SYSTEM() : Foptimizer(&Boptimizer) {
}

void SYSTEM::Run() {

	Boptimizer.LoadDatabase();

	while (true) {
		//Enter loop
		while (true) {
			int current_user = Foptimizer.ShowMainMenuAndLogin();

			if (current_user == -1) {
				cout << "User is not found, Please Sign Up first.\n";
			}
			else if (current_user == -100) {
				cout << "Goodbye!\n";
				Boptimizer.SaveDatabase();
				return;
			}
			else {
				Boptimizer.Set_Current_User(current_user);
				Boptimizer.SaveDatabase();
				break;
			}
		}

		//Menu loop
		while (true) {
			int choice = Foptimizer.ShowUserMenu();

			if (choice == 1) {

				Foptimizer.Print_Received_Questions();
			}
			else if (choice == 2) {
				Foptimizer.Print_User_Questions();
			}
			else if (choice == 3) {
				Foptimizer.Get_User_Answer();
			}
			else if (choice == 4) {
				Foptimizer.DeleteQuestion();
			}
			else if (choice == 5) {

				Foptimizer.AskQuestion();
			}
			else if (choice == 6) {
				Foptimizer.List_System_Users();
			}
			else if (choice == 7) {
				Foptimizer.List_Feed();
			}
			else {
				cout << "Logging out...\n";
				break;
			}
		}
	}
}