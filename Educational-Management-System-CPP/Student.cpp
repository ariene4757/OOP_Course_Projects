#include "Student.h"
#include"User.h"
#include<stdexcept>
#include<sstream>




Student::Student(int id, std::string name, std::string username, std::string email, std::string password, double gpa) :User(id, name, username, email, password), GPA(gpa) {

}

double Student::Get_GPA()const {
	return GPA;
}

std::string Student::ToString()const {
	std::ostringstream oss;
	oss << "1|";
	oss << Get_UserID();
	oss << "|";
	oss << Get_Name();
	oss << "|";
	oss << Get_User_name();
	oss << "|";
	oss << Get_Email();
	oss << "|";
	oss << Get_Password();
	oss << "|";
	oss << Get_GPA();
	return oss.str();

}

std::vector<std::string> Student::Get_Menu()const {
	std::vector<std::string>Student_DashBoard;
	std::string sentence;

	sentence = "Register in Course";
	Student_DashBoard.push_back(sentence);
	sentence = "List My Courses";
	Student_DashBoard.push_back(sentence);
	sentence = "View Course";
	Student_DashBoard.push_back(sentence);
	sentence = "Grades report";
	Student_DashBoard.push_back(sentence);
	sentence = "Log out";
	Student_DashBoard.push_back(sentence);
	return Student_DashBoard;

}

std::vector<std::string>Student::Get_Registered_Courses()const {
	return Registered_Courses;
}

bool Student::Register_Course(std::string code) {
	for (const auto& c : Registered_Courses) {
		if (code == c) {
			return false;
		}
	}

	Registered_Courses.push_back(code);

	return true;
}

std::vector<std::string>Student::Get_Courses_Codes()const {
	return Registered_Courses;
}

std::vector<std::string> Student::Course_Details_Dash_Board() {
	std::string sentence;
	std::vector<std::string> Dash_Board;

	sentence = "UnRegister from Course";
	Dash_Board.push_back(sentence);
	sentence = "Submit solution";
	Dash_Board.push_back(sentence);
	sentence = "Back";
	Dash_Board.push_back(sentence);
	return Dash_Board;
}

std::vector<std::string> Student::Get_Course_Details(Course* course) {
	std::ostringstream oss;
	std::vector<std::string> Details;

	oss << "Course " << course->Get_CourseName() << " with code " << course->Get_Code() << " - "
		<< "By " << course->Get_Dr_Name() << "\n";
	Details.push_back(oss.str());
	oss.str(""); oss.clear();

	oss << "Course has " << course->Get_Assignments().size() << " assignments\n";
	Details.push_back(oss.str());
	oss.str(""); oss.clear();

	auto& assignments = course->Get_Assignments();
	int i = 1;
	for (auto& temp : assignments) {
		oss << "Assignment " << i;
		i++;
		bool found = false;
		Solution* mySol = nullptr;
		auto& sols = temp->Get_solutions();

		for (auto& sol : sols) {
			if (sol->Get_Student_ID() == Get_UserID()) {
				found = true;
				mySol = sol;
				break;
			}
		}
		if (found) {
			oss << " submitted - ";
			if (mySol->Get_Grade() == -1) {
				oss << "NA";
			}
			else {
				oss << mySol->Get_Grade();
			}
		}
		else {
			oss << " NOT submitted - NA";
		}
		oss << "/" << temp->Get_Max_Grade() << " [ID: " << temp->Get_Assignment_ID() << "]\n";
		Details.push_back(oss.str());
		oss.str(""); oss.clear();


	}

	return Details;
}

bool Student::IsRegistered_In_Course(std::string code) {
	const auto& codes = Get_Registered_Courses();
	for (const auto& subcode : codes) {
		if (code == subcode) {
			return true;
		}
	}
	return false;
}


std::pair<int, std::pair<std::string, double>> Student::Student_Data() {

	std::pair<int, std::pair<std::string, double>>  data;

	data.first = this->Get_UserID();

	data.second.first = this->Get_Name();
	data.second.second = this->Get_GPA();

	return data;
}

bool Student::Unregister_From_Course(std::string code) {

	for (auto i = Registered_Courses.begin(); i != Registered_Courses.end(); i++) {
		if (*i == code) {

			Registered_Courses.erase(i);
			return true;
		}
	}
	return false;
}


Student::~Student() {}