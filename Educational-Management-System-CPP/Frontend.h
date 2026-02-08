#ifndef FRONTEND_
#define FRONTEND_
#include"Backend.h"
class Frontend
{
public:
	Frontend(Backend& optimizer) :sys(optimizer) {}
	int MainMenu();
	int ViewUserDashboard();
	void Create_Course();
	void Register_In_Course();
	void View_Course();
	void List_Courses();
	void Add_Assignment(std::string code = "");
	void Submit_Solution(std::string code, int assignmentid);
	int ExecuteDash(int choice, User* current_user, std::string code = "");
	int ExecuteAction(int choice, User* current_user);
	int DocFlow(int chocie, User* current_user);
	int StudFlow(int choice, User* current_user);
	int DashStudFlow(int choice, User* current_user, std::string code = "");
	int DashDocFlow(int choice, User* current_user, std::string code = "");
	std::pair<std::string, int> View_Solutions(std::string code = "", int id = -1);
	void View_Solution(std::string code, int AssignmentID, int studentID);
	void List_Students(std::string code);
	void Grade_Solution(std::string code = "", int id = -1);
	bool Handle_Overwrite_Choice();
	void View_Grades_Report();
	void UnRegister_From_Course(std::string code);


private:
	bool valid_input(int st, int ed, int choice) {
		return choice >= st && choice <= ed;
	}
	std::string trim(const std::string& str) {
		size_t first = str.find_first_not_of(" \t\n\r");
		if (std::string::npos == first) return "";

		size_t last = str.find_last_not_of(" \t\n\r");
		return str.substr(first, (last - first + 1));
	}
	std::string convert_to_low(std::string x) {
		std::string res = "";
		for (int i = 0; i < x.size(); i++) {
			res += tolower(x[i]);
		}
		return res;
	}
	Backend& sys;
};


#endif