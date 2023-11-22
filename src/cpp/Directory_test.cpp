/*
 * Directory_test.cpp
 *
 *  Created on: Sep 27, 2022
 *      Author: KZ
 */


#include "Directory.h"
#include "TextNote.h"

#include "doctest.h"

#include <iostream>
#include <sstream>
#include <ctime>

TEST_CASE("creating directory containing text notes") {
	std::time_t current = current_time();
	std::string current_time_str = time_to_string_detailed(current);
	TextNote note1("n1");
	TextNote note2("n2","note with text");


	Directory dir("notes");
	dir.add(&note1).add(&note2);

	dir.output(std::cout); // TODO: remove extra spam in cout

	std::stringstream sout;
	dir.output(sout);
	std::string expected = current_time_str + "notes\n"
			+ current_time_str + "n1\n\n"
			+ current_time_str + "n2\nnote with text\n";
	CHECK(sout.str() == expected);




}


