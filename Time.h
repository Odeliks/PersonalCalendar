#pragma once

struct Time{
	int hour;
	int minute;
	bool operator==(const Time& other) {
		return (hour == other.hour && minute == other.minute);
	}
	bool operator>(const Time& other) {
		if(hour == other.hour) {
			if(minute > other.minute) {
				return true;
			}
			return false;
		}
		if(hour < other.hour) {
			return false;
		}
		return true;
	}
	bool operator>=(const Time& other) {
		return (*this > other || *this == other);
	}
};