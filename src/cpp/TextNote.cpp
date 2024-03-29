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

#define NORMALIZE_NOTE_TEXT

TextNote::TextNote(std::string title, std::string text): KnowledgeItem{title}, _text{text} {
#ifdef NORMALIZE_NOTE_TEXT
  normalize_text();
#endif
}

TextNote::TextNote(std::string title, std::string text, std::time_t creation_time):
		KnowledgeItem{title, creation_time}, _text{text}{
#ifdef NORMALIZE_NOTE_TEXT
  normalize_text();
#endif
}


void TextNote::normalize_text() {
  if (_text.empty()) {return;}
  if (_text.back() == '\n') {return;}
  _text+='\n';
}

TEST_CASE("creating note without text") {
  TextNote note("title");
  CHECK(note.title() == "title");
  CHECK(note.text() == ""); // newline not added for empty text
}

TEST_CASE("creating note with text without newline") {
  TextNote note("title", "text");
  CHECK(note.title() == "title");
#ifdef NORMALIZE_NOTE_TEXT
  CHECK(note.text() == "text\n"); // newline added automatically
#else
  CHECK(note.text() == "text");
#endif
}

TEST_CASE("creating note with text with newline") {
  TextNote note("title", "text\n");
  CHECK(note.title() == "title");
  CHECK(note.text() == "text\n"); // extra newline not added
}

std::string TextNote::text() const {
	return _text;
}

void TextNote::print(std::ostream &out) const {
	out<<"title="<<title()<<", text="<<text()<<",created="<<creation_time_string();
	// creation_time_string outputs endline - no need to add another one
}

TEST_CASE("printing note") {
  TextNote note("hello");
  std::stringstream outstream;
  note.print(outstream);
  //std::cout<<outstream.str(); //TODO: replace with checks
  Timestamp current = current_time();
  std::string expected = "title=hello, text=,created="+time_to_string_detailed(current);
  CHECK(outstream.str() == expected);

}


std::ostream& TextNote::output(std::ostream &out) {
	KnowledgeItem::output(out);
	out<<text()<<std::endl;
	return out;
}

TEST_CASE("output note without text") {
  TextNote note("title");
  std::string current_time_str = time_to_string_detailed(current_time());
  std::stringstream sout;
  note.output(sout);
  CHECK(sout.str() ==
         current_time_str+
         "title\n"
         "\n");

}

TEST_CASE("output note with text without newline") {
  TextNote note("title", "text");
  std::string current_time_str = time_to_string_detailed(current_time());
  std::stringstream sout;
  note.output(sout);
  CHECK(sout.str() ==
         current_time_str+
         "title\n"
#ifdef NORMALIZE_NOTE_TEXT
         "text\n"
#else
         "text"
#endif
         "\n");


#ifdef NORMALIZE_NOTE_TEXT
  CHECK(note.text() == "text\n"); // newline added automatically
#else
  CHECK(note.text() == "text");
#endif
}

TEST_CASE("output note with text with newline") {
  TextNote note("title", "text\n");
  std::string current_time_str = time_to_string_detailed(current_time());
  std::stringstream sout;
  note.output(sout);
  CHECK(sout.str() ==
         current_time_str+
         "title\n"
         "text\n"
         "\n");
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
        "Thu Sep 22 15:35:54 2022\n" //single endline, not two
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
    TextNote item("a", "text\n");
    SearchCriteria<std::string, std::time_t> criteria;
    criteria.addEqualToCheck<std::string>("text", "nine\n");
    CHECK(item.match(&criteria) == 0);
}

TEST_CASE("Match with criteria with non-matching conditions, for text and title") {
    TextNote item("a", "text\n");
    SearchCriteria<std::string, std::time_t> criteria;
    criteria.addEqualToCheck<std::string>("title", "nine");
    criteria.addEqualToCheck<std::string>("text", "nine\n");
    CHECK(item.match(&criteria) == 0);
}

TEST_CASE("Match with criteria with non-matching type conditions, for title") {
    TextNote item("a");
    SearchCriteria<std::string, std::time_t> criteria;
    criteria.addEqualToCheck<std::string>("nine");
    CHECK(item.match(&criteria) == 0);
}

TEST_CASE("Match with criteria with non-matching type conditions, for text and title") {
    TextNote item("a", "text\n");
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
    TextNote item("a", "text\n");
    SearchCriteria<std::string, std::time_t> criteria;
    criteria.addEqualToCheck<std::string>("text", "text\n");
    CHECK(item.match(&criteria) == 1);
}

TEST_CASE("Match with criteria with matching condition, for text and title") {
    TextNote item("a", "text\n");
    SearchCriteria<std::string, std::time_t> criteria;
    criteria.addEqualToCheck<std::string>("title", "a");
    criteria.addEqualToCheck<std::string>("text", "text\n");
    CHECK(item.match(&criteria) == 1);
}

TEST_CASE("Match with criteria with matching type condition, for title") {
    TextNote item("a");
    SearchCriteria<std::string, std::time_t> criteria;
    criteria.addEqualToCheck<std::string>("a");
    CHECK(item.match(&criteria) == 0.5);
}

TEST_CASE("Match with criteria with matching type condition, for text and title") {
    TextNote item("a\n", "a\n"); // for this test, check that all string values are the same - need to set title same as text
    SearchCriteria<std::string, std::time_t> criteria;
    criteria.addEqualToCheck<std::string>("a\n");
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
    TextNote item("a", "text\n");
    SearchCriteria<std::string, std::time_t> criteria;
    criteria.addEqualToCheck<std::string>("text", "nine\n");
    criteria.addEqualToCheck<std::string>("text", "text\n");
    CHECK(item.match(&criteria) == 0.5);
}

TEST_CASE("Match with criteria with matching and non-matching conditions, for text and title") {
    TextNote item("a", "text\n");
    SearchCriteria<std::string, std::time_t> criteria;
    criteria.addEqualToCheck<std::string>("title", "nine");
    criteria.addEqualToCheck<std::string>("title", "a");

    criteria.addEqualToCheck<std::string>("text", "nine\n");
    criteria.addEqualToCheck<std::string>("text", "text\n");
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
    TextNote item("a", "nine\n");
    SearchCriteria<std::string, std::time_t> criteria;
    criteria.addEqualToCheck<std::string>("nine\n");
    criteria.addEqualToCheck<std::string>("a");
    CHECK(item.match(&criteria) == 0.5);
}
