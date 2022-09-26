/*
 * KnowledgeItem.h
 *
 *  Created on: Sep 22, 2022
 *      Author: KZ
 */

#ifndef KNOWLEDGEITEM_H_
#define KNOWLEDGEITEM_H_

#include <string>
#include <ctime>

class KnowledgeItem {
public:
	KnowledgeItem(std::string title);
	KnowledgeItem(std::string title, std::time_t creation_time);
	virtual ~KnowledgeItem() = 0;
	std::string title() const;
	std::string creation_time_string() const;
	std::time_t creation_time() const;
protected:
	std::string _title;
	std::time_t _creation_time;
};

#endif /* KNOWLEDGEITEM_H_ */
