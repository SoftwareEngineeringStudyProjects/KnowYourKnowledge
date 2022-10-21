/*
 * StreamStorageLoader_test.cpp
 *
 *  Created on: Oct 21, 2022
 *      Author: KZ
 */


#include "StreamStorageLoader.h"

#include "doctest.h"

TEST_CASE("trim string") {
  std::string test = "  hello  world!    ";
  string_helper::trim(test);
  CHECK(test=="hello  world!");
}

