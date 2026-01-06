#ifndef QUESTION_H
#define QUESTION_H
#include <string>
#include <map>
using namespace std;

struct Question {
    int question_id;
    int from_user_id;
    int to_user_id;
    int parent_id;
    string text;
    string answer = "Not answered yet";
    bool is_anonymous;

};




extern int last_question_id;

extern map<int, Question> QuesData;

void Ask_Question(int);

void SaveQuesData();
void LoadQuesData();
void print_question_to_me(int);
void print_question_from_me(int);
void AnswerQuestion(int);
void delete_question(int);
void feed();
int get_valid_int(const string&, int, int);


#endif


