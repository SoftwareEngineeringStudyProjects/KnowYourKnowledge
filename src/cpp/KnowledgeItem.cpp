/*
 * KnowledgeItem.cpp
 *
 *  Created on: Sep 22, 2022
 *      Author: KZ
 */

#include "KnowledgeItem.h"
#include "SearchCriteria.h"
#include "doctest.h"
#include "TextNote.h"

#include <cassert>



KnowledgeItem::KnowledgeItem(std::string title): KnowledgeItem{title, std::time(nullptr)} {
}

KnowledgeItem::KnowledgeItem(std::string title, std::time_t creation_time):
		_title{title}, _creation_time{creation_time} {
	assert(title.length() != 0);

}

KnowledgeItem::~KnowledgeItem() {
	// TODO Auto-generated destructor stub
}

std::string KnowledgeItem::title() const {
	return _title;
}

std::time_t KnowledgeItem::creation_time() const{
	return _creation_time;
}

std::string KnowledgeItem::creation_time_string() const {
	return std::asctime(std::localtime(&_creation_time));
}

std::ostream& KnowledgeItem::KnowledgeItem::output(std::ostream &out) {
	out<<creation_time_string();
	out<<title()<<std::endl;

	return out;
}

void KnowledgeItem::save_to(BaseStorageSaver &storage) {
	storage.save_creation_time(creation_time());
	storage.save_title(title());
}

double KnowledgeItem::match(SearchCriteria<std::string, std::time_t> *criteria) {
    double passed = 0, total = 0;
    for (const auto &condition: criteria->get("title")) {
        if (condition(_title)) ++passed;
        ++total;
    }
    for (const auto &condition: criteria->get("creation_time")) {
        if (condition(_creation_time)) ++passed;
        ++total;
    }
    if (total == 0) return 1;
    return passed / total;
}