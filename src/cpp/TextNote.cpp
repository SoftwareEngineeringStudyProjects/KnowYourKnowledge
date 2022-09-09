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

std::string TextNote::title() const {
	return _title;
}

std::string TextNote::text() const {
	return _text;
}

std::string TextNote::creation_time_string() const {
	return std::asctime(std::localtime(&_creation_time));
}
