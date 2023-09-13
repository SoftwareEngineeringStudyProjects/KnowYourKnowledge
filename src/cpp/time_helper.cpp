/*
 * time_helper.cpp
 *
 *  Created on: Oct 4, 2022
 *      Author: KZ
 */

#include "time_helper.h"


Timestamp current_time() {
	return time(nullptr);
}

std::string time_to_string(Timestamp time) {
	const unsigned int maxChar = 20;
	char date[maxChar];
	std::strftime(date, sizeof(date), "%Y.%m.%d %H:%M:%S", std::localtime(&time));
	return std::string(date);
}

//FIXME: hour seems to be wrong, +1 compared to real value
Timestamp time_from_string(const std::string& time_str) {
	struct std::tm tm;
	std::sscanf(time_str.c_str(), "%d.%d.%d %d:%d:%d", &tm.tm_year,
			&tm.tm_mon, &tm.tm_mday, &tm.tm_hour, &tm.tm_min, &tm.tm_sec);

	tm.tm_year -= 1900; //1900 -> 0, 2022 -> 122
	tm.tm_mon -= 1; //January = 0
	tm.tm_isdst = -1; // The value is positive if DST is in effect, zero if not and negative if no information is available
	return std::mktime(&tm);
}
