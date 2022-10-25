/*
 * Directory.cpp
 *
 *  Created on: Sep 27, 2022
 *      Author: KZ
 */

#include "Directory.h"

#include "doctest.h"


Directory::Directory(const std::string &title) : KnowledgeItem{title} {
}

Directory::Directory(const std::string &title, std::time_t creationTime)  : KnowledgeItem{title, creationTime}  {
}

Directory::~Directory() {
    // TODO Auto-generated destructor stub
}

Directory &Directory::Directory::add(KnowledgeItem *item) {
    items_.push_back(item);
    return *this;
}

std::ostream &Directory::output(std::ostream &out) {
    KnowledgeItem::output(out);

    for (KnowledgeItem *item: items_) {
        item->output(out);
    }

    return out;
}

void Directory::save_to(BaseStorageSaver &storage) {
  KnowledgeItem::save_to(storage);
  storage.begin_children();
  for (KnowledgeItemPtr item: items_) {
      storage.save_child(item);
  }
  storage.end_children();
}


size_t Directory::size() const {
    return items_.size();
}

KnowledgeItemPtr const&  Directory::operator[](size_t index) const {
    return items_[index];
}



std::vector<KnowledgeItemPtr> Directory::items() const {
    return items_;
}

TEST_CASE("create directory with current time") {
  Directory dir{"dir"};
  CHECK(dir.title() == "dir");
  CHECK(dir.creation_time() == current_time());
}

TEST_CASE("create directory with fixed time") {
  Directory dir{"dir", 12345};
  CHECK(dir.title() == "dir");
  CHECK(dir.creation_time() == 12345);
}

