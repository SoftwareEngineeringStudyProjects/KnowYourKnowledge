/*
 * TextNote.cpp
 *
 *  Created on: Sep 8, 2022
 *      Author: KZ
 */

#include "TextNote.h"

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

std::string TextNote::creation_time_string() const {
	return std::asctime(std::localtime(&_creation_time));
}
std::time_t TextNote::creation_time() const {
	return _creation_time;
}

void TextNote::print() const {
	std::cout<<"title="<<title()<<", text="<<text()<<",created="<<creation_time_string()<<std::endl;
}
