#ifndef BACKEND_H_
#define BACKEND_H_
#include<map>
#include<string>
#include"User.h"
#include"Question.h"
#include<vector>
#include <utility>
struct ThreadTree {
	Question* parentQuestion;
	std::vector<ThreadTree> childThreads;
};


class Backend
{
public:
	~Backend();
	void LoadDatabase();
	void SaveDatabase();
	static int Login(std::string, std::string);
	static int SignUp(const std::string&, const std::string&, const std::string&, const std::string&, bool);
	static void SetSystemCounter(int);
	void Ask_Question(const std::string&, const std::string&, int, int, int, bool);
	int Get_Max_UserID()const;
	static void Set_Current_User(int);
	int Get_Current_User()const;
	bool AllowAnon(int)const;
	int Get_Max_QuesID()const;
	std::vector<Question*> Get_User_Questions()const;
	std::vector<ThreadTree>Get_Received_Questions_Tree()const;
	Question* QData(int) const; 
	void Answer_Question(const std::string&, int);
	bool Is_Ques_Found(int);
	bool Is_User_Found(int);
	std::vector<std::pair<int, std::string>>List_Users()const;
	std::vector<ThreadTree>Build_Feed_Tree()const;
	bool Delete_Question(int);

private:
	void Get_All_Children_IDs(int, std::vector<int>&);
	ThreadTree Build_Thread_Tree(Question*)const;
	static int Current_User;
	static int User_Choice;
	static std::map<int, User*>UsersData;
	static std::map <int, Question*> QuesData;
	static int counter_;
	static int counter;
	void LoadUsersData();
	void SaveUsersData();
	void LoadQuesData();
	void SaveQuestionsData();


};
#endif
