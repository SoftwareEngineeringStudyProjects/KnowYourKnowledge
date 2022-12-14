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
	std::time_t current_time = time(nullptr);
	std::string current_time_str = std::asctime(std::localtime(&current_time));
	TextNote note1("n1");
	TextNote note2("n2","note with text");


	Directory dir("notes");
	dir.add(&note1).add(&note2);

	dir.output(std::cout);

	std::stringstream sout;
	dir.output(sout);
	std::string expected = current_time_str + "notes\n"
			+ current_time_str + "n1\n\n"
			+ current_time_str + "n2\nnote with text\n";
	CHECK(sout.str() == expected);




}


