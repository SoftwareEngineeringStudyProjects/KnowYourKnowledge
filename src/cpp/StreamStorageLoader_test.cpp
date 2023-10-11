/*
 * StreamStorageLoader_test.cpp
 *
 *  Created on: Oct 21, 2022
 *      Author: KZ
 */


#include "StreamStorageLoader.h"
#include "time_helper.h"

#include "doctest.h"

#include <sstream>

TEST_CASE("trim string") {
  std::string test = "  hello  world!    ";
  string_helper::trim(test);
  CHECK(test=="hello  world!");
}

TEST_CASE("load textnote from string") {
  Timestamp now = current_time();
  std::string current_time_str = time_to_string(now);
  std::string text;
  SUBCASE("note without text") {
    text = "";
  }
  SUBCASE("note with text") {
    text = "this is text\ntext\n";
  }
  std::string input = current_time_str + "\nhello\n" + text;


  std::istringstream instream{input};
  StreamStorageLoader<std::istringstream> loader {instream};
  KnowledgeItemPtr item = loader.load();

  CHECK(item->title() == "hello");
  CHECK(item->creation_time() == now);
  TextNote* note = dynamic_cast<TextNote*>(item);
  REQUIRE(note != nullptr);
  CHECK(note->text() == text);


}

TEST_CASE("loading note with empty title causes exception") {
  Timestamp now = current_time();
  std::string current_time_str = time_to_string(now);
  std::string text;
  SUBCASE("note without text") {
    text = "";
  }
  SUBCASE("note with text") {
    text = "this is text\ntext\n";
  }
  std::string input = current_time_str + "\n\n" + text;


  std::istringstream instream{input};
  StreamStorageLoader<std::istringstream> loader {instream};

  SUBCASE("check with bool variable") {
    bool exception_caught = false;
    try {
      KnowledgeItemPtr item = loader.load();
    }
    catch(const std::runtime_error& ex) {
      CHECK(std::string(ex.what())=="Title can't be empty");
      exception_caught = true;
    }
    CHECK(exception_caught);
  }

  SUBCASE("check for unreachable code") {
    try {
      KnowledgeItemPtr item = loader.load();
      CHECK(false); // this should be unreachable
    }
    catch(const std::runtime_error& ex) {
      CHECK(std::string(ex.what())=="Title can't be empty");
    }
  }

  SUBCASE("check with custom macro") {
    CHECK_THROWS_WITH_AS (loader.load(), "Title can't be empty", std::runtime_error);
  }


}

TEST_CASE("load directory from string") {
  std::string current_time_str = time_to_string(current_time());

}

