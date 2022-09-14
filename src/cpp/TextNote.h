/*
 * TextNote.h
 *
 *  Created on: Sep 8, 2022
 *      Author: KZ
 */

#ifndef TEXTNOTE_H_
#define TEXTNOTE_H_

#include <ctime>
#include <string>
#include <iostream>
class TextNote {
	friend class FileBuilder;
public:
	TextNote(std::string title, std::string text = "");
	TextNote(std::string title, std::string text, std::time_t creation_time);
	std::string title() const;
	std::string text() const;
	std::string creation_time_string() const;
	std::time_t creation_time() const;
	void print() const;
private:
	std::string _title;
	std::string _text;
	std::time_t _creation_time;
};

#endif /* TEXTNOTE_H_ */
