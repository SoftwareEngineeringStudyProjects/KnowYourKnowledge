/*
 * StreamStorageLoader.h
 *
 *  Created on: Oct 21, 2022
 *      Author: KZ
 */

#ifndef STREAMSTORAGELOADER_H_
#define STREAMSTORAGELOADER_H_

#include "KnowledgeItem.h"
#include "TextNote.h"
#include "Directory.h"
#include "time_helper.h"

#include <string>


template<typename InStreamT>
class StreamStorageLoader {
public:
  StreamStorageLoader(InStreamT& instream): instream_{instream}  {}

  KnowledgeItemPtr load();
private:
  InStreamT& instream_;
};

namespace string_helper {

// code from https://stackoverflow.com/a/25385766
const char* ws = " \t\n\r\f\v";

// trim from end of string (right)
inline std::string& rtrim(std::string &s, const char *t = ws) {
  s.erase(s.find_last_not_of(t) + 1);
  return s;
}

// trim from beginning of string (left)
inline std::string& ltrim(std::string &s, const char *t = ws) {
  s.erase(0, s.find_first_not_of(t));
  return s;
}

// trim from both ends of string (right then left)
inline std::string& trim(std::string &s, const char *t = ws) {
  return ltrim(rtrim(s, t), t);
}

}

template<typename InStreamT>
inline KnowledgeItemPtr StreamStorageLoader<
    InStreamT>::load() {
  KnowledgeItemPtr result = nullptr;
  std::string line;
  instream_.getline(line);
  Timestamp creationTime = time_from_string(line);
  std::string title;
  instream_.getline(title);
  std::string text = "";

  while(true) {
    instream_.getline(line);
    string_helper::trim(line);
    if (line.empty()) { // next item?
      if (!result) { // no text - default to TextNote
        result = new TextNote(title, text, creationTime);
      }
      return result;
    } else if (line == "{") { // start collection
//      Directory dir = new Directory(title, creationTime); //TODO: add this constructor in Directory
//      result = dir;
//      KnowledgeItemPtr child = load();
//      dir->add(child);

    } else if (line == "}") { // end collection
      // return dir? or return nullptr to signal end of current collection
    } else { // part of text
      text+=line+"\n";
    }
  }

}

#endif /* STREAMSTORAGELOADER_H_ */
