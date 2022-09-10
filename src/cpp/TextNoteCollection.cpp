/*
 * TextNoteCollection.cpp
 *
 *  Created on: 10 Sep 2022
 *      Author: MouseCreator
 */

#include "TextNoteCollection.h"

TextNoteCollection::TextNoteCollection(std::string title, std::time_t creation_time):
_title(title), _creation_time(creation_time){}

TextNoteCollection::~TextNoteCollection() {

}


std::string TextNoteCollection::title() {
	return _title;
}
std::time_t TextNoteCollection::creation_time() {
	return _creation_time;
}
std::size_t TextNoteCollection::size() {
	return notes.size();
}
TextNote TextNoteCollection::getNote(std::size_t num) {
	return notes[num];
}
