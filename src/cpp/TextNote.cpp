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


