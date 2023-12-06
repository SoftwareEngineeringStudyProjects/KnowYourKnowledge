/*
 * TextNoteCollection.cpp
 *
 *  Created on: 10 Sep 2022
 *      Author: MouseCreator
 */

#include "TextNoteCollection.h"
#include "doctest.h"
#include <sstream>
#include <cassert>
TextNoteCollection::TextNoteCollection(std::string title, std::time_t creation_time):
        _title(title), _creation_time(creation_time){}
TextNoteCollection::TextNoteCollection(std::string title):
        _title(title) { _creation_time = std::time(nullptr); }
TextNoteCollection::~TextNoteCollection() {

}


std::string TextNoteCollection::title() const{
    return _title;
}
std::time_t TextNoteCollection::creation_time() const{
    return _creation_time;
}
std::size_t TextNoteCollection::size() const {
    return notes.size();
}

TextNoteCollection* TextNoteCollection::add(TextNote note)  {
    notes.emplace_back(note);
    return this;
}
void TextNoteCollection::remove(std::size_t num) {
    assert(num < notes.size());
    notes.erase(notes.begin() + num);
}
TextNote TextNoteCollection::get(std::size_t num) const{
    return notes[num];
}
std::string TextNoteCollection::creation_time_string() const{
    return std::asctime(std::localtime(&_creation_time));
}
void TextNoteCollection::print(std::ostream& out) const{
    out << "Collection:\n"<<"title="<<title()<<",created="<<creation_time_string()<<"\n";
    for (std::size_t i = 0; i < notes.size();i++) {
        notes[i].print(out);
    }
}

bool compare_strings_notify_diff(const std::string& first, const std::string& second,
    std::ostream& out = std::cout) {
  if (first == second) {return true;}
  std::stringstream sin1{first};
  std::stringstream sin2{second};
  std::string line1;
  std::string line2;
  int line_count = 0;
  while (std::getline(sin1, line1)) {
      if (!std::getline(sin2, line2)) {
        out<<"second has fewer lines, line_count="<<line_count<<", first line=`"<<line1<<"`"<<std::endl;
        break;
      }
      if (line1 == line2) {
        //out<<line_count<<":"<<line1<<std::endl;
        line_count++;
        continue;
      } else {
        out<<"different lines on line_count="<<line_count<<", line1=`"<<line1<<"`, line2=`"<<line2<<"`"<<std::endl;
        line_count++;
      }

  }


  return false;
}

TEST_CASE("printing collection") {
  TextNote note("hello");

  TextNote note2("test1", "``Message``");
  TextNote note3("test2", "```");
  TextNote note4("test3", "Message\n\nwith newlines\n");

  TextNoteCollection collection("test");
  collection.add(note)->add(note2)->add(note3)->add(note4);
  std::stringstream outstream;
  collection.print(outstream);
  Timestamp current = current_time();

  CHECK(compare_strings_notify_diff(outstream.str(),
      "Collection:\n"
      "title=test,created="+time_to_string_detailed(current)+"\n" // two newlines here - separates collection from item
      "title=hello, text=,created="+time_to_string_detailed(current)+
      "title=test1, text=``Message``\n,created="+time_to_string_detailed(current)+
      "title=test2, text=```\n,created="+time_to_string_detailed(current)+
      "title=test3, text=Message\n\nwith newlines\n,created="+time_to_string_detailed(current)
      ));
}
