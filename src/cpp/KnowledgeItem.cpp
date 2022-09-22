/*
 * KnowledgeItem.cpp
 *
 *  Created on: Sep 22, 2022
 *      Author: KZ
 */

#include "KnowledgeItem.h"

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

