/*
 * storage.h
 *
 *  Created on: Sep 30, 2022
 *      Author: KZ
 */

#ifndef STORAGE_H_
#define STORAGE_H_


#include "storage_base.h"
#include "KnowledgeItem.h"

#include <string>

//TODO: do we need a single storage class, or separate classes for save and load?
// single class means we should initialize fields with meaningless values
//template<typename OutStreamT, typename InStreamT, typename ResultT = std::string>
//class StreamStorage {
//public:
//	StreamStorage() {};
//	StreamStorage(const ResultT& data):outstream{}, instream{data} {}
//	void save(KnowledgeItemPtr item);
//	KnowledgeItemPtr load();
//private:
//	OutStreamT outstream;
//	InStreamT instream;
//};

template<typename OutStreamT, typename ResultT = std::string>
class StreamStorageSaver: public BaseStorageSaver {
public:
  StreamStorageSaver(): real_stream { new OutStreamT }, outstream { *real_stream }, indentLevel{0} {}
  StreamStorageSaver(OutStreamT &out): real_stream { nullptr }, outstream { out }, indentLevel{0} {}
  ~StreamStorageSaver() {
    if (real_stream) { delete real_stream; }
  }

  OutStreamT& underlying_stream() {
    return outstream;
  }

  void save(KnowledgeItemPtr item) override;

  void save_title(const std::string &title) override;
  void save_creation_time(Timestamp time) override;
  void save_multiline(const std::string &text) override;
  void save_child(KnowledgeItemPtr child) override;
  void begin_children() override;
  void end_children() override;

private:
  OutStreamT* real_stream;
  OutStreamT& outstream;
  int indentLevel;
  void addIndent();


};

template<typename OutStreamT, typename ResultT>
inline void StreamStorageSaver<OutStreamT, ResultT>::save(KnowledgeItemPtr item) {
  item->save_to(*this);
}

template<typename OutStreamT, typename ResultT>
inline void StreamStorageSaver<OutStreamT, ResultT>::save_title(const std::string &title) {
  addIndent();
  outstream << title << std::endl;
}

template<typename OutStreamT, typename ResultT>
inline void StreamStorageSaver<OutStreamT, ResultT>::save_creation_time(Timestamp time) {
  addIndent();
  outstream << time_to_string(time) << std::endl;
}

template<typename OutStreamT, typename ResultT>
inline void StreamStorageSaver<OutStreamT, ResultT>::save_multiline(const std::string &text) {
  if (text.size()==0) {return;}
  addIndent();
  outstream << text;
  //TODO: add indents inside text? replace \n with indent?
}

template<typename OutStreamT, typename ResultT>
inline void StreamStorageSaver<OutStreamT, ResultT>::save_child(
    KnowledgeItemPtr child) {
  child->save_to(*this);
  addIndent();
  outstream<<"\n";
}

template<typename OutStreamT, typename ResultT>
inline void StreamStorageSaver<OutStreamT, ResultT>::begin_children() {
  addIndent();
  outstream<<"{\n";
  indentLevel++;
}

template<typename OutStreamT, typename ResultT>
inline void StreamStorageSaver<OutStreamT, ResultT>::end_children() {
  indentLevel--;
  addIndent();
  outstream<<"}\n";
}

template<typename OutStreamT, typename ResultT>
inline void StreamStorageSaver<OutStreamT, ResultT>::addIndent() {
  // outstream<<indentLevel; //for debug purposes
  for(int i = 0; i<indentLevel; i++) {
    outstream<<"  ";
  }
}

#endif /* STORAGE_H_ */
