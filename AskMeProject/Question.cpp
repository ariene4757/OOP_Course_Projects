#include "Question.h"
int Question::counter_ = 0;


Question::Question(int id, const std::string& txt, const std::string& ans, int userID, int recID, int parentID, bool isAnon)
	: Question_id(id), question_text(txt), answer(ans), from_user_id(userID), to_user_id(recID), parent_id(parentID), is_anonymous(isAnon)
{

	if (id > counter_) {
		counter_ = id;
	}
}

Question::~Question() {

}

std::string Question::Get_question_text() const {
	return this->question_text;
}

std::string Question::Get_answer() const {
	return this->answer;
}

int Question::Get_from_user_id() const {
	return this->from_user_id;
}

int Question::Get_to_user_id() const {
	return this->to_user_id;
}

int Question::Get_parent_id() const {
	return this->parent_id;
}

bool Question::Get_is_anonymous() const {
	return this->is_anonymous;
}

int Question::Get_Question_id() const {
	return this->Question_id;
}

void Question::SetCurrent_QuesID(int lastID) {
	counter_ = lastID;
}

int Question::Get_Max_QuesID() {
	return counter_;
}

void Question::Set_Answer(const std::string& ans) {
	answer = ans;
}