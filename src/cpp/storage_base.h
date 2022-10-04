/*
 * storage_base.h
 *
 *  Created on: Oct 4, 2022
 *      Author: KZ
 */

#ifndef STORAGE_BASE_H_
#define STORAGE_BASE_H_

#include "KnowledgeItem.h"
#include "time_helper.h"

#include <string>

class KnowledgeItem;
using KnowledgeItemPtr = KnowledgeItem*;

class BaseStorageSaver {
public:
	virtual ~BaseStorageSaver() {};
	virtual void save(KnowledgeItemPtr item) = 0;

	virtual void save_title(const std::string& title) = 0;
	virtual void save_creation_time(Timestamp time) = 0;

};



#endif /* STORAGE_BASE_H_ */
