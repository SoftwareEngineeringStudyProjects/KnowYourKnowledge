/*
 * TextNote.h
 *
 *  Created on: Sep 8, 2022
 *      Author: KZ
 */

#ifndef TEXTNOTE_H_
#define TEXTNOTE_H_

#include "KnowledgeItem.h"

#include <ctime>
#include <string>
#include <iostream>
class TextNote: public KnowledgeItem {
	friend class FileBuilder;
public:
	TextNote(std::string title, std::string text = "");
	TextNote(std::string title, std::string text, std::time_t creation_time);
	std::string text() const;
	void print() const;
	std::ostream& output(std::ostream &out) override;

private:
	std::string _text;
};

#endif /* TEXTNOTE_H_ */
