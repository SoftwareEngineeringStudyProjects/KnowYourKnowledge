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

void TextNote::print() const {
	std::cout<<"title="<<title()<<", text="<<text()<<",created="<<creation_time_string()<<std::endl;
}

std::ostream& TextNote::output(std::ostream &out) {
	KnowledgeItem::output(out);
	out<<text()<<std::endl;
	return out;
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

std::pair<int, int> TextNote::_match(SearchCriteria<std::string, std::time_t> *criteria) {
    std::pair<int, int> baseResult = KnowledgeItem::_match(criteria);
    int passed = baseResult.second, total = baseResult.first;

    for (const auto& condition: criteria->get("text")) {
        if (condition(_text)) ++passed;
        ++total;
    }

    for (const auto& condition: criteria->get<std::string>()) {
        if (condition(_text)) ++passed;
        ++total;
    }

    return {total, passed};
}

TEST_CASE("creating object with fixed creation time") {
	//1663850154 = Thu Sep 22 15:35:54 2022
	TextNote note("hello","this is text\ntext\n",1663850154);

	CHECK(note.title() == "hello");
	CHECK(note.text() == "this is text\ntext\n");
	CHECK(note.creation_time() == 1663850154);
	CHECK(note.creation_time_string() == "Thu Sep 22 15:35:54 2022\n");

	std::stringstream sout;
	note.output(sout);
	CHECK(sout.str() ==
			"Thu Sep 22 15:35:54 2022\n"
			"hello\n"
			"this is text\ntext\n"
			"\n");

}

TEST_CASE("Match with empty criteria") {
    TextNote item("a");
    SearchCriteria<std::string, std::time_t> criteria;
    CHECK(item.match(&criteria) == 1);
}

TEST_CASE("Match with criteria with non-matching conditions") {
    TextNote item("a");
    SearchCriteria<std::string, std::time_t> criteria;
    criteria.addEqualToCheck<std::string>("title", "nine");
    CHECK(item.match(&criteria) == 0);
}

TEST_CASE("Match with criteria with non-matching type conditions") {
    TextNote item("a");
    SearchCriteria<std::string, std::time_t> criteria;
    criteria.addEqualToCheck<std::string>("nine");
    CHECK(item.match(&criteria) == 0);
}

TEST_CASE("Match with criteria with matching condition") {
    TextNote item("a");
    SearchCriteria<std::string, std::time_t> criteria;
    criteria.addEqualToCheck<std::string>("title", "a");
    CHECK(item.match(&criteria) == 1);
}

TEST_CASE("Match with criteria with matching type condition") {
    TextNote item("a");
    SearchCriteria<std::string, std::time_t> criteria;
    criteria.addEqualToCheck<std::string>("a");
    CHECK(item.match(&criteria) == 0.5);
}

TEST_CASE("Match with criteria with matching and non-matching conditions") {
    TextNote item("a");
    SearchCriteria<std::string, std::time_t> criteria;
    criteria.addEqualToCheck<std::string>("title", "nine");
    criteria.addEqualToCheck<std::string>("title", "a");
    CHECK(item.match(&criteria) == 0.75);
}

TEST_CASE("Match with criteria with matching and non-matching type conditions") {
    TextNote item("a");
    SearchCriteria<std::string, std::time_t> criteria;
    criteria.addEqualToCheck<std::string>("nine");
    criteria.addEqualToCheck<std::string>("a");
    CHECK(item.match(&criteria) == 0.5);
}