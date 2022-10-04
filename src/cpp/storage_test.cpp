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


#include <sstream>

TEST_CASE("working with stream storage") {
	StreamStorageSaver<std::stringstream> storage;
	TextNote note("hello");
	std::string current_time_str = time_to_string(current_time());

	storage.save(&note);

	std::string expected = current_time_str + "\nhello\n";
	CHECK(storage.underlying_stream().str() == expected);
}

