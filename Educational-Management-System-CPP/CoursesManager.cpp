#include "CoursesManager.h"
#include "Course.h"
#include"User.h"
#include<sstream>
#include<fstream>
#include"DateTime.h"


int CoursesManager::Courses_Count = 0;


void CoursesManager::Add_Course(std::string CourseName, int id, std::string DrName, std::string CourseCode) {

	int newid = Courses_Count;
	Course* newcourse = new Course(newid, CourseName, id, DrName, CourseCode);
	CourseData[CourseCode] = newcourse;

	Courses_Count++;
}

bool CoursesManager::IsCourseExist(std::string Code) {
	if (CourseData.count(Code)) {
		return true;
	}
	return false;
}

void CoursesManager::LoadCourseData() {


	std::ifstream fin("CourseData.txt");
	if (fin.fail()) {
		return;
	}
	CourseData.clear();
	Courses_Count = 0;
	std::string line;
	Course* current_course = nullptr;
	Assignment* current_assignment = nullptr;

	while (getline(fin, line)) {
		if (line.empty()) continue;
		std::string segment;
		std::vector<std::string> parts;
		std::istringstream iss(line);
		while (getline(iss, segment, '|')) {
			if (segment.empty()) continue;
			parts.push_back(segment);
		}
		if (parts.empty()) continue;
		std::string type = parts[0];

		if (type == "CRS") {
			int id = stoi(parts[1]);
			std::string name = parts[2];
			int docId = stoi(parts[3]);
			std::string code = parts[4];
			std::string DrName = parts[5];
			int RegisteredSt = stoi(parts[6]);
			current_course = nullptr;
			current_course = new Course(id, name, docId, DrName, code);
			current_course->Registered_Students = RegisteredSt;
			CourseData[code] = current_course;
			if (id >= Courses_Count) Courses_Count = id + 1;
		}
		else if (type == "ASG") {
			if (current_course != nullptr) {
				int id = stoi(parts[1]);
				std::string content = parts[2];
				double maxGrade = stod(parts[3]);
				int days = stoi(parts[4]);
				int month = stoi(parts[5]);
				int year = stoi(parts[6]);
				int hour = stoi(parts[7]);
				int minute = stoi(parts[8]);
				DateTime deadline(days, month, year, hour, minute);

				current_course->Add_Assignment(content, maxGrade, deadline, id);

				current_assignment = current_course->Get_Assignments().back();

			}
		}
		else if (type == "SOL") {
			if (current_assignment != nullptr) {

				int studId = stoi(parts[1]);
				std::string answer = parts[2];
				double grade = stod(parts[3]);
				std::string comment = parts[4];

				Solution* newsol = new Solution(studId, answer);
				newsol->Set_Grade(grade);
				newsol->Set_commnet(comment);
				current_assignment->Add_Solution(newsol);



			}
		}

	}

	fin.close();
}

void CoursesManager::SaveCourseData() {
	std::ofstream fout("CourseData.txt");
	if (fout.fail()) {
		return;
	}
	for (auto& pair : CourseData) {
		fout << "CRS|";
		fout << pair.second->Get_Course_ID() << "|";
		fout << pair.second->Get_CourseName() << "|";
		fout << pair.second->Get_Doc_ID() << "|";
		fout << pair.first << "|";
		fout << pair.second->Get_Dr_Name() << "|";
		fout << pair.second->Registered_Students << "\n";
		std::vector<Assignment*> temp = pair.second->Get_Assignments();
		for (auto& assignment : temp) {
			fout << "ASG|";
			fout << assignment->Get_Assignment_ID() << "|";
			fout << assignment->Get_Assignment_content() << "|";
			fout << assignment->Get_Max_Grade() << "|";
			fout << assignment->Get_Deadline().day << "|";
			fout << assignment->Get_Deadline().month << "|";
			fout << assignment->Get_Deadline().year << "|";
			fout << assignment->Get_Deadline().hour << "|";
			fout << assignment->Get_Deadline().minute << "\n";
			std::vector<Solution*> tempsol = assignment->Get_solutions();
			for (auto& sol : tempsol) {
				fout << "SOL|";
				fout << sol->Get_Student_ID() << "|";
				fout << sol->Get_Answer() << "|";
				fout << sol->Get_Grade() << "|";
				fout << sol->Get_Comment() << "\n";
			}

		}
	}
	fout.close();
}

