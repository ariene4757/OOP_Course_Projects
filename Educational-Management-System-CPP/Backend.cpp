#include "Backend.h"
#include "UserManager.h"
#include"CoursesManager.h"
#include"Doctor.h"
#include<stdexcept>






void Backend::SignUp(std::string name, std::string username, std::string email, std::string password, int type, std::string Doc_Code, double gpa) {


	if (user_manager.IsUserExist(username)) {
		throw std::runtime_error("Username already exists!");
	}


	if (type == 1) {
		current_user = user_manager.Add_User(type, name, username, email, password, gpa);
	}
	else if (type == 2) {
		if (Doc_Code == "DOC_2026_PASS") {
			current_user = user_manager.Add_User(type, name, username, email, password);
		}
		else {
			throw std::invalid_argument("Invalid Doctor Secret Code! Access Denied.");
		}

	}
	else {
		throw std::invalid_argument("Invalid user type!");
	}
	user_manager.Save_Users_Data();

}

void Backend::Login(std::string username, std::string password) {
	if (!user_manager.IsUserExist(username)) {
		throw std::runtime_error("User name is not exist!");
	}
	current_user = user_manager.ValidUser(username, password);



}

std::vector<std::string>Backend::Get_Dash_Menu()const {
	return user_manager.Get_DashBoard(current_user);
}

void Backend::Create_Course(std::string CourseName, std::string CourseCode) {

	if (course_manager.IsCourseExist(CourseCode)) {
		throw std::runtime_error("Course Code already exists!");
	}
	int id = current_user->Get_UserID();
	course_manager.Add_Course(CourseName, id, current_user->Get_Name(), CourseCode);
	user_manager.Add_Course_In_DR_List(current_user, CourseCode);
	Save_Database();

}

void Backend::Load_Database() {
	course_manager.LoadCourseData();
	user_manager.Load_Users_Data();
	user_manager.Load_Student_Courses();



	course_manager.Reset_All_Counts();
	auto users = user_manager.Get_All_Students();

	for (auto const& userPtr : users) {
		Student* student = dynamic_cast<Student*>(userPtr);
		if (student != nullptr) {
			for (std::string code : student->Get_Registered_Courses()) {
				course_manager.Plus_St_Count(code);
			}
		}
	}
}

void Backend::Save_Database() {
	user_manager.Save_Users_Data();
	course_manager.SaveCourseData();
	user_manager.Save_Student_Courses();

}

Backend::Backend() {
	Load_Database();

	const std::map<std::string, Course*>& all_courses = course_manager.Get_Course_Map();
	for (const auto& pair : all_courses) {
		Course* c = pair.second;
		int id = c->Get_Doc_ID();
		User* user = user_manager.Get_User_byID(id);

		Doctor* doc = dynamic_cast<Doctor*>(user);
		if (doc != nullptr) {
			doc->Add_Course_Code(pair.first);
		}

	}



}

Backend::~Backend() {
	Save_Database();
}

void Backend::Register_In_Course(std::string code) {
	if (!course_manager.IsCourseExist(code)) {
		throw std::invalid_argument("Course is not found");
	}
	bool status = user_manager.Register_In_Course(code, current_user);
	if (!status) {
		throw std::runtime_error("You are already registered in this course!");
	}
	course_manager.Plus_St_Count(code);
	this->Save_Database();
}

std::vector<std::pair<std::string, std::string>> Backend::User_Courses() {
	std::vector<std::string> codes = user_manager.Get_User_CourseCodes(current_user);
	std::vector<std::string> courses = course_manager.Get_Courses(codes);
	std::vector<std::pair<std::string, std::string>> res;
	for (int i = 0; i < codes.size(); i++) {
		res.push_back({ courses[i], codes[i] });
	}
	return res;
}

std::vector<std::string>Backend::Details_Dash() {
	std::vector<std::string> Dash = user_manager.Get_Course_Details_DashBoard(current_user);
	return Dash;
}

std::vector<std::string >Backend::CourseDetails(std::string code) {
	std::vector<std::string> Details;
	Course* course = course_manager.Get_Course(code);
	Details = user_manager.Get_Course_Details(course, current_user);
	return Details;

}

bool Backend::CourseExist(std::string code) {
	if (!course_manager.IsCourseExist(code)) {
		return false;
	}
	return true;
}

void Backend::Add_Assignment(std::string code, std::string content, double max_grade, int alloweddays) {

	if (course_manager.Get_Course(code)->Get_Doc_ID() != current_user->Get_UserID()) {
		throw std::runtime_error("You can\'t add assignment to this course");
	}
	if (max_grade < 0) {
		throw std::invalid_argument("Max grade can\'t  be negative");
	}
	if (alloweddays <= 0) {
		throw std::invalid_argument("Deadline can\'t  be negative");
	}

	course_manager.Add_Assignment(content, code, max_grade, alloweddays);
	Save_Database();
}

std::string Backend::Get_Assignment_Content(std::string code, int id) {
	std::string content = course_manager.Get_Assignment_Content(code, id);
	return content;


}

bool Backend::Valid_Sol_Submition(std::string code, int id) {
	return course_manager.Allow_Submition(current_user->Get_UserID(), code, id);
}

void Backend::Answer_Assignment(std::string sol, std::string code, int id) {
	course_manager.Submit_Solution(current_user->Get_UserID(), sol, code, id);
	Save_Database();
}

void Backend::valid_Assignment_ID(std::string code, int  id) {
	const auto& assignments = course_manager.Get_Course(code)->Get_Assignments();
	bool found = false;
	if (!assignments.empty()) {

		for (const auto& assign : assignments) {
			if (assign->Get_Assignment_ID() == id) {
				found = true;
			}
		}
	}
	else {
		throw std::runtime_error("Course has no assignments");
	}

	if (!found) {
		throw std::runtime_error("Invalid Assignment ID for current Course");
	}
}

std::vector<Solution*> Backend::Get_Solutions(std::string code, int id) {
	const std::vector<Assignment* >& Assignments = course_manager.Get_Course(code)->Get_Assignments();
	std::vector<Solution*> Sols;
	for (const auto& Assign : Assignments) {
		if (Assign->Get_Assignment_ID() == id) {
			Sols = Assign->Get_solutions();
			break;
		}
	}
	if (Sols.empty()) {
		throw std::runtime_error("Assignment has no solutions yet");
	}
	return Sols;

}

int Backend::Get_AssigMax_Grade(std::string code, int id) {
	std::vector<Assignment*> Assign = course_manager.Get_Course(code)->Get_Assignments();
	int max_grade{};
	for (const auto& assign : Assign) {
		if (id == assign->Get_Assignment_ID()) {
			max_grade = assign->Get_Max_Grade();
		}
	}
	return max_grade;
}

Course* Backend::Get_Course(std::string code)const {
	Course* course = course_manager.Get_Course(code);
	Student* stud = dynamic_cast<Student*>(current_user);
	if (stud == nullptr) {
		if (course->Get_Doc_ID() != current_user->Get_UserID()) {
			throw std::runtime_error("You are not allowed to view this course details");
		}

	}

	return course;
}

std::vector<Student*> Backend::Get_All_Students() {
	std::vector<Student*> res = user_manager.Get_All_Students();
	return res;
}

void Backend::Grade_Solution(double Grade, int assignmentId, std::string coursecode, int studID, std::string comment) {
	Course* course = course_manager.Get_Course(coursecode);

	if (course->Get_Doc_ID() != current_user->Get_UserID()) {
		throw std::runtime_error("You are not allowed to Grade this course Solutions");
	}
	bool assignfound = false;
	bool solfound = false;
	const std::vector<Assignment*>& assigns = course->Get_Assignments();
	for (const auto& assign : assigns) {
		if (assign->Get_Assignment_ID() == assignmentId) {
			assignfound = true;
			const std::vector<Solution*>& sols = assign->Get_solutions();
			for (const auto& sol : sols) {
				if (sol->Get_Student_ID() == studID) {
					solfound = true;
					if (Grade > assign->Get_Max_Grade() || Grade < 0) {
						throw std::logic_error("Invalid Grade");
					}
					sol->Set_Grade(Grade);
					sol->Set_commnet(comment);
					

					break;
				}
			}
			break;
		}
	}
	if (!assignfound) {
		throw std::runtime_error("Assignment is not Found");
	}
	if (!solfound) {
		throw std::runtime_error("This student hasn't submit solution yet");
	}
	Save_Database();
}

bool Backend::IsSolutionDraded(std::string code, int assignmentID, int studentID) {
	return course_manager.Solution_Graded(code, assignmentID, studentID);

}

bool Backend::DoesSolutionExist(std::string code, int id, int studentID) {
	if (!this->CourseExist(code)) {
		throw std::runtime_error("Course is not exist");
	}
	return course_manager.SolExist(code, id, studentID);

}

bool Backend::Has_Solutions(std::string code, int id) {
	if (!this->CourseExist(code)) {
		throw std::logic_error("Course is not found");

	}
	return course_manager.Has_Solutions(code, id);

}

std::pair < std::pair<int, std::pair<std::string, double>>, std::vector<std::string>> Backend::Get_User_Report() {
	std::pair<int, std::pair<std::string, double>> userdata = user_manager.Get_User_Data(current_user);
	std::vector<std::string> courses = user_manager.Get_User_CourseCodes(current_user);
	std::pair < std::pair<int, std::pair<std::string, double>>, std::vector<std::string>> res;
	res.first = userdata;
	res.second = courses;
	return res;

}

void Backend::Unregister_From_Course(std::string code) {
	Student* stud = dynamic_cast<Student*>(current_user);
	if (stud == nullptr) {
		throw std::runtime_error("User is not found");
	}
	user_manager.Handle_User_Unregisteration(code, stud);

	course_manager.Handle_Unregister(code, stud->Get_UserID());
	this->Save_Database();

}
