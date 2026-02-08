#ifndef FRONTEND_H_
#define FRONTEND_H_

#include"Backend.h"

class Frontend
{
public:
	int ShowMainMenuAndLogin();
	int  ShowUserMenu();
	Frontend(Backend* appBackend) {
		system = appBackend;
	}
	void AskQuestion();
	void Print_User_Questions();
	void Print_Thread_Recursive(const ThreadTree&, int);
	void Print_Received_Questions();
	void Get_User_Answer();
	void List_System_Users();
	void List_Feed();
	void DeleteQuestion();

private:
	std::string convert_into_lower(std::string& s) {
		std::string res = "";
		for (int i = 0; i < s.size(); i++)
			if (s[i] != ' ') {
				res += tolower(s[i]);
			}
		return res;
	}

	bool IsValidInput(int choice, int start, int end) {
		return (choice <= end && choice >= start);
	}
	Backend* system;
};

#endif 