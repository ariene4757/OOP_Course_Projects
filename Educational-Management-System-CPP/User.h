#ifndef USER_H_
#define USER_H_
#include<string>
#include <vector>
#include<utility>
#include"Course.h"


class User
{
public:
	User(int id, std::string name, std::string username, std::string email, std::string password);
	virtual ~User();
	std::string Get_Name()const;
	std::string Get_User_name()const;
	std::string Get_Email()const;
	std::string Get_Password()const;
	virtual std::vector<std::string> Get_Menu()const = 0;
	int Get_UserID()const;
	virtual std::string ToString()const = 0;
	virtual std::vector<std::string> Get_Courses_Codes()const = 0;
	virtual std::vector<std::string> Course_Details_Dash_Board() = 0;
	virtual std::vector<std::string> Get_Course_Details(Course* course) = 0;



private:
	static int user_counter;
	int user_id;
	std::string name{};
	std::string email{};
	std::string user_name{};
	std::string password{};


};

#endif