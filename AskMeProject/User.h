#ifndef USER_H_
#define USER_H_
#include<iostream>


class User
{

public:
	User(int, const std::string&, const std::string&, const std::string&, const std::string&, bool);
	~User();
	std::string GetName()const;
	std::string GetPassword()const;
	std::string GetUserName()const;
	bool Getallowanony()const;
	std::string Get_email()const;
	void SetID(int);
	int GetID() const;


private:
	std::string Name{};
	std::string password{};
	int id;
	std::string username{};
	std::string email;
	bool allowanony;

};

#endif 