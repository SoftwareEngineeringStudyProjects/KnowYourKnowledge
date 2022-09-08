/*
 * TextNote.h
 *
 *  Created on: Sep 8, 2022
 *      Author: KZ
 */

#ifndef TEXTNOTE_H_
#define TEXTNOTE_H_

#include <string>
#include <ctime>

class TextNote {
public:
	TextNote(std::string title, std::string text = "");
	std::string title();
	std::string text();
	std::string creation_time_string();
private:
	std::string _title;
	std::string _text;
	std::time_t _creation_time;
};

#endif /* TEXTNOTE_H_ */
