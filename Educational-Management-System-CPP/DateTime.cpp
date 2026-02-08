#define _CRT_SECURE_NO_WARNINGS
#include "DateTime.h"
#include <ctime>
#include "DateTime.h"
#include<sstream>

bool DateTime::isBefore(const DateTime& now) const {
	if (year != now.year) return year < now.year;
	if (month != now.month) return month < now.month;
	if (day != now.day) return day < now.day;
	if (hour != now.hour) return hour < now.hour;
	return minute < now.minute;
}
std::string DateTime::toString() const {
	std::ostringstream oss;
	oss << day << "/" << month << "/" << year << "  " << hour << ":" << minute;
	return oss.str();
}

DateTime DateTime::getCurrentDateTime() {
	time_t now = time(0);
	tm* ltm = localtime(&now);

	return {
		ltm->tm_mday,
		1 + ltm->tm_mon,
		1900 + ltm->tm_year,
		ltm->tm_hour,
		ltm->tm_min
	};
}


void DateTime::addDays(int daysCount) {
	day += daysCount;
}

DateTime::DateTime(int days, int month, int year, int hour, int minute) :day(days), month(month), year(year), hour(hour), minute(minute) {

}


DateTime DateTime::GetFutureDate(int days) {
	DateTime now = getCurrentDateTime();
	now.day += days;
	while (now.day > 30) {
		now.day -= 30;
		now.month++;
		if (now.month > 12) {
			now.month = 1;
			now.year++;
		}
	}
	return now;
}