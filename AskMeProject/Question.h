#ifndef QUESTION_H_
#define QUESTION_H_

#include <iostream>
#include <string>

class Question
{
public:
	Question(int id, const std::string& text, const std::string& ans, int fromUser, int toUser, int parent, bool isAnon);
	~Question();
	std::string Get_question_text() const;
	std::string Get_answer() const;
	int Get_from_user_id() const;
	int Get_to_user_id() const;
	int Get_parent_id() const;
	bool Get_is_anonymous() const;
	int Get_Question_id() const;
	static void SetCurrent_QuesID(int lastID);
	static int Get_Max_QuesID();
	void Set_Answer(const std::string&);

private:
	static int counter_;
	int Question_id;
	std::string question_text;
	int from_user_id;
	int to_user_id;
	int parent_id;
	std::string answer;
	bool is_anonymous;
};

#endif

