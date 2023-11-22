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
	//if text is not empty, it must end with endline (\n) - if not present, it is added in constructor
	TextNote(std::string title, std::string text = "");
	TextNote(std::string title, std::string text, std::time_t creation_time);
	std::string text() const;
	void print(std::ostream &out = std::cout) const;
	std::ostream& output(std::ostream &out) override;
	void save_to(BaseStorageSaver &storage) override;

private:
	std::string _text;
	void normalize_text();

    virtual MatchResult _match(SearchCriteria<std::string, std::time_t> *criteria) override;
};

#endif /* TEXTNOTE_H_ */
