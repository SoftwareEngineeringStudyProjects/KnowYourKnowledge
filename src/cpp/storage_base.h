/*
 * storage_base.h
 *
 *  Created on: Oct 4, 2022
 *      Author: KZ
 */

#ifndef STORAGE_BASE_H_
#define STORAGE_BASE_H_

#include "KnowledgeItem.h"

class KnowledgeItem;
using KnowledgeItemPtr = KnowledgeItem*;

class BaseStorageSaver {
public:
	virtual ~BaseStorageSaver() {};
	virtual void save(KnowledgeItemPtr item) = 0;
};



#endif /* STORAGE_BASE_H_ */
