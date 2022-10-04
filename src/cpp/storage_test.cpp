/*
 * storage_test.cpp
 *
 *  Created on: Oct 4, 2022
 *      Author: KZ
 */


#include "storage.h"

#include "doctest.h"

#include <sstream>

TEST_CASE("working with storage") {
	StreamStorageSaver<std::stringstream> storage;

}

