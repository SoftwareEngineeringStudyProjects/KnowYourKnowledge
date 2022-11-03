/*
 * KnowledgeItem.h
 *
 *  Created on: Sep 22, 2022
 *      Author: KZ
 */

#ifndef KNOWLEDGEITEM_H_
#define KNOWLEDGEITEM_H_

#include "storage_base.h"
#include "SearchCriteria.h"
#include "MatchResult.h"

#include <ostream>
#include <string>
#include <ctime>

class BaseStorageSaver;

class KnowledgeItem {
public:
    KnowledgeItem(std::string title);
    KnowledgeItem(std::string title, std::time_t creation_time);
    virtual ~KnowledgeItem() = 0;
    std::string title() const;
    std::string creation_time_string() const;
    std::time_t creation_time() const;

    virtual std::ostream& output(std::ostream& out);

    virtual void save_to(BaseStorageSaver& storage);

    virtual double match(SearchCriteria<std::string, std::time_t> *criteria);
protected:
	std::string _title;
	std::time_t _creation_time;

    virtual MatchResult _match(SearchCriteria<std::string, std::time_t> *criteria);
};

//typedef KnowledgeItem* KnowledgeItemPtr;
using KnowledgeItemPtr = KnowledgeItem*;



#endif /* KNOWLEDGEITEM_H_ */