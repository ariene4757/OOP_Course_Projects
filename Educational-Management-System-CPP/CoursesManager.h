#ifndef COURSES_MANAGER_
#define COURSES_MANAGER_
#include<map>
#include"Course.h"
class CoursesManager
{
public:
	void Add_Course(std::string CourseName, int id, std::string DrName, std::string CourseCode);
	bool IsCourseExist(std::string Code);
	void LoadCourseData();
	void SaveCourseData();
	std::vector<std::string> Get_Courses(std::vector<std::string> codes);
	void Plus_St_Count(std::string code);
	void Add_Assignment(std::string content, std::string course_code, double max_grade, int allowedtime);
	Course* Get_Course(std::string code)const;
	const std::map<std::string, Course*>& Get_Course_Map();
	std::string Get_Assignment_Content(std::string code, int id);
	bool Allow_Submition(int usreID, std::string code, int id);
	void Submit_Solution(int studID, std::string sol, std::string code, int id);
	bool Solution_Graded(std::string code, int AssignmentID, int studentID);
	bool SolExist(std::string code, int AssignmentID, int studentID);
	bool Has_Solutions(std::string code, int AssignID);
	void Handle_Unregister(std::string code, int studentID);
	void Reset_All_Counts();
	~CoursesManager();
private:
	std::map<std::string, Course*> CourseData;
	static int Courses_Count;

};

#endif