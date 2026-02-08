#ifndef USER_MANAGER_
#define USER_MANAGER_
#include<map>
#include<string>
#include"User.h"
#include"Student.h"
class UserManager
{
public:
	void Load_Users_Data();
	void Save_Users_Data();
	User* Add_User(int type, std::string name, std::string username, std::string email, std::string password, double gpa = 0.0);
	std::vector<std::string> Get_DashBoard(User* current_user)const;
	User* ValidUser(std::string username, std::string password);
	bool IsUserExist(std::string username)const;
	bool Register_In_Course(std::string code, User* current_user);
	void Save_Student_Courses();
	void Load_Student_Courses();
	User* Get_User_byID(int id);
	void Add_Course_In_DR_List(User* Current_User, std::string code);
	std::vector<std::string> Get_User_CourseCodes(User* current_user)const;
	std::vector<std::string> Get_Course_Details_DashBoard(User* current_user);
	std::vector<std::string> Get_Course_Details(Course* course, User* current_user);
	bool IsRegistered(Student* stud, std::string code);
	std::vector<Student*> Get_All_Students()const;
	std::pair<int, std::pair<std::string, double>> Get_User_Data(User* current_user);
	void Handle_User_Unregisteration(std::string code, Student* current_user);
	~UserManager();
private:
	static int user_count;
	std::map<std::string, User*> UserData;


};

#endif 
