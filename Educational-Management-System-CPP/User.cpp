#include "User.h"





User::User(int id, std::string name, std::string username, std::string email, std::string password) :
	user_id(id), name(name), user_name(username), email(email), password(password)
{
}

User:: ~User() {}

std::string User::Get_Name()const {
	return this->name;
}

std::string User::Get_User_name()const {
	return this->user_name;
}

std::string User::Get_Email()const {
	return this->email;
}

std::string User::Get_Password()const {
	return this->password;
}

int User::Get_UserID()const {
	return this->user_id;
}





