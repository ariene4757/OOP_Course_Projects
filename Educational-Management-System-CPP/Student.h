#ifndef STUDENT_
#define STUDENT_
#include"User.h"
#include<vector>
#include"Course.h"


class Student : public User
{
public:

	Student(int id, std::string name, std::string username, std::string email, std::string password, double gpa);
	~Student();
	std::vector<std::string> Get_Registered_Courses()const;
	bool Register_Course(std::string code);
	double Get_GPA()const;
	std::string ToString()const;
	std::vector<std::string> Get_Menu()const;
	std::vector<std::string> Get_Courses_Codes()const;
	std::vector<std::string> Course_Details_Dash_Board();
	std::vector<std::string> Get_Course_Details(Course* course);
	bool IsRegistered_In_Course(std::string code);
	std::pair<int, std::pair<std::string, double>> Student_Data();
	bool Unregister_From_Course(std::string code);

private:
	double GPA{};
	std::vector<std::string> Registered_Courses;
};



#endif

