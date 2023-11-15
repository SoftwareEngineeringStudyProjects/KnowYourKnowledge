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

  CHECK(outstream.str() ==
      "Collection:\n"
      "title=test,created="+time_to_string_detailed(current)+"\n" // two newlines here - separates collection from item
      "title=hello, text=,created="+time_to_string_detailed(current)+
      "title=test1, text=``Message``,created="+time_to_string_detailed(current)+
      "title=test2, text=```,created="+time_to_string_detailed(current)+
      "title=test3, text=Message\n\nwith newlines\n,created="+time_to_string_detailed(current)
      );
}
