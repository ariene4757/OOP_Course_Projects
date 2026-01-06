#include"questions.h"
#include"user.h"
#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<limits>
#include<algorithm>
#include <cctype>
int get_valid_int(const string& prompt, int min_val, int max_val) {
    int choice;
    while (true) {
        cout << prompt;
        cin >> choice;

        if (!cin.fail() && choice >= min_val && choice <= max_val) {
            return choice;
        }

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please try again.\n";
    }
}


int last_question_id = 0;
map<int, Question> QuesData;

void LoadQuesData() {
    ifstream in("question.txt");
    if (in.fail()) {
        cerr << "Warning: couldn't open file, starting with empty data.\n";
        return;
    }
    QuesData.clear();

    string line;
    while (getline(in, line)) {
        Question u;
        if (line.empty())
            continue;
        istringstream iss(line);
        string field;
        getline(iss, field, '|'); u.from_user_id = stoi(field);
        getline(iss, field, '|'); u.parent_id = stoi(field);
        getline(iss, field, '|'); u.question_id = stoi(field);
        getline(iss, field, '|'); u.to_user_id = stoi(field);
        getline(iss, field, '|'); u.is_anonymous = stoi(field);
        getline(iss, u.text, '|');
        getline(iss, u.answer);        
        QuesData[u.question_id] = u;
        last_question_id = max(last_question_id, u.question_id);
    }
   
    in.close();
    

}

void SaveQuesData() {
    ofstream out("question.txt");
    if (out.fail()) {
        cerr << "Warning: couldn't open file.\n";
        return;
    }
    for (pair<int,Question> x : QuesData) {
        out << x.second.from_user_id << '|' << x.second.parent_id << '|' << x.second.question_id<< '|' << x.second.to_user_id << '|' << x.second.is_anonymous<< '|' << x.second.text << '|' << x.second.answer << endl;
    }

    out.close();
}

void Ask_Question(int user_id) {

    cout << "Enter User id or -1 to cancel: ";
    int num;
    cin >> num;
    while (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input.try again... \n";
        cout << "Enter User id or -1 to cancel: ";
        cin >> num;
    }
    if (num == -1) {
        cout << "Asking question canceled\n";
        return;
    }
    
    Question question;
    question.from_user_id = user_id;
    bool reciever_found = false;
    bool allow_anon;
    for (auto &x : UserData) {
        if (x.second.id == num) {
            reciever_found = true;
            question.to_user_id= num;
            allow_anon = x.second.anonymous;
            break;
        }
    }
    if (!reciever_found) {
        cout << "User you searching for is not found\n";
        return;
    }
    if (allow_anon) {
         
          question.is_anonymous = get_valid_int("Do you want to ask anonymously? (0 or 1): ", 0, 1);
    }
    else {
        cout << "Note: Anonymous questions are not allowed for this user\n";
        question.is_anonymous=0;
    }
    int question_status;
    cout << "For thread question: Enter Question id or -1 for new question: ";
    cin >> question_status;
    while (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input.try again... \n";
        cout << "For thread question: Enter Question id or -1 for new question: ";
        cin >> question_status;
    }
    if (question_status == -1) {
        question.question_id = last_question_id + 1;
        last_question_id = question.question_id;
        question.parent_id = -1;
        cout << "Enter question text: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, question.text);

    }

    else {
       
       auto iter = QuesData.find(question_status);
       if (iter != QuesData.end()) {
           question.question_id = ++last_question_id;
           question.parent_id = question_status;
           cout << "Enter question text: ";
           cin.ignore(numeric_limits<streamsize>::max(), '\n');
           getline(cin, question.text);

       }
       else {
           cout << "There is no question has this ID.\n";
           return;
           
       }
    }

    QuesData[question.question_id] = question;





}
void print_question_to_me(int user_id) {
    bool have_ques = false;
    for (pair<int, Question> tempval : QuesData) {
        if (tempval.second.to_user_id == user_id) {
            have_ques = true;
            cout << "Question ID (" << tempval.first << ")";
            if (tempval.second.is_anonymous) {
                cout << " from anonymous "<<endl;
            }
            else {
                cout<< " from user ID(" << tempval.second.from_user_id << ")\n";
            }
            cout << "Question: " << tempval.second.text << endl;
           
           cout << "Answer: " << tempval.second.answer << endl;
          
            for (pair<int, Question> tempval2 : QuesData) {
                if (tempval2.second.parent_id == tempval.first) {
                    cout << "Thread: Question ID (" << tempval2.second.question_id << ")";
                    if (tempval2.second.is_anonymous) {
                        cout << " from anonymous    Question: " << tempval2.second.text << endl;

                    }
                    else {
                        cout << " from user ID(" << tempval2.second.from_user_id << ")  Question: " << tempval2.second.text << endl;
                    }
                    
                    cout << "Thread: Answer: " << tempval2.second.answer << endl;
                   

                }
            }

        }
    }
    if (!have_ques) {
        cout << "You don\'t have any questions\n";
    }
}
void print_question_from_me(int user_id) {
    bool user_ask = false;
    for (auto& x : QuesData) {
        if (x.second.from_user_id == user_id) {
            user_ask = true;
          

                cout << "Question ID (" << x.second.question_id << ") ";
                if (!x.second.is_anonymous) {
                    cout << "Asked as Non-Anonymous ";
                }

                cout << "to user ID (" << x.second.to_user_id << ")\n";
                if (x.second.parent_id != -1) {
                    cout << "[Thread of QID(" << x.second.parent_id << ")] ";
                }
                cout << "Question: " << x.second.text << endl;
                
                cout << "Answer: " << x.second.answer << endl;
     
          

            
           
            

        }

    }
    if (!user_ask) {
        cout << "User has no questions asked\n";
    }
}
void AnswerQuestion(int user_id) {
    cout << "Enter Question ID or -1 to cancel: ";
    int quesnum;
    cin >> quesnum;
    while(cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input.try again... ";
        cin >> quesnum;

    }
    if (quesnum == -1) {
        cout << "Answering question cancelled\n";
        return;
    }
    auto t = QuesData.find(quesnum);
    if (t != QuesData.end()) {
        if (t->second.to_user_id != user_id) {
            cout << "You are not allowed to answer this question\n ";
            return;
        }
        else {
            cout << "Question: " << t->second.text << endl;
            cout << "Answer: " << t->second.answer << endl;
            if (t->second.answer != "Not answered yet") {
                cout << "\n";
                cout << "Warning:Already answered. answer will be updated \n";
                cout << "Do you want to edit the previous answer?(yes/no): ";
                string edit;
                cin >> edit;
                transform(edit.begin(), edit.end(), edit.begin(), ::tolower);
                while (cin.fail() || (edit != "yes" && edit != "no")) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input...please try again\n";
                    cin >> edit;
                    transform(edit.begin(), edit.end(), edit.begin(), ::tolower);
                }
                if (edit == "yes") {
                    cout << "Enter answer: ";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    getline(cin, t->second.answer);

                }
                else {
                    cout << "Editing answer cancelled\n";
                }
                

            }
            else {
                cout << "Enter answer: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, t->second.answer);

            }
        }
        
    }
    else {
        cout << "Question is not found \n";
        return;
    }


}
void delete_question(int user_id) {
    cout << "Enter Question ID or -1 to cancel: ";
    int question_number;
    cin >> question_number;
    while (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input.try again... ";
        cin >> question_number;


    }
    auto f = QuesData.find(question_number);
    if (f != QuesData.end()) {
        if (f->second.to_user_id != user_id) {
            cout << "You are not allowed to delete this question\n";
            return;

        }
        else {
            vector <int> Ques_To_Delete;
            
            for (pair<int, Question> v : QuesData) {
                if (v.second.parent_id == question_number) {
                    Ques_To_Delete.push_back(v.second.question_id);
                 }
                
            }
            for (int temp_id : Ques_To_Delete) {
                QuesData.erase(temp_id);
            }
            QuesData.erase(f);
            cout << "Question and all its threads (if any) were deleted successfully\n";


        }

    }
    else {
        cout << "Question is not found\n";
    }

}
void feed() {
    for (auto & p : QuesData) {
        if (p.second.parent_id == -1) {
            cout << "Question ID(" << p.second.question_id << ") ";
            if (!p.second.is_anonymous) {
                cout << "from user Id(" << p.second.from_user_id << ") ";
            }
            else {
                cout << "from anonymous ";
            }
            cout << "To user ID(" << p.second.to_user_id << ") \n";
            cout << "Question: " << p.second.text<<endl;
            cout << "Answer: " << p.second.answer << endl;
            for (auto& thrd : QuesData) {
                if (thrd.second.parent_id == p.second.question_id) {
                    cout << "   Thread ID(" << thrd.second.question_id << ") ";

                    if (!thrd.second.is_anonymous)
                        cout << "from user ID(" << thrd.second.from_user_id << ") ";
                    else
                        cout << "from anonymous ";

                    cout << "to user ID(" << thrd.second.to_user_id << ")\n";
                    cout << "   Thread: " << thrd.second.text << endl;
                    cout << "   Thread Answer: " << thrd.second.answer << endl;
                }

            }
            cout << "\n__________________________________________\n";
        }

        
    }
}