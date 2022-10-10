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

Timestamp current_time();

std::string time_to_string(Timestamp time);


Timestamp time_from_string(const std::string& time_str);

#endif /* TIME_HELPER_H_ */
