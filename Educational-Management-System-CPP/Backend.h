#ifndef BACKEND_
#define BACKEND_
#include"UserManager.h"
#include"CoursesManager.h"
class Backend
{
public:
	void SignUp(std::string name, std::string username, std::string email, std::string password, int type, std::string Doc_Code = "", double gpa = 0.0);
	User* current_user = nullptr;
	void Login(std::string username, std::string password);
	std::vector<std::string> Get_Dash_Menu()const;
	void Create_Course(std::string CourseName, std::string  CourseCode);
	void Load_Database();
	void Save_Database();
	Backend();
	~Backend();
	void Register_In_Course(std::string code);
	std::vector<std::pair<std::string, std::string>> User_Courses();
	std::vector<std::string> Details_Dash();
	std::vector<std::string> CourseDetails(std::string code);
	void Add_Assignment(std::string code, std::string content, double max_grade, int allowedtime);
	bool CourseExist(std::string code);
	std::string Get_Assignment_Content(std::string code, int id);
	bool Valid_Sol_Submition(std::string code, int id);
	void Answer_Assignment(std::string sol, std::string code, int id);
	void valid_Assignment_ID(std::string code, int  id);
	std::vector<Solution*> Get_Solutions(std::string code, int id);
	int Get_AssigMax_Grade(std::string code, int id);
	Course* Get_Course(std::string code)const;
	std::vector<Student*> Get_All_Students();
	void Grade_Solution(double Grade, int assignmentId, std::string coursecode, int studID, std::string comment= "");
	bool IsSolutionDraded(std::string code, int assignmentID, int studentID);
	bool DoesSolutionExist(std::string code, int id, int studentID);
	bool Has_Solutions(std::string code, int id);
	std::pair<std::pair<int ,std::pair<std::string,double>>, std::vector<std::string>> Get_User_Report();
	void Unregister_From_Course(std::string code);
private:
	UserManager user_manager;
	CoursesManager course_manager;

};





#endif