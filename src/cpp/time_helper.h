/*
 * time_helper.h
 *
 *  Created on: Sep 30, 2022
 *      Author: KZ
 */

#ifndef TIME_HELPER_H_
#define TIME_HELPER_H_

#include <string>
#include <ctime>

using Timestamp = std::time_t;

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
	return std::mktime(&tm);
}


#endif /* TIME_HELPER_H_ */
