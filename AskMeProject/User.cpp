#include "User.h"



User::User(int id, const std::string& username, const std::string& password, const std::string& email, const std::string& name, bool anony) :id(id), username(username), password(password), email(email), Name(name), allowanony(anony) {
}

User:: ~User() {
}


std::string User::GetName() const {
	return this->Name;
}


std::string User::GetPassword() const {
	return this->password;
}


std::string User::GetUserName() const {
	return this->username;
}


std::string User::Get_email()const {
	return this->email;
}


bool User::Getallowanony()const {
	return this->allowanony;
}


void User::SetID(int loadid) {
	this->id = loadid;
}



int User::GetID() const {
	return this->id;
}
