#ifndef DATETIME_
#define DATETIME_
#include<string>
#include <ctime>
class DateTime
{
public:


	int day, month, year;
	int hour, minute;
	bool isBefore(const DateTime& now) const;
	std::string toString() const;
	static DateTime getCurrentDateTime();
	void addDays(int daysCount);
	DateTime(int days, int month, int year, int hour, int minute);
	static ::DateTime GetFutureDate(int days);


};

#endif 