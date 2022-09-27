/*
 * Directory.cpp
 *
 *  Created on: Sep 27, 2022
 *      Author: KZ
 */

#include "Directory.h"


Directory::Directory(const std::string &title): KnowledgeItem{title} {
}

Directory::~Directory() {
	// TODO Auto-generated destructor stub
}

Directory& Directory::Directory::add(KnowledgeItem *item) {
	items_.push_back(item);
	return *this;
}
