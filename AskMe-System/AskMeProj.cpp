
#include"User.h"
#include"questions.h"
#include<iostream>
#include <limits>
#include <algorithm>

int current_user_state;
bool end_program = false;
void user_operations() {
    LoadData();
    cout << "Welcome\n";

    cout << "Menu:\n\
                        1: Login\n\
                        2: Sign Up\n\
                        3: Exit system\n";
  
    int choice;
   
   choice = get_valid_int("Enter number in range 1 - 3:", 1, 3);

    if (choice == 1) {
        current_user_state = login();
        while (current_user_state == -1) {
            current_user_state = login();
        }


    }
    else if (choice == 2) {


        current_user_state = SignUp();
        SaveData();



    }
    else {
        end_program = true;
        
    }

}

void menu() {

    int choice_2;
    while (true){


        cout << "Menu:\n\
                   1: Print Questions To Me\n\
                   2: Print Questions From Me\n\
                   3: Answer Question\n\
                   4: Delete Question\n\
                   5: Ask Question\n\
                   6: List System Users\n\
                   7: Feed\n\
                   8: Logout\n";
        
       choice_2 = get_valid_int("Enter number in range 1 - 8: ", 1, 8);
        if (choice_2 == 8) {
            cout << "Log out sucessfully\n";
            return;

            


        }
        
        if (choice_2 == 1) {
            print_question_to_me(current_user_state);
            cout<<"\n__________________________________________\n";

        }
        else if (choice_2 == 2) {
            print_question_from_me(current_user_state);
            cout << "\n__________________________________________\n";


        }
        else if (choice_2 == 3) {

            AnswerQuestion(current_user_state);
            SaveQuesData();
            cout << "\n__________________________________________\n";
        }
        else if (choice_2 == 4) {
            delete_question(current_user_state);
            SaveQuesData();
            cout << "\n__________________________________________\n";

        }
        else if (choice_2 == 5) {

            Ask_Question(current_user_state);
            SaveQuesData();
            cout << "\n__________________________________________\n";

        }
        else if (choice_2 == 6) {
            list_users();
            cout << "\n__________________________________________\n";

        }
        else if (choice_2 == 7) {
            feed();



        }
        

      }
    

}

int main() {
    LoadQuesData();
    while (true) {
       
        user_operations();
        if (end_program) {
            cout << "Exiting system\n";
                return 0;
        }
      
        menu();
       

    }
   

}



