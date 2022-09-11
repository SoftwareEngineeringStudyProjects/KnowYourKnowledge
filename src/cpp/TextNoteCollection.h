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
	TextNoteCollection(std::string title);
	TextNoteCollection(std::string title, std::time_t creation_time);
	virtual ~TextNoteCollection();

	TextNoteCollection* add(TextNote note);
	//TODO: void remove();
	TextNote get(std::size_t num) const;
	std::string title() const;
	std::time_t creation_time() const;
	std::string creation_time_string() const;
	std::size_t size() const;
	void print() const;
private:
	std::vector<TextNote> notes;

	std::string _title;
	std::time_t _creation_time;
};

#endif /* TEXTNOTECOLLECTION_H_ */
