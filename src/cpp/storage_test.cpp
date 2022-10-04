/*
 * storage_test.cpp
 *
 *  Created on: Oct 4, 2022
 *      Author: KZ
 */


#include "storage.h"
#include "TextNote.h"
#include "time_helper.h"

#include "doctest.h"

#include <iostream>
#include <sstream>

TEST_CASE("working with stream storage") {
	StreamStorageSaver<std::stringstream> storage;
	StreamStorageSaver<std::ostream> storage_console{std::cout};
	TextNote note("hello");
	std::string current_time_str = time_to_string(current_time());

	storage.save(&note);
	storage_console.save(&note);

	std::string expected = current_time_str + "\nhello\n";
	CHECK(storage.underlying_stream().str() == expected);
}

TEST_CASE("working with stream storage - notes with text") {
	StreamStorageSaver<std::stringstream> storage;
	StreamStorageSaver<std::ostream> storage_console{std::cout};
	TextNote note("hello","this is text\ntext\n");
	std::string current_time_str = time_to_string(current_time());

	storage.save(&note);
	storage_console.save(&note);

	std::string expected = current_time_str + "\nhello\n" + "this is text\ntext\n";
	CHECK(storage.underlying_stream().str() == expected);
}

