/*
 * Directory.h
 *
 *  Created on: Sep 27, 2022
 *      Author: KZ
 */

#ifndef DIRECTORY_H_
#define DIRECTORY_H_

#include "KnowledgeItem.h"

#include <vector>

class Directory: public KnowledgeItem {
public:
	Directory(const std::string& title);
	virtual ~Directory();

	Directory& add(KnowledgeItem* item);

private:
	std::vector<KnowledgeItem*> items_;
};

#endif /* DIRECTORY_H_ */
