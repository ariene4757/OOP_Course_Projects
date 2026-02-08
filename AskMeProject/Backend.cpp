#include "Backend.h"
#include"User.h"
#include"Question.h"
#include<sstream>
#include <iostream>
#include<iostream>
#include<fstream>

using namespace std;

int Backend::counter = 0;
std::map<int, User*> Backend::UsersData;
std::map <int, Question*>Backend::QuesData;
int Backend::Current_User = -1;


void Backend::LoadDatabase() {
	LoadUsersData();
	LoadQuesData();
}

void Backend::SaveDatabase() {
	SaveUsersData();
	SaveQuestionsData();
}

void Backend::SaveUsersData() {
	ofstream out("UsersData.txt");
	if (out.fail()) {
		cerr << "Warning: couldn't open file.\n";
		return;
	}
	for (pair<int, User* > p : UsersData) {
		out << p.first << '|' << p.second->GetName() << '|' << p.second->GetUserName()
			<< '|' << p.second->GetPassword() << '|' << p.second->Get_email() << '|' << p.second->Getallowanony() << "\n";
	}
	out.close();

}

int Backend::SignUp(const std::string& username, const std::string& password, const std::string& email, const std::string& name, bool allowanony) {
	counter++;

	UsersData[counter] = new User(counter, username, password, email, name, allowanony);
	return counter;

}

int Backend::Login(std::string username, std::string password) {

	for (auto tempuser = UsersData.begin(); tempuser != UsersData.end(); tempuser++) {
		if (tempuser->second->GetUserName() == username) {
			if (tempuser->second->GetPassword() == password) {
				std::cout << "Welcome back," << tempuser->second->GetName() << std::endl;
				return tempuser->first;

			}
		}
	}
	return -1;

}

void Backend::SetSystemCounter(int lastId) {
	counter = lastId;
}

void Backend::SaveQuestionsData() {
	ofstream fout("QuestionsData.txt");
	if (fout.fail()) {
		cerr << "Warning: couldn't open file.\n";
		return;
	}

	for (pair<int, Question*>x : QuesData) {
		fout << x.first << '|' << x.second->Get_question_text() << '|' << x.second->Get_from_user_id() << '|' << x.second->Get_to_user_id()
			<< '|' << x.second->Get_parent_id() << '|' << x.second->Get_answer() << '|' << x.second->Get_is_anonymous() << "\n";
	}
	fout.close();
}

void Backend::LoadQuesData() {
	/*----------------------------------------------------------------------------------------*/

	ifstream fin("QuestionsData.txt");
	if (fin.fail()) {

		cout << "No previous data found.\n";
		return;
	}
	QuesData.clear();
	string line;
	int id, userid, recid, parentid;
	string ans, txt;
	bool isAnon;
	int maxID = 0;

	while (getline(fin, line)) {
		if (line.empty()) {
			continue;
		}
		istringstream iss(line);
		string field;
		getline(iss, field, '|');
		id = stoi(field);
		getline(iss, field, '|');
		txt = field;
		getline(iss, field, '|');
		userid = stoi(field);

		getline(iss, field, '|');
		recid = stoi(field);

		getline(iss, field, '|');
		parentid = stoi(field);
		getline(iss, field, '|');
		ans = field;
		getline(iss, field, '|');
		isAnon = stoi(field);
		Question* newQues = new Question(id, txt, ans, userid, recid, parentid, isAnon);
		QuesData[id] = newQues;

		if (id > maxID) {
			maxID = id;
		}



	}
	fin.close();
	Question::SetCurrent_QuesID(maxID);

}

void Backend::LoadUsersData() {
	ifstream fin("UsersData.txt");
	if (fin.fail()) {

		cout << "No previous data found.\n";
		return;
	}
	UsersData.clear();
	string line;
	int idFromFile;
	string username, password, email, name;
	bool allowAnon;
	int maxID = 0;


	while (getline(fin, line)) {
		if (line.empty()) {
			continue;
		}
		istringstream iss(line);
		string field;
		getline(iss, field, '|');
		idFromFile = stoi(field);
		getline(iss, field, '|');
		name = field;
		getline(iss, field, '|');
		username = field;
		getline(iss, field, '|');
		password = field;
		getline(iss, field, '|');
		email = field;
		getline(iss, field, '|');
		allowAnon = stoi(field);
		User* newuser = new User(idFromFile, username, password, email, name, allowAnon);
		UsersData[idFromFile] = newuser;

		if (idFromFile > maxID) {
			maxID = idFromFile;
		}



	}
	fin.close();
	SetSystemCounter(maxID);

}

void Backend::Ask_Question(const std::string& txt, const std::string& ans, int userid, int recid, int parentid, bool isAnon) {
	int newID = Question::Get_Max_QuesID() + 1;
	Question* NewQuestion = new Question(newID, txt, ans, userid, recid, parentid, isAnon);
	QuesData[newID] = NewQuestion;
	SaveQuestionsData();
}

int Backend::Get_Max_UserID()const {
	return counter;
}

void Backend::Set_Current_User(int id) {
	Current_User = id;

}

int Backend::Get_Current_User()const {
	return Current_User;
}

bool Backend::AllowAnon(int rec) const {
	return UsersData[rec]->Getallowanony();
}

int Backend::Get_Max_QuesID()const {
	return Question::Get_Max_QuesID();
}

ThreadTree Backend::Build_Thread_Tree(Question* q)const {
	ThreadTree node;
	node.parentQuestion = q;

	for (const pair <int, Question*>& x : QuesData) {
		if (x.second->Get_parent_id() == q->Get_Question_id()) {
			ThreadTree childNode = Build_Thread_Tree(x.second);
			node.childThreads.push_back(childNode);
		}
	}
	return node;
}

std::vector<ThreadTree> Backend::Get_Received_Questions_Tree()const {
	std::vector<ThreadTree> res;
	for (const pair<int, Question*>& pair : QuesData) {
		if (pair.second->Get_to_user_id() == Current_User && pair.second->Get_parent_id() == -1) {
			Question* q = pair.second;
			res.push_back(Build_Thread_Tree(q));
		}
	}

	return res;
}

std::vector<Question*> Backend::Get_User_Questions() const {

	vector <Question*> res;
	for (const auto& temp : QuesData) {
		if (temp.second->Get_from_user_id() == Current_User) {
			res.push_back(temp.second);
		}
	}
	return res;
}

Question* Backend::QData(int id) const {
	Question* Ques = QuesData[id];
	return Ques;
}

void  Backend::Answer_Question(const string& ans, int id) {
	QuesData[id]->Set_Answer(ans);
	SaveQuestionsData();
}

bool Backend::Is_Ques_Found(int id) {
	auto it = QuesData.find(id);
	if (it == QuesData.end()) {
		return false;
	}
	else {
		return true;
	}
}

bool Backend::Is_User_Found(int id) {
	auto it = UsersData.find(id);
	if (it == UsersData.end()) {
		return false;
	}
	return true;
}

std::vector<std::pair<int, std::string>> Backend::List_Users()const {
	vector<pair<int, std::string>> users;
	for (const auto& temp : UsersData) {
		pair<int, std::string > user = make_pair(temp.first, temp.second->GetName());
		users.push_back(user);
	}
	return users;
}

std::vector<ThreadTree>Backend::Build_Feed_Tree()const {
	vector<ThreadTree>res;
	for (const auto& temp : QuesData) {
		if (temp.second->Get_parent_id() == -1) {
			res.push_back(Build_Thread_Tree(temp.second));
		}
	}
	return res;

}

void Backend::Get_All_Children_IDs(int q_id, std::vector<int>& child_ids) {
	for (const auto& Q : QuesData) {
		if (Q.second->Get_parent_id() == q_id) {
			child_ids.push_back(Q.first);
			Get_All_Children_IDs(Q.first, child_ids);


		}
	}

}


bool Backend::Delete_Question(int q_id) {
	auto it = QuesData.find(q_id);
	if (it == QuesData.end()) {
		return false;
	}

	if (it->second->Get_from_user_id() != Current_User || it->second->Get_to_user_id() == Current_User) {
		return false;
	}

	std::vector<int>ids_to_delete;
	ids_to_delete.push_back(q_id);
	Get_All_Children_IDs(q_id, ids_to_delete);
	for (int id : ids_to_delete) {
		delete QuesData[id];
		QuesData.erase(id);
	}

	SaveQuestionsData();
	return true;



}


Backend::~Backend() {
	for (auto& pair : QuesData) {
		delete pair.second;
	}
	QuesData.clear();

	for (auto& pair : UsersData) {
		delete pair.second;
	}
	UsersData.clear();
}