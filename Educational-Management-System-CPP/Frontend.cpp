#include "Frontend.h"
#include<iostream>
#include<vector>
#include<iostream>
#include"User.h"
#include"Doctor.h"
#include<stdexcept>
#include"Student.h"
using namespace std;




int Frontend::ExecuteAction(int choice, User* current_user) {
	Student* studentPtr = dynamic_cast<Student*>(current_user);
	if (studentPtr) {
		return this->StudFlow(choice, current_user);

	}
	if (Doctor* docPtr = dynamic_cast<Doctor*>(current_user)) {
		return this->DocFlow(choice, current_user);
	}
	return 100;
}

int Frontend::MainMenu() {

	cout << "Enter Your Choice\n\
             \t1 - Login\n\
             \t2 - Sign up\n\
             \t3 - Exit\n\
             \tEnter your choice: ";
	int choice;
	cin >> choice;
	while (cin.fail() || !valid_input(1, 3, choice)) {
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Invalid Input. try Again\n";
		cout << "Enter your choice: ";
		cin >> choice;
	}
	cin.ignore(10000, '\n');
	if (choice == 1) {
		string username, password;
		while (true) {
			try {
				cout << "Enter user name: ";
				getline(cin, username);
				cout << "Enter password: ";
				getline(cin, password);
				sys.Login(username, password);
				cout << "Welcome " << sys.current_user->Get_Name() << " ,You are logged in\n";
				break;
			}
			catch (const exception& e) {
				cout << "Error: " << e.what() << "\nTry again.\n";
				cin.clear();

			}


		}







	}
	else if (choice == 2) {
		int type;
		std::string secret_code;
		while (true) {
			try {
				double gpa;
				std::string name, username, email, password;
				cout << "Enter your name: ";
				getline(cin, name);
				cout << "Enter user name: ";
				getline(cin, username);
				cout << "Enter email: ";
				getline(cin, email);
				cout << "Enter your password: ";
				getline(cin, password);


				cout << "Are you (1) Student or (2) Doctor?: ";
				cin >> type;
				if (type == 1) {

					cout << "Enter your GPA: ";
					cin >> gpa;
					sys.SignUp(name, username, email, password, 1, "", gpa);
				}
				else if (type == 2) {
					cout << "Enter Doctor Secret Code : ";
					cin >> secret_code;
					sys.SignUp(name, username, email, password, 2, secret_code);
				}
				else {
					throw std::invalid_argument("Invalid input");
				}
				cin.ignore(10000, '\n');
				cout << "Signed up successfully!\n";
				break;



			}
			catch (const exception& e) {
				cout << "Error: " << e.what() << "\nTry again.\n";
				cin.clear();
				cin.ignore(10000, '\n');
			}


		}

	}
	else {
		cout << "Existing program....\n";
		return -1;
	}
	return 100;
}

int Frontend::ViewUserDashboard() {


	while (true) {
		try {
			cout << "\n===============DashBoard================\n";
			std::vector<std::string> dash = sys.Get_Dash_Menu();
			for (int i = 0; i < dash.size(); i++) {
				cout << i + 1 << " - " << dash[i] << endl;
			}
			cout << "Enter your choice: ";
			int choice;
			cin >> choice;

			int status = this->ExecuteAction(choice, sys.current_user);
			if (status == -1) {
				return -1;
			}
			break;
		}
		catch (const exception& e) {
			cout << "Error: " << e.what() << "\nTry again.\n";
			cin.clear();
			cin.ignore(10000, '\n');
		}

	}
	return 100;

}

int Frontend::ExecuteDash(int choice, User* current_user, std::string code) {
	Student* studentPtr = dynamic_cast<Student*>(current_user);
	if (studentPtr) {
		return this->DashStudFlow(choice, current_user, code);

	}
	if (Doctor* docPtr = dynamic_cast<Doctor*>(current_user)) {
		return this->DashDocFlow(choice, current_user, code);
	}

	return 100;
}

void Frontend::Create_Course() {
	while (true) {
		try {
			string coursename, coursecode;
			cout << "Enter course name: ";
			getline(cin >> ws, coursename);
			cout << "Enter course code: ";
			getline(cin >> ws, coursecode);
			sys.Create_Course(coursename, coursecode);
			cout << "Course added sucessfully\n";
			break;

		}
		catch (const exception& e) {
			cout << "Error: " << e.what() << "\nTry again.\n";
			cin.clear();


		}


	}

}

void Frontend::Register_In_Course() {
	cin.ignore(10000, '\n');
	while (true) {
		try {

			std::string coursecode;
			cout << "Enter course code: ";
			getline(cin, coursecode);
			sys.Register_In_Course(coursecode);
			cout << "Registered successfully\n";
			break;
		}
		catch (const exception& e) {
			cout << "Error: " << e.what() << "\nTry again.\n";

		}
	}
}

void Frontend::List_Courses() {
	vector<pair<string, string>> courses = sys.User_Courses();
	if (courses.empty()) {
		cout << "You don\'t have any courses yet\n";
		return;
	}
	cout << "My Courses List\n";
	for (int i = 0; i < courses.size(); i++) {
		cout << i + 1 << ") Course " << courses[i].first << " - " << courses[i].second << "\n";
	}
}

void Frontend::View_Course() {

	while (true) {
		try {
			List_Courses();
			vector<pair<string, string>> courses = sys.User_Courses();
			if (courses.empty()) {
				return;
			}
			cout << "Which ith [" << 1 << " - " << courses.size() << "] course to view? ";
			int choice;
			cin >> choice;
			while (cin.fail() || !valid_input(1, (int)courses.size(), choice)) {
				cin.clear();
				cin.ignore(10000, '\n');
				cout << "Invalid Input. try Again\n";
				cout << "Enter your choice: ";
				cin >> choice;

			}
			vector<string> Details = sys.CourseDetails(courses[choice - 1].second);

			for (int i = 0; i < Details.size(); i++) {
				cout << Details[i];

			}

			cout << "Please make a choice: \n";
			vector<std::string>Dash = sys.Details_Dash();
			for (int i = 0; i < Dash.size(); i++) {
				cout << i + 1 << " - " << Dash[i] << endl;
			}
			int subchoice;
			cout << "Enter your choice: ";
			cin >> subchoice;
			while (cin.fail() || !valid_input(1, (int)Dash.size(), subchoice)) {
				cin.clear();
				cin.ignore(10000, '\n');
				cout << "Invalid Input. try Again\n";
				cout << "Enter your choice: ";
				cin >> subchoice;

			}


			this->ExecuteDash(subchoice, sys.current_user, courses[choice - 1].second);
			break;
		}

		catch (const exception& e) {
			cout << "Error: " << e.what() << "\nTry again.\n";

		}
	}

}

void Frontend::Add_Assignment(std::string code) {
	std::string targetCode = code;
	while (true) {
		try {
			if (targetCode == "") {
				cout << "Enter course code: ";
				getline(cin >> ws, targetCode);
			}
			if (!sys.CourseExist(targetCode)) {
				throw std::invalid_argument("Course is not exist");

			}
			cout << "Adding New Assignment to Course " << targetCode << endl;

			std::string content;
			int max_grade{};
			int allowedtime;
			cout << "Enter Assignment Content (Question): ";
			getline(cin >> ws, content);
			cout << "Enter Max Grade: ";
			cin >> max_grade;
			while (cin.fail()) {
				cin.clear();
				cin.ignore(10000, '\n');
				cout << "Invalid input. Enter Max Grade again: ";
				cin >> max_grade;
			}
			cin.ignore(10000, '\n');
			cout << "Enter Deadline Duration (in days): ";
			cin >> allowedtime;
			while (cin.fail()) {
				cin.clear();
				cin.ignore(10000, '\n');
				cout << "Invalid input. Enter Duration again: ";
				cin >> allowedtime;
			}
			cin.ignore(10000, '\n');


			sys.Add_Assignment(targetCode, content, max_grade, allowedtime);
			cout << "Assignment Added Successfully\n";
			break;
		}
		catch (const exception& e) {
			cout << "Error: " << e.what() << "\nTry again.\n";

		}
	}
}

void Frontend::Submit_Solution(std::string code, int id) {

	try {
		std::string content = sys.Get_Assignment_Content(code, id);
		cout << "ASM Content: " << content << endl;
		bool stat = sys.Valid_Sol_Submition(code, id);
		if (!stat) {
			cout << "You can'\t submit solution for this assignment after deadline\n";
			return;
		}
		std::string sol;
		cout << "Enter your answer: ";
		getline(cin >> ws, sol);
		sys.Answer_Assignment(sol, code, id);
		cout << "Solution has been submitted\n";
	}
	catch (const exception& e) {
		cout << "Error: " << e.what() << ".\n";

	}
}

void Frontend::View_Solution(std::string code, int AssignmentID, int studentID) {
	std::vector<Solution*> sols = sys.Get_Solutions(code, AssignmentID);
	for (const auto& sol : sols) {
		if (sol->Get_Student_ID() == studentID) {
			cout << "Student ID: " << sol->Get_Student_ID() << "\n";
			cout << "Answer: " << sol->Get_Answer() << "\n";
			return;
		}
	}
}

