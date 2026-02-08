#ifndef COURSE_
#define COURSE_
#include<string>
#include<vector>
#include <algorithm>
#include"DateTime.h"

struct Solution {
public:

	Solution(int studID, std::string ans) :student_id(studID), answer_text(ans) {}
	void Set_Grade(double grade) {
		this->grade = grade;
	}
	void Set_commnet(std::string comment) {
		this->doc_comment = comment;
	}
	double Get_Grade()const {
		return this->grade;
	}
	int Get_Student_ID()const {
		return this->student_id;
	}

	std::string Get_Comment()const {
		return this->doc_comment;
	}
	std::string Get_Answer()const
	{
		return this->answer_text;
	}

private:

	int student_id;
	std::string answer_text{ "NOT ANSWERED YET" };
	double grade{ -1 };
	std::string doc_comment{ "NO COMMENT" };
};


struct Assignment {
public:

	Assignment(int id, const std::string& content, double max_grade, int AllowedTime)
		: id(id),
		Assignment_TXT(content),
		max_grade(max_grade),
		deadline(DateTime::GetFutureDate(AllowedTime))
	{
	}


	Assignment(int id, const std::string& content, double max_grade, const DateTime& end)
		: id(id),
		Assignment_TXT(content),
		max_grade(max_grade),
		deadline(end)
	{
	}
	Assignment(const Assignment&) = delete;
	Assignment& operator=(const Assignment&) = delete;
	void Add_Solution(Solution* studsol) {
		Student_Solutions.push_back(studsol);
	}

	std::vector<Solution*>& Get_solutions() {
		return this->Student_Solutions;
	}

	double Get_Max_Grade()const {
		return this->max_grade;
	}
	int Get_Assignment_ID()const {
		return this->id;
	}
	std::string Get_Assignment_content()const {
		return this->Assignment_TXT;
	}
	~Assignment() {
		for (auto sol : Student_Solutions) {
			delete sol;
		}
		Student_Solutions.clear();
	}
	int Get_Graded_Solutions()const {
		int count = 0;
		for (auto sol : Student_Solutions) {
			if (sol->Get_Grade() != -1) {
				count++;
			}
		}
		return count;
	}
	DateTime Get_Deadline()const {
		return deadline;
	}
	void ExtendDeadline(int days) {
		deadline.addDays(days);
	}
	void Set_DateTime(int allowedDays) {
		deadline = deadline.GetFutureDate(allowedDays);
	}
	bool ISGradedSol(int studentID) {
		for (const auto& sol : Student_Solutions) {
			if (sol->Get_Student_ID() == studentID) {
				if (sol->Get_Grade() != -1) {
					return true;
				}

			}
		}
		return false;

	}

	bool Remove_Solution(int student_id) {
		for (auto it = Student_Solutions.begin(); it != Student_Solutions.end(); ++it) {

			if ((*it)->Get_Student_ID() == student_id) {

				delete* it;

				Student_Solutions.erase(it);

				return true;
			}
		}
		return false;
	}
private:
	int id;
	std::string Assignment_TXT{};
	double max_grade{ -1 };
	std::vector<Solution*> Student_Solutions;
	DateTime deadline;

};

class Course
{
public:
	Course(int id, std::string Name, int doc_id, std::string DrName, std::string code);
	~Course();
	int Get_Course_ID()const;
	int Get_Doc_ID()const;
	std::string Get_Code()const;
	std::vector<Assignment*>& Get_Assignments();
	void Add_Assignment(std::string content, double max_grade, int allowedtime);
	std::string Get_CourseName()const;
	int Get_Active_Assignments()const;
	int Registered_Students{ 0 };
	std::string Get_Dr_Name()const;
	void Add_Assignment(std::string content, double max_grade, DateTime deadline, int id);
	void Handle_Stud_Unregister(int studentID);


private:
	int Assignment_counter = 1;
	static int Courses_counter;
	std::vector<Assignment*> Course_Assignment;
	int Course_ID{};
	std::string Course_Name{};
	int doctor_id{};
	std::string code{};
	std::string DrName;


};

#endif
