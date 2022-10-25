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
	Directory(const std::string& title, std::time_t creationTime);
	virtual ~Directory();

	Directory& add(KnowledgeItemPtr item);
	std::ostream& output(std::ostream &out) override;
  void save_to(BaseStorageSaver &storage) override;

    size_t size() const;

    KnowledgeItemPtr const& operator[](size_t index) const;

    std::vector<KnowledgeItemPtr> items() const;


private:
	std::vector<KnowledgeItemPtr> items_;
};

#endif /* DIRECTORY_H_ */
