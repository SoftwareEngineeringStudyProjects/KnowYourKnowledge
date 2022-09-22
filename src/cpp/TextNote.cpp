/*
 * TextNote.cpp
 *
 *  Created on: Sep 8, 2022
 *      Author: KZ
 */

#include "TextNote.h"

#include "doctest.h"

#include <cassert>

TextNote::TextNote(std::string title, std::string text): _title{title}, _text{text} {
	assert(title.length() != 0);
	_creation_time = std::time(nullptr);

}

TextNote::TextNote(std::string title, std::string text, std::time_t creation_time):
		_title(title), _text(text), _creation_time(creation_time){}


std::string TextNote::title() const {
	return _title;
}

std::string TextNote::text() const {
	return _text;
}

std::time_t TextNote::creation_time() const{
	return _creation_time;
}

std::string TextNote::creation_time_string() const {
	return std::asctime(std::localtime(&_creation_time));
}

void TextNote::print() const {
	std::cout<<"title="<<title()<<", text="<<text()<<",created="<<creation_time_string()<<std::endl;
}

TEST_CASE("creating object with fixed creation time") {
	//1663850154 = Thu Sep 22 15:35:54 2022
	TextNote note("hello","this is text\ntext\n",1663850154);

	CHECK(note.title() == "hello");
	CHECK(note.text() == "this is text\ntext\n");
	CHECK(note.creation_time() == 1663850154);
	CHECK(note.creation_time_string() == "Thu Sep 22 15:35:54 2022\n");

}