pair<std::string, int >  Frontend::View_Solutions(std::string code, int id) {
	std::string coursecode = code;

	try {
		if (coursecode == "") {
			cout << "Enter Course code: ";
			getline(cin >> ws, coursecode);
			code = coursecode;
			std::vector<std::string> assignments = sys.CourseDetails(coursecode);
			for (int i = 0; i < assignments.size(); i++) {
				cout << assignments[i];
			}
			cout << "Enter assignment ID to View Solutions: ";
			cin >> id;
		}
		std::string assignment_content = sys.Get_Assignment_Content(coursecode, id);
		cout << "Assignment content: " << assignment_content << endl;
		cout << "Students Solutions: \n";

		std::vector<Solution*> solutions = sys.Get_Solutions(coursecode, id);
		cout << "\n";
		cout << "No. | Student ID | Status      | Grade  | Answer Preview\n";
		cout << "--------------------------------------------------------\n";
		for (int i = 0; i < solutions.size(); i++) {
			string status = "Pending";
			string gradeStr = "--";

			if (solutions[i]->Get_Grade() != -1) {
				status = "Graded ";
				gradeStr = to_string((int)solutions[i]->Get_Grade());
			}


			cout << (i + 1) << "   | "
				<< solutions[i]->Get_Student_ID() << "          | "
				<< status << "     | "
				<< gradeStr << "/" << sys.Get_AssigMax_Grade(coursecode, id) << "    | "
				<< solutions[i]->Get_Answer().substr(0, 15) << "..."
				<< endl;
		}


	}
	catch (const exception& e) {
		cout << "Error: " << e.what() << ".\n";

	}


	return { code, id };


}

void Frontend::List_Students(std::string code) {
	try {
		Course* course = sys.Get_Course(code);
		cout << "\n--- Students Registered in " << course->Get_CourseName() << " (" << code << ") ---\n";
		std::vector<Student*> res = sys.Get_All_Students();

		int cnt = 1;
		bool foundAny = false;
		for (int i = 0; i < res.size(); i++) {
			if (res[i]->IsRegistered_In_Course(code)) {
				cout << cnt++ << ") " << res[i]->Get_Name() << " (ID: " << res[i]->Get_UserID() << ")\n";
				foundAny = true;
			}
		}

		if (!foundAny) {
			cout << "No students found for this course.\n";
		}
	}
	catch (const exception& e) {
		cout << "Error: " << e.what() << ".\n";

	}











}

void Frontend::Grade_Solution(std::string code, int id) {
	pair<std::string, int > pair = this->View_Solutions(code, id);
	code = pair.first;
	id = pair.second;
	bool forceUpdate = false;
	int studentID;
	while (true) {
		try {
			if (!sys.Has_Solutions(code, id)) {

				return;

			}

			if (!forceUpdate) {
				cout << "Enter Student ID to grade his solution: ";
				cin >> studentID;
			}
			if (!sys.DoesSolutionExist(code, id, studentID)) {
				throw runtime_error("This student hasn't submitted a solution yet.");
			}

			if (sys.IsSolutionDraded(code, id, studentID) && !forceUpdate) {
				throw std::logic_error("Already graded");
			}

			this->View_Solution(code, id, studentID);
			cout << "Enter Grade: ";
			double grade; cin >> grade;

			cout << "Enter Comment: ";
			string comment; getline(cin >> ws, comment);
			sys.Grade_Solution(grade, id, code, studentID, comment);
			cout << "Successfully Graded! \n";
			break;




		}
		catch (const std::logic_error& e) {
			if (string(e.what()) == "Already graded") {
				forceUpdate = Handle_Overwrite_Choice();
				if (!forceUpdate)
					return;

			}
			else {
				cout << "Error: " << e.what() << ".\n";
				forceUpdate = true;

			}
		}

		catch (const exception& e) {
			cout << "Error: " << e.what() << ".\n";

		}


	}

}

bool Frontend::Handle_Overwrite_Choice() {
	string stat;
	cin.clear();
	while (true) {

		cout << "This solution is already graded. Overwrite? (Yes/No): ";
		if (!(getline(cin >> ws, stat))) continue;
		stat = trim(stat);
		stat = convert_to_low(stat);

		if (stat == "yes") return true;
		if (stat == "no") return false;

		cout << "Error: Please enter 'yes' or 'no'." << endl;

	}

}

int Frontend::DashDocFlow(int choice, User* current_user, std::string code) {
	try {

		if (choice == 1) {
			this->Add_Assignment(code);

		}
		else if (choice == 2) {
			int id;
			cout << "Enter Assignment ID: ";
			cin >> id;
			sys.valid_Assignment_ID(code, id);

			this->Grade_Solution(code, id);
		}
		else if (choice == 3) {
			this->List_Students(code);
		}
		else if (choice == 4) {
			return -1;
		}
		else {
			throw std::invalid_argument("Invalid choice");
		}

	}
	catch (const exception& e) {
		cout << "Error: " << e.what() << ".\n";

	}
	return 100;

}

int Frontend::DocFlow(int choice, User* current_user) {
	if (choice == 1) {
		this->View_Course();
	}

	else if (choice == 2) {
		this->Create_Course();
	}
	else if (choice == 3) {
		this->Add_Assignment();
	}
	else if (choice == 4) {
		this->View_Solutions();
	}
	else if (choice == 5) {
		this->Grade_Solution();
	}
	else if (choice == 6) {
		return -1;
	}
	else {
		throw std::invalid_argument("Invalid choice");
	}
	return 100;
}

int Frontend::StudFlow(int choice, User* current_user) {
	if (choice == 1) {
		this->Register_In_Course();
	}
	else if (choice == 2) {
		this->List_Courses();

	}
	else if (choice == 3) {
		this->View_Course();
	}
	else if (choice == 4) {
		this->View_Grades_Report();
	}
	else if (choice == 5) {
		return -1;
	}
	else {
		throw std::invalid_argument("Invalid choice");
	}


	return 100;
}


void Frontend::View_Grades_Report() {
	try {
		auto report = sys.Get_User_Report();

		cout << "\n========= STUDENT GRADE REPORT =========\n";
		cout << "Student: " << report.first.second.first << " (ID: " << report.first.first << ")\n";
		cout << "Student GPA: " << report.first.second.second << endl;

		for (const auto& code : report.second) {
			Course* current_course = sys.Get_Course(code);

			if (current_course == nullptr) {
				continue;
			}

			cout << "\n------------------------------------------------------\n";
			cout << " Course: " << current_course->Get_CourseName() << " (" << code << ")\n";
			cout << "------------------------------------------------------\n";

			vector<Assignment*> assignments = current_course->Get_Assignments();

			if (assignments.empty()) {
				cout << "  -> No assignments in this course.\n";
				continue;
			}

			double totalStudentGrade = 0;
			double totalMaxGrade = 0;

			cout << " ID  |      Status      |    Grade     |      Comment      \n";
			cout << "-----|------------------|--------------|--------------\n";

			for (Assignment* asg : assignments) {
				bool isSubmitted = false;
				bool isGraded = false;
				double myGrade = 0;
				string comment;
				totalMaxGrade += asg->Get_Max_Grade();

				for (Solution* sol : asg->Get_solutions()) {
					if (sol->Get_Student_ID() == sys.current_user->Get_UserID()) {
						isSubmitted = true;

						if (sol->Get_Grade() != -1) {
							isGraded = true;
							myGrade = sol->Get_Grade();
							comment = sol->Get_Comment();

						}
						else {
							comment = "Waiting....";
						}
						
						break;
					}
				}


				cout << "  " << asg->Get_Assignment_ID();
				if (asg->Get_Assignment_ID() < 10) cout << "  | ";
				else cout << " | ";


				if (!isSubmitted) {

					cout << "Not Submitted    |   NA / " << asg->Get_Max_Grade();
					if (asg->Get_Max_Grade() < 10) cout << " ";
					cout << "    |      --           ";
				}
				else if (!isGraded) {
					cout << "Pending Grade    |   NA / " << asg->Get_Max_Grade();
					if (asg->Get_Max_Grade() < 10) cout << " ";
					cout << "    |   " << comment;
				}
				else {
					cout << " Graded          |   ";
					if (myGrade < 10) cout << " ";
					cout << myGrade << " / " << asg->Get_Max_Grade();
					if (asg->Get_Max_Grade() < 10) cout << " ";
					totalStudentGrade += myGrade;
					cout << "    |   " << comment;
				}

				cout << "\n";
			}

			cout << "------------------------------------------------------\n";
			cout << "  Total Course Grade: " << totalStudentGrade << " / " << totalMaxGrade << "\n";
		}

		cout << "\n=====================================================\n";

	}
	catch (const std::exception& e) {
		cout << "Error: " << e.what() << ".\n";
	}
}



void Frontend::UnRegister_From_Course(std::string code) {

	try {
		cout << "Are you sure you want to unregister from this course (Yes/No): ";
		string stat;
		getline(cin >> ws, stat);
		stat = trim(stat);
		stat = convert_to_low(stat);
		if (stat == "no") {
			return;
		}
		sys.Unregister_From_Course(code);



		cout << "UNREGISTRATION SUCCESSFULLY\n";

	}
	catch (const std::exception& e) {
		cout << "Error: " << e.what() << ".\n";
	}
}





int Frontend::DashStudFlow(int choice, User* current_user, std::string code) {
	if (choice == 1) {
		this->UnRegister_From_Course(code);
	}
	else if (choice == 2) {
		int id;
		cout << "Enter Assignment ID: ";
		cin >> id;
		sys.valid_Assignment_ID(code, id);
		this->Submit_Solution(code, id);
	}
	else if (choice == 3) {
		return -1;
	}
	else {
		throw std::invalid_argument("Invalid choice");
	}
	return 100;

}

