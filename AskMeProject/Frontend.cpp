#include "Frontend.h"
#include <string>
#include <iostream>
using namespace std;

int Frontend::ShowMainMenuAndLogin() {
	cout << "\nMenu:\n"
		"\t1) Login\n"
		"\t2) Sign Up\n"
		"\t3) Exit\n"
		"Enter number in range 1 - 3: ";

	int choice;
	cin >> choice;

	while (!IsValidInput(choice, 1, 3) || cin.fail()) {
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Invalid Input..Try again.\nEnter number in range 1 - 3: ";
		cin >> choice;
	}
	cin.ignore(10000, '\n');

	if (choice == 1) {
		string username, password;
		cout << "Enter username: ";
		getline(cin, username);
		cout << "Enter password: ";
		getline(cin, password);

		return system->Login(username, password);
	}
	else if (choice == 2) {
		string username, password, email, name;
		bool allowanonymous;

		cout << "Enter username: ";
		getline(cin, username);

		cout << "Enter password: ";
		getline(cin, password);

		cout << "Enter name: ";
		getline(cin, name);

		cout << "Enter email: ";
		cin >> email;

		int tempAnon;
		cout << "Allow anonymous questions? (1: Yes / 0: No): ";
		cin >> tempAnon;

		while (!IsValidInput(tempAnon, 0, 1) || cin.fail()) {
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "Invalid input... Please try again.\n";
			cout << "Allow anonymous questions? (1: Yes / 0: No): ";
			cin >> tempAnon;
		}
		cin.ignore(10000, '\n');
		allowanonymous = (tempAnon == 1);

		return system->SignUp(username, password, email, name, allowanonymous);
	}
	else {
		return -100;
	}
}

int Frontend::ShowUserMenu() {
	cout << "\nMenu:\n"
		"\t1) Print Question To Me\n"
		"\t2) Print Question From Me\n"
		"\t3) Answer Question\n"
		"\t4) Delete Question\n"
		"\t5) Ask Question\n"
		"\t6) List System Users\n"
		"\t7) Feed\n"
		"\t8) Logout\n"
		"Enter number in range 1-8: ";

	int menuchoice;
	cin >> menuchoice;

	while (!IsValidInput(menuchoice, 1, 8) || cin.fail()) {
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Invalid Input....Try Again.\n";
		cout << "Enter number in range 1-8: ";
		cin >> menuchoice;
	}
	return menuchoice;
}

void Frontend::AskQuestion() {
	cout << "Enter User ID or -1 to cancel: ";
	int reciever_id;
	cin >> reciever_id;
	while (cin.fail() || !(reciever_id == -1 || system->Is_User_Found(reciever_id))) {
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "can\'t find this user....Try Again.\n";
		cout << "Enter User ID or -1 to cancel: ";
		cin >> reciever_id;
	}
	cin.ignore(10000, '\n');

	if (reciever_id == -1) {
		cout << "Question has been cancelled\n";
		return;
	}
	bool Question_status;
	string txt, ans;
	int parent_id;
	if (system->AllowAnon(reciever_id)) {
		cout << "Do you want to ask anonymously ? (0:No / Yes:1): ";
		cin >> Question_status;
		while (!IsValidInput(Question_status, 0, 1) || cin.fail()) {
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "Invalid Input ....Try Again.\n";
			cout << "Do you want to ask anonymously ? (0:No / Yes:1): ";
			cin >> Question_status;
		}
		cin.ignore(10000, '\n');

	}
	else {
		cout << "Note: Anonymous questions are not allowed for this user\n";
		Question_status = 0; // 1 =  means anonymous Question 1 = reciever allows asking him anonymous questions
	}

	cout << "For thread question enter parent ID or -1 for new Qestion: ";
	cin >> parent_id;
	int max_quesid = system->Get_Max_QuesID();
	while (!IsValidInput(parent_id, -1, max_quesid) || cin.fail()) {
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "can\'t find this Question....Try Again.\n";
		cout << "For thread question enter parent ID or -1 for new Qestion: ";
		cin >> parent_id;
	}
	cin.ignore(10000, '\n');
	cout << "Enter question text: ";
	getline(cin, txt);
	ans = "Not answered yet";
	system->Ask_Question(txt, ans, system->Get_Current_User(), reciever_id, parent_id, Question_status);
	cout << "Your question has been sent\n";


}

void Frontend::Print_Thread_Recursive(const ThreadTree& node, int level) {
	string spaces(level * 4, ' ');
	cout << spaces;
	if (level > 0)cout << ">>Thread: ";
	else cout << "Question: ";


	cout << node.parentQuestion->Get_question_text() << " (" << node.parentQuestion->Get_Question_id() << ")";
	if (node.parentQuestion->Get_is_anonymous()) cout << " [Anon]";
	else cout << " From [User: " << node.parentQuestion->Get_from_user_id() << "]";
	cout << "-> To: [User " << node.parentQuestion->Get_to_user_id() << "]" << endl;

	string answerIndent = spaces;


	cout << answerIndent << ">>Answer: " << node.parentQuestion->Get_answer() << endl;
	for (auto& child : node.childThreads) {

		Print_Thread_Recursive(child, level + 1);

	}
}

void Frontend::Print_Received_Questions() {
	auto tree = system->Get_Received_Questions_Tree();
	if (tree.empty()) {
		cout << "No Questions\n";
		return;
	}

	for (const auto& rootNode : tree) {
		Print_Thread_Recursive(rootNode, 0);
		cout << "---------------------------------\n";
	}
}

void Frontend::Print_User_Questions() {
	vector<Question*> userQues = system->Get_User_Questions();
	if (userQues.empty()) {
		cout << "User has no Questions\n";
		return;
	}
	for (const auto& Ques : userQues) {
		cout << "Question ID (" << Ques->Get_Question_id() << ") ";
		if (Ques->Get_is_anonymous()) {
			cout << "[Anon]";
		}
		cout << "to user ID (" << Ques->Get_to_user_id() << ") " << endl;

		if (Ques->Get_parent_id() != -1) {
			cout << "\t[Reply to Question ID: " << Ques->Get_parent_id() << "]\n";
		}
		cout << "Question: " << Ques->Get_question_text() << endl;
		cout << "Answer: " << Ques->Get_answer() << endl;

		cout << "--------------------------------------------------\n";
	}
}

void Frontend::Get_User_Answer() {
	cout << "Enter Question ID or -1 to cancel operation: ";
	int tempid;
	cin >> tempid;
	while (cin.fail() || !(tempid == -1 || system->Is_Ques_Found(tempid))) {
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "can\'t find this Question....Try Again\n";
		cout << "Enter Question ID or -1 to cancel operation: ";
		cin >> tempid;

	}

	cin.ignore(10000, '\n');
	Question* current_ques = system->QData(tempid);
	if (current_ques->Get_to_user_id() != system->Get_Current_User()) {
		cout << "You are not allowed to answer this Question\n";
		return;
	}
	cout << "Question ID (" << current_ques->Get_Question_id() << ") ";

	if (!current_ques->Get_is_anonymous())
		cout << "from user ID (" << current_ques->Get_from_user_id() << ")\n";
	else
		cout << "[Anon] \n";
	cout << "Question: " << current_ques->Get_question_text() << endl;
	if (current_ques->Get_answer() != "Not answered yet") {
		cout << "Warning: Question is already answered,\nIf you want to change answer enter yes or no to cancel: ";
		string status;
		getline(cin, status);
		status = convert_into_lower(status);
		while (status != "yes" && status != "no") {
			cout << "Invalid Input..Please try again\n";
			cout << "If you want to answer enter yes or no to cancel: ";
			getline(cin, status);
			status = convert_into_lower(status);
		}

		if (status == "no") {
			cout << "Operation has been cancelled\n";
			return;
		}
	}

	string ans;
	cout << "Enter answer: ";
	getline(cin, ans);
	system->Answer_Question(ans, current_ques->Get_Question_id());
	cout << "Answer has been updated sucessfully.\n";
	cout << "----------------------------------------\n";

}

void Frontend::List_System_Users() {
	std::vector<std::pair<int, std::string>> users = system->List_Users();

	for (const auto& temp : users) {
		cout << "Name: " << temp.second << " [" << temp.first << "] \n";
	}
}

void Frontend::List_Feed() {
	vector<ThreadTree> feed = system->Build_Feed_Tree();
	if (feed.empty()) {
		cout << "No Questions\n";
		return;

	}
	cout << "\n================= System Feed ================= \n";
	for (const auto& ques : feed) {
		Print_Thread_Recursive(ques, 0);
		cout << "-----------------------------------\n";

	}
}

void Frontend::DeleteQuestion() {
	cout << "Enter Question ID to delete or -1 to cancel operation: ";
	int id;
	cin >> id;
	while (cin.fail() || !(id == -1 || system->Is_Ques_Found(id))) {
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Invalid Input. Try again.\n";
		cout << "Enter Question ID to delete or -1 to cancel operation: ";
		cin >> id;
	}
	cin.ignore(10000, '\n');


	bool status = system->Delete_Question(id);
	if (status) {
		cout << "Question Deleted sucessfully\n";

	}
	else {
		cout << "You are not allowed to delete this Question\n";
	}


}
