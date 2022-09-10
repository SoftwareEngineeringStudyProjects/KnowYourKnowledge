/*
 * TextNoteCollection.h
 *
 *  Created on: 10 Sep. 2022
 *      Author: MouseCreator
 */

#ifndef TEXTNOTECOLLECTION_H_
#define TEXTNOTECOLLECTION_H_
#include <vector>
#include "TextNote.h"
class TextNoteCollection {
public:
	TextNoteCollection(std::string name, std::time_t creation_time);
	virtual ~TextNoteCollection();

	void addNote(TextNote note);
	void removeNote(TextNote note);
	TextNote getNote(std::size_t num);
	std::string title();
	std::time_t creation_time();
	std::size_t size();
private:
	std::vector<TextNote> notes;

	std::string _title;
	std::time_t _creation_time;
};

#endif /* TEXTNOTECOLLECTION_H_ */
