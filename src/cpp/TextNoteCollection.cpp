/*
 * TextNoteCollection.cpp
 *
 *  Created on: 10 Sep 2022
 *      Author: MouseCreator
 */

#include "TextNoteCollection.h"
#include <cassert>
TextNoteCollection::TextNoteCollection(std::string title, std::time_t creation_time):
_title(title), _creation_time(creation_time){}
TextNoteCollection::TextNoteCollection(std::string title):
_title(title) { _creation_time = std::time(nullptr); }
TextNoteCollection::~TextNoteCollection() {

}


std::string TextNoteCollection::title() const{
	return _title;
}
std::time_t TextNoteCollection::creation_time() const{
	return _creation_time;
}
std::size_t TextNoteCollection::size() const {
	return notes.size();
}

TextNoteCollection* TextNoteCollection::add(TextNote note)  {
	notes.emplace_back(note);
	return this;
}
void TextNoteCollection::remove(std::size_t num) {
	assert(num < notes.size());
	notes.erase(notes.begin() + num);
}
TextNote TextNoteCollection::get(std::size_t num) const{
	return notes[num];
}
std::string TextNoteCollection::creation_time_string() const{
	return std::asctime(std::localtime(&_creation_time));
}
void TextNoteCollection::print() const{
	std::cout << "Collection:\n"<<"title="<<title()<<",created="<<creation_time_string()<<"\n";
	for (std::size_t i = 0; i < notes.size();i++) {
		notes[i].print();
	}
}
