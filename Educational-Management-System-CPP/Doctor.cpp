#include "Doctor.h"
#include<sstream>





Doctor::Doctor(int id, std::string name, std::string username, std::string email, std::string password) :User(id, name, username, email, password) {

}

std::string Doctor::ToString()const {
	std::ostringstream oss;
	oss << "2|";
	oss << Get_UserID();
	oss << "|";
	oss << Get_Name();
	oss << "|";
	oss << Get_User_name();
	oss << "|";
	oss << Get_Email();
	oss << "|";
	oss << Get_Password();
	return oss.str();

}

std::vector<std::string>Doctor::Get_Menu()const {
	std::vector<std::string> Doctor_DashBoard;
	std::string sentence;
	sentence = "List My Courses";
	Doctor_DashBoard.push_back(sentence);
	sentence = "Create Course";
	Doctor_DashBoard.push_back(sentence);
	sentence = "Add Assignment";
	Doctor_DashBoard.push_back(sentence);
	sentence = "View Solutions";
	Doctor_DashBoard.push_back(sentence);
	sentence = "Grade Solution";
	Doctor_DashBoard.push_back(sentence);
	sentence = "Log out";
	Doctor_DashBoard.push_back(sentence);
	return Doctor_DashBoard;
}



void Doctor::Add_Course_Code(std::string code) {
	CoursesCodes.push_back(code);
}


std::vector<std::string>Doctor::Get_Courses_Codes()const {
	return CoursesCodes;
}


std::vector<std::string> Doctor::Course_Details_Dash_Board() {
	std::string sentence;
	std::vector<std::string> Dash_Board;
	sentence = "Add Assignments";
	Dash_Board.push_back(sentence);
	sentence = "View/Grade Assignments";
	Dash_Board.push_back(sentence);
	sentence = "List Students";
	Dash_Board.push_back(sentence);
	sentence = "Back";
	Dash_Board.push_back(sentence);
	return Dash_Board;
}


std::vector<std::string>Doctor::Get_Course_Details(Course* course) {
	std::vector<std::string> Details;
	std::ostringstream oss;
	// Header
	oss << course->Get_CourseName();
	oss << " - " << course->Get_Code() << "\n";
	Details.push_back(oss.str());
	oss.str("");
	oss.clear();



	oss << "Registered Students: " << course->Registered_Students << "\n";
	oss << "Active Assignments: " << course->Get_Active_Assignments() << "\n";
	Details.push_back(oss.str());
	oss.str(""); oss.clear();
	oss << "List of Assignments: \n";
	if (course->Get_Assignments().empty()) {
		oss << "Has no Assignments yet\n";
		Details.push_back(oss.str());
		return Details;

	}
	auto& Assignments = course->Get_Assignments();
	int i = 1;
	for (auto& c : Assignments) {
		oss << i << ". Assignment " << i << " [" << c->Get_solutions().size()
			<< "/" << course->Registered_Students << "] Submitted - ["
			<< c->Get_Graded_Solutions() << " Graded]";
		Details.push_back(oss.str());
		oss.str(""); oss.clear();
		oss << "[ID: " << c->Get_Assignment_ID() << "]\n";
		Details.push_back(oss.str());
		oss.str(""); oss.clear();
		i++;
	}

	return Details;
}









Doctor::~Doctor() {}