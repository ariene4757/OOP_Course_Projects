#include "Course.h"


//int Course::Assignment_counter = 1;



Course::Course(int id, std::string Name, int doc_id, std::string DrName, std::string code) :Course_ID(id), Course_Name(Name), doctor_id(doc_id), DrName(DrName), code(code) {

}

Course::~Course() {
	for (auto assignment : Course_Assignment) {
		delete assignment;
	}
	Course_Assignment.clear();
}

int Course::Get_Course_ID()const {
	return Course_ID;
}

int Course::Get_Doc_ID()const {
	return doctor_id;
}

std::vector<Assignment*>& Course::Get_Assignments() {
	return Course_Assignment;
}



void Course::Add_Assignment(std::string content, double max_grade, int allowedtime) {
	Assignment* newAssignment = nullptr;

	newAssignment = new Assignment(Assignment_counter, content, max_grade, allowedtime);
	Assignment_counter++;

	this->Course_Assignment.push_back(newAssignment);




}

void Course::Add_Assignment(std::string content, double max_grade, DateTime deadline, int id) {
	Assignment* newAssignment = new Assignment(id, content, max_grade, deadline);
	if (Assignment_counter <= id) {
		Assignment_counter = id + 1;

	}


	this->Course_Assignment.push_back(newAssignment);


}



std::string Course::Get_Code()const {
	return code;
}

std::string Course::Get_CourseName()const {
	return Course_Name;
}
int Course::Get_Active_Assignments()const {
	int cnt = 0;
	DateTime now = DateTime::getCurrentDateTime();
	for (auto* assign : Course_Assignment) {
		if (now.isBefore(assign->Get_Deadline())) {
			cnt++;
		}

	}
	return cnt;

}
std::string Course::Get_Dr_Name()const {

	return DrName;
}

void Course::Handle_Stud_Unregister(int studentID) {
	Registered_Students--;
	for (auto& assign : this->Course_Assignment) {
		assign->Remove_Solution(studentID);
	}
}