std::vector<std::string>CoursesManager::Get_Courses(std::vector<std::string> codes) {
	std::vector<std::string> user_courses;

	for (int i = 0; i < codes.size(); i++) {
		if (CourseData.count(codes[i])) {
			user_courses.push_back(CourseData[codes[i]]->Get_CourseName());
		}
	}

	return user_courses;
}



void CoursesManager::Add_Assignment(std::string content, std::string course_code, double max_grade, int allowedtime) {

	int id = CourseData[course_code]->Get_Course_ID();
	CourseData[course_code]->Add_Assignment(content, max_grade, allowedtime);

}

Course* CoursesManager::Get_Course(std::string code)const {
	auto it = CourseData.find(code);
	if (it == CourseData.end()) {
		throw std::runtime_error("Course is not found");
	}
	return it->second;

}

const std::map<std::string, Course*>& CoursesManager::Get_Course_Map() {

	return CourseData;
}

std::string CoursesManager::Get_Assignment_Content(std::string code, int id) {

	Course* course = CourseData[code];
	for (const auto& assignment : course->Get_Assignments()) {
		if (id == assignment->Get_Assignment_ID()) {
			return assignment->Get_Assignment_content();
		}
	}
	throw std::invalid_argument("Invalid Input");
	return "";


}
bool CoursesManager::Allow_Submition(int userID, std::string code, int id) {
	Course* course = CourseData[code];
	for (const auto& assignment : course->Get_Assignments()) {
		if (id == assignment->Get_Assignment_ID()) {
			for (const auto& sol : assignment->Get_solutions()) {
				if (sol->Get_Student_ID() == userID) {
					throw std::runtime_error("Already Submitted");
				}
			}

			if (DateTime::getCurrentDateTime().isBefore(assignment->Get_Deadline())) {
				return true;

			}



		}
	}
	return false;

}



void CoursesManager::Submit_Solution(int studID, std::string ans, std::string code, int id) {
	Course* course = CourseData[code];
	for (const auto& assignment : course->Get_Assignments()) {
		if (id == assignment->Get_Assignment_ID()) {
			Solution* sol = new Solution(studID, ans);
			assignment->Add_Solution(sol);


		}
	}

}





bool CoursesManager::SolExist(std::string code, int AssignmentID, int studentID) {
	std::vector<Assignment*> assigns = CourseData[code]->Get_Assignments();
	bool found = false;
	for (const auto& assign : assigns) {
		if (assign->Get_Assignment_ID() == AssignmentID) {
			found = true;
			std::vector<Solution*> sols = assign->Get_solutions();
			for (const auto& sol : sols) {
				if (sol->Get_Student_ID() == studentID) {
					return true;
				}
			}
		}
	}
	if (!found) {
		throw std::runtime_error("Assignment is not found");
	}
	return false;

}





bool CoursesManager::Solution_Graded(std::string code, int AssignmentID, int studentID) {
	if (!this->IsCourseExist(code)) {
		throw std::runtime_error("Can/'t find this course");
	}
	std::vector<Assignment*> Assign = CourseData[code]->Get_Assignments();
	for (const auto& A : Assign) {
		if (A->Get_Assignment_ID() == AssignmentID) {
			if (A->ISGradedSol(studentID)) {
				return true;
			}
			else {
				return false;
			}
		}

	}
	throw std::logic_error("Solution is not found");
}


bool CoursesManager::Has_Solutions(std::string code, int AssignID) {
	std::vector<Assignment*> assigns = CourseData[code]->Get_Assignments();
	for (const auto& assign : assigns) {
		if (assign->Get_Assignment_ID() == AssignID) {
			if (assign->Get_solutions().empty()) {
				return false;
			}
			else {
				return true;
			}
		}
	}
	throw std::runtime_error("Assignment is not found");
	return false;
}


void CoursesManager::Handle_Unregister(std::string code, int studentID) {
	if (!CourseData.count(code)) {
		throw std::runtime_error("Course Is Not Found");
	}
	CourseData[code]->Handle_Stud_Unregister(studentID);

}




void CoursesManager::Reset_All_Counts() {
	for (auto& pair : CourseData) {
		pair.second->Registered_Students = 0;
	}
}

void CoursesManager::Plus_St_Count(std::string code) {
	if (CourseData.count(code)) {
		CourseData[code]->Registered_Students++;
	}
}


CoursesManager::~CoursesManager() {
	for (auto& pair : CourseData) {
		delete pair.second;
	}
	CourseData.clear();
}