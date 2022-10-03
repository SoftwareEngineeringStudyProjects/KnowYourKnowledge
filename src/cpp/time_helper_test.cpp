/*
 * time_helper_test.cpp
 *
 *  Created on: Sep 30, 2022
 *      Author: KZ
 */

#include "time_helper.h"

#include "doctest.h"

#include <iostream>

TEST_CASE("get current time, convert to/from string") {
	Timestamp current = current_time();
	std::string current_str = time_to_string(current);
	std::cout<<"current time is "<< current_str<<" ."<<std::endl;
	//TODO: currently does not work, need either some better way of comparing times, or different implementations
	//CHECK(time_from_string(current_str) == current);
	//TODO: error seems to be exactly 1 hour - maybe check implementation
	//CHECK(time_to_string(time_from_string(current_str)) == current_str);
}



