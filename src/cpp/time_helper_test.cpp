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
	CHECK(time_from_string(current_str) == current);

	std::string converted = time_to_string(time_from_string(current_str));
  std::cout<<"current time (converted) is "<< converted<<" ."<<std::endl;
	//TODO: error seems to be exactly 1 hour - maybe check implementation
	CHECK(converted == current_str);
	//TODO: sometimes this check works, and previous doesn't, even though they should be the same
	//CHECK(time_to_string(time_from_string(current_str)) == current_str);

}

TEST_CASE("fixed time, convert to/from string") {
  std::string fixed_str;
  SUBCASE("September") { // should use DST
    fixed_str = "2023.09.13 14:33:33";
  }
  SUBCASE("January") { // no DST
    fixed_str = "2023.01.13 14:33:33";
  }

  std::string converted = time_to_string(time_from_string(fixed_str));
  std::cout<<" time (converted) is "<< converted<<" ."<<std::endl;
  CHECK(converted == fixed_str);

}

TEST_CASE("check time difference") {
  std::string start_str = "2023.09.13 14:33:33";
  std::string end_str;
  int expected_diff_s;
  SUBCASE("1 minute") {
    end_str = "2023.09.13 14:34:33";
    expected_diff_s = 60;
  }
  SUBCASE("1 hour") {
    end_str = "2023.09.13 15:33:33";
    expected_diff_s = 60*60;
  }
  SUBCASE("1 day") {
    end_str = "2023.09.14 14:33:33";
    expected_diff_s = 24*60*60;
  }

  Timestamp start_time = time_from_string(start_str);
  Timestamp end_time = time_from_string(end_str);

  CHECK(end_time - start_time == expected_diff_s);

}

