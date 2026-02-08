#include "UserManager.h"
#include"User.h"
#include"Student.h"
#include"Doctor.h"
#include<stdexcept>
#include<sstream>
#include<fstream>

int UserManager::user_count = 0;


bool UserManager::IsUserExist(std::string username)const {
	return UserData.count(username);
}

std::vector<std::string>UserManager::Get_Course_Details(Course* course, User* current_user) {
	return current_user->Get_Course_Details(course);


}
User* UserManager::Add_User(int type, std::string name, std::string username, std::string email, std::string password, double gpa) {
	int lastid = user_count++;
	User* user = nullptr;
	if (type == 1) {

		user = new Student(lastid, name, username, email, password, gpa);

	}
	else if (type == 2) {
		user = new Doctor(lastid, name, username, email, password);

	}
	UserData[username] = user;
	return user;

}

User* UserManager::ValidUser(std::string username, std::string password) {
	auto it = UserData.find(username);
	if (it->second->Get_Password() != password) {
		throw std::invalid_argument("Invalid password! Access Denied.");
	}
	return it->second;
}

std::vector<std::string>UserManager::Get_DashBoard(User* current_user)const {
	return current_user->Get_Menu();
}

void UserManager::Load_Users_Data() {
	std::ifstream fin("UsersData.txt");
	if (fin.fail()) {
		return;
	}

	UserData.clear();
	std::string line;
	User* user = nullptr;
	int type, id;
	std::string name, username, email, password;
	double Gpa;
	while (getline(fin, line)) {
		if (line.empty()) {
			continue;
		}

		std::istringstream iss(line);
		std::string field;
		getline(iss, field, '|');
		type = stoi(field);
		getline(iss, field, '|');
		id = stoi(field);
		getline(iss, field, '|');
		name = field;
		getline(iss, field, '|');
		username = field;
		getline(iss, field, '|');
		email = field;
		getline(iss, field, '|');
		password = field;
		if (type == 1) {
			getline(iss, field, '|');
			Gpa = stod(field);
			user = new Student(id, name, username, email, password, Gpa);
		}
		else {
			user = new Doctor(id, name, username, email, password);
		}




		UserData[username] = user;
		if (id >= user_count) {
			user_count = id + 1;
		}
	}
}

void UserManager::Save_Users_Data() {
	std::ofstream fout("UsersData.txt");
	if (fout.fail()) {
		return;
	}
	for (auto& pair : UserData) {
		fout << pair.second->ToString() << "\n";
	}


	fout.close();
}

bool UserManager::Register_In_Course(std::string code, User* current_user) {
	Student* studentPtr = dynamic_cast<Student*>(current_user);
	bool status;
	if (studentPtr != nullptr)
		status = studentPtr->Register_Course(code);

	else
		return false;
	return status;

}

User* UserManager::Get_User_byID(int id) {
	for (auto& pair : UserData) {
		if (pair.second->Get_UserID() == id) {
			return pair.second;
		}
	}
	return nullptr;
}

void UserManager::Load_Student_Courses() {
	std::ifstream fin("Stud_Course_Data.txt");

	if (fin.fail()) {
		return;
	}
	int studId;

	std::string line;
	while (getline(fin, line)) {
		if (line.empty()) continue;
		std::istringstream iss(line);
		std::string field;

		getline(iss, field, '|');
		if (field.empty()) continue;
		studId = stoi(field);
		Student* studentPtr = dynamic_cast<Student*>(Get_User_byID(studId));

		if (studentPtr != nullptr) {
			while (getline(iss, field, '|')) {
				if (field.empty()) continue;
				studentPtr->Register_Course(field);


			}

		}




	}




	fin.close();


}

void UserManager::Save_Student_Courses() {
	std::ofstream fout("Stud_Course_Data.txt");
	if (fout.fail()) {
		return;
	}
	for (auto& pair : UserData) {
		Student* studentPtr = dynamic_cast<Student*>(pair.second);
		if (studentPtr != nullptr && !studentPtr->Get_Registered_Courses().empty()) {
			fout << studentPtr->Get_UserID() << "|";
			std::vector<std::string> stud_courses = studentPtr->Get_Registered_Courses();
			for (std::string code : stud_courses) {
				fout << code << "|";
			}
			fout << "\n";

		}

	}
	fout.close();

}



void UserManager::Add_Course_In_DR_List(User* current_user, std::string code) {
	Doctor* current_dr = dynamic_cast<Doctor*>(current_user);
	if (current_dr) {
		current_dr->Add_Course_Code(code);
	}

}



std::vector<std::string>  UserManager::Get_User_CourseCodes(User* current_user)const {
	std::vector<std::string> codes = current_user->Get_Courses_Codes();
	return codes;
}


std::vector<std::string> UserManager::Get_Course_Details_DashBoard(User* current_user) {
	std::vector<std::string>  Dash = current_user->Course_Details_Dash_Board();
	return Dash;
}






bool UserManager::IsRegistered(Student* stud, std::string code) {

	return stud->IsRegistered_In_Course(code);
}




std::vector<Student*>UserManager::Get_All_Students()const {
	std::vector<Student*> res;
	for (const auto& stud : UserData) {
		Student* studPtr = dynamic_cast<Student*>(stud.second);
		if (studPtr != nullptr) {
			res.push_back(studPtr);
		}
	}
	return res;
}


std::pair<int, std::pair<std::string, double>> UserManager::Get_User_Data(User* current_user) {
	Student* stud = dynamic_cast<Student*>(current_user);
	if (stud == nullptr) {
		throw std::runtime_error("User is not found");
	}
	return stud->Student_Data();
}


void UserManager::Handle_User_Unregisteration(std::string code, Student* current_user) {

	current_user->Unregister_From_Course(code);
}



UserManager::~UserManager() {
	for (auto& pair : UserData) {
		delete pair.second;
	}
	UserData.clear();
}