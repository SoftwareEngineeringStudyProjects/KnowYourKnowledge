/*
 * TextNote.cpp
 *
 *  Created on: Sep 8, 2022
 *      Author: KZ
 */

#include "TextNote.h"

#include "doctest.h"

#include <sstream>
#include <cassert>

TextNote::TextNote(std::string title, std::string text): KnowledgeItem{title}, _text{text} {
}

TextNote::TextNote(std::string title, std::string text, std::time_t creation_time):
		KnowledgeItem{title, creation_time}, _text{text}{}

std::string TextNote::text() const {
	return _text;
}

void TextNote::print(std::ostream &out) const {
	out<<"title="<<title()<<", text="<<text()<<",created="<<creation_time_string()<<std::endl;
}

TEST_CASE("printing note") {
  TextNote note("hello");
  std::stringstream outstream;
  note.print(outstream);
  //std::cout<<outstream.str(); //TODO: replace with checks
  Timestamp current = current_time();
  std::string expected = "title=hello, text=,created="+time_to_string_detailed(current)+"\n";
  CHECK(outstream.str() == expected);

}


std::ostream& TextNote::output(std::ostream &out) {
	KnowledgeItem::output(out);
	out<<text()<<std::endl;
	return out;
}

TEST_CASE("output for object with fixed creation time") {
  //1663850154 = Thu Sep 22 15:35:54 2022
  TextNote note("hello","this is text\ntext\n",1663850154);

  CHECK(note.title() == "hello");
  CHECK(note.text() == "this is text\ntext\n");
  CHECK(note.creation_time() == 1663850154);
  CHECK(note.creation_time_string() == "Thu Sep 22 15:35:54 2022\n");

  std::stringstream sout;
  SUBCASE("output - format used in file") {
    note.output(sout);
    CHECK(sout.str() ==
        "Thu Sep 22 15:35:54 2022\n"
        "hello\n"
        "this is text\ntext\n"
        "\n");
  }
  SUBCASE("print - format used for debug") {
    note.print(sout);
    CHECK(sout.str() ==
        "title=hello, text=this is text\ntext\n,created="
        "Thu Sep 22 15:35:54 2022\n\n" //two endlines - one added by to_string_detailed, another by print
        );
  }

}


void TextNote::save_to(BaseStorageSaver &storage) {
	KnowledgeItem::save_to(storage);
	storage.save_multiline(text());
}
/*
double TextNote::match(SearchCriteria <std::string, std::time_t> *criteria)  {
    std::pair<int, int> result = _match(criteria);
    return result.first == 0 ? 1 : result.second / result.first;
}*/

MatchResult TextNote::_match(SearchCriteria<std::string, std::time_t> *criteria) {
    MatchResult baseResult = KnowledgeItem::_match(criteria);
    int passed = baseResult.passed(), total = baseResult.total();

    for (const auto& condition: criteria->get("text")) {
        if (condition(_text)) ++passed;
        ++total;
    }

    for (const auto& condition: criteria->get<std::string>()) {
        if (condition(_text)) ++passed;
        ++total;
    }

    return MatchResult(total, passed);
}



TEST_CASE("Match with empty criteria") {
    TextNote item("a");
    SearchCriteria<std::string, std::time_t> criteria;
    CHECK(item.match(&criteria) == 1);
}

TEST_CASE("Match with criteria with non-matching conditions, for title") {
    TextNote item("a");
    SearchCriteria<std::string, std::time_t> criteria;
    criteria.addEqualToCheck<std::string>("title", "nine");
    CHECK(item.match(&criteria) == 0);
}

TEST_CASE("Match with criteria with non-matching conditions, for text") {
    TextNote item("a", "text");
    SearchCriteria<std::string, std::time_t> criteria;
    criteria.addEqualToCheck<std::string>("text", "nine");
    CHECK(item.match(&criteria) == 0);
}

TEST_CASE("Match with criteria with non-matching conditions, for text and title") {
    TextNote item("a", "text");
    SearchCriteria<std::string, std::time_t> criteria;
    criteria.addEqualToCheck<std::string>("title", "nine");
    criteria.addEqualToCheck<std::string>("text", "nine");
    CHECK(item.match(&criteria) == 0);
}

TEST_CASE("Match with criteria with non-matching type conditions, for title") {
    TextNote item("a");
    SearchCriteria<std::string, std::time_t> criteria;
    criteria.addEqualToCheck<std::string>("nine");
    CHECK(item.match(&criteria) == 0);
}

TEST_CASE("Match with criteria with non-matching type conditions, for text and title") {
    TextNote item("a", "text");
    SearchCriteria<std::string, std::time_t> criteria;
    criteria.addEqualToCheck<std::string>("nine");
    CHECK(item.match(&criteria) == 0);
}

TEST_CASE("Match with criteria with matching condition, for title") {
    TextNote item("a");
    SearchCriteria<std::string, std::time_t> criteria;
    criteria.addEqualToCheck<std::string>("title", "a");
    CHECK(item.match(&criteria) == 1);
}

TEST_CASE("Match with criteria with matching condition, for text") {
    TextNote item("a", "text");
    SearchCriteria<std::string, std::time_t> criteria;
    criteria.addEqualToCheck<std::string>("text", "text");
    CHECK(item.match(&criteria) == 1);
}

TEST_CASE("Match with criteria with matching condition, for text and title") {
    TextNote item("a", "text");
    SearchCriteria<std::string, std::time_t> criteria;
    criteria.addEqualToCheck<std::string>("title", "a");
    criteria.addEqualToCheck<std::string>("text", "text");
    CHECK(item.match(&criteria) == 1);
}

TEST_CASE("Match with criteria with matching type condition, for title") {
    TextNote item("a");
    SearchCriteria<std::string, std::time_t> criteria;
    criteria.addEqualToCheck<std::string>("a");
    CHECK(item.match(&criteria) == 0.5);
}

TEST_CASE("Match with criteria with matching type condition, for text and title") {
    TextNote item("a", "a");
    SearchCriteria<std::string, std::time_t> criteria;
    criteria.addEqualToCheck<std::string>("a");
    CHECK(item.match(&criteria) == 1);
}

TEST_CASE("Match with criteria with matching and non-matching conditions, for title") {
    TextNote item("a");
    SearchCriteria<std::string, std::time_t> criteria;
    criteria.addEqualToCheck<std::string>("title", "nine");
    criteria.addEqualToCheck<std::string>("title", "a");
    CHECK(item.match(&criteria) == 0.5);
}

TEST_CASE("Match with criteria with matching and non-matching conditions, for text") {
    TextNote item("a", "text");
    SearchCriteria<std::string, std::time_t> criteria;
    criteria.addEqualToCheck<std::string>("text", "nine");
    criteria.addEqualToCheck<std::string>("text", "text");
    CHECK(item.match(&criteria) == 0.5);
}

TEST_CASE("Match with criteria with matching and non-matching conditions, for text and title") {
    TextNote item("a", "text");
    SearchCriteria<std::string, std::time_t> criteria;
    criteria.addEqualToCheck<std::string>("title", "nine");
    criteria.addEqualToCheck<std::string>("title", "a");

    criteria.addEqualToCheck<std::string>("text", "nine");
    criteria.addEqualToCheck<std::string>("text", "text");
    CHECK(item.match(&criteria) == 0.5);
}

TEST_CASE("Match with criteria with matching and non-matching type conditions, for title") {
    TextNote item("a");
    SearchCriteria<std::string, std::time_t> criteria;
    criteria.addEqualToCheck<std::string>("nine");
    criteria.addEqualToCheck<std::string>("a");
    CHECK(item.match(&criteria) == 0.25);
}

TEST_CASE("Match with criteria with matching and non-matching type conditions, for text and title") {
    TextNote item("a", "nine");
    SearchCriteria<std::string, std::time_t> criteria;
    criteria.addEqualToCheck<std::string>("nine");
    criteria.addEqualToCheck<std::string>("a");
    CHECK(item.match(&criteria) == 0.5);
}
