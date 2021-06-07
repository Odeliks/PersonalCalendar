#pragma once

struct Date {
	int day;
	int month;
	int year;
	bool operator==(const Date& other) {
		return (day == other.day && month == other.month && year == other.year);
	}
};