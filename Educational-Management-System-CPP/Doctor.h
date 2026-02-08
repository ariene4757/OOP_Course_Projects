#ifndef DOCTOR_
#define DOCTOR_
#include"User.h"
#include<vector>
#include"Course.h"
class Doctor :public User
{
public:

	Doctor(int id, std::string name, std::string username, std::string email, std::string password);
	~Doctor();
	std::vector<std::string> Get_Menu()const;
	std::string ToString()const;
	std::vector<std::string> Get_Courses_Codes()const;
	void Add_Course_Code(std::string code);
	std::vector<std::string> Course_Details_Dash_Board();
	std::vector<std::string> Get_Course_Details(Course* course);

private:
	std::vector<std::string > CoursesCodes;

};

#endif