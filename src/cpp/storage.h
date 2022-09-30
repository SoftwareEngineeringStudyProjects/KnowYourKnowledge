/*
 * storage.h
 *
 *  Created on: Sep 30, 2022
 *      Author: KZ
 */

#ifndef STORAGE_H_
#define STORAGE_H_

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
class StreamStorageSaver {
public:
	StreamStorageSaver() {};
	void save(KnowledgeItemPtr item);
private:
	OutStreamT outstream;

};


#endif /* STORAGE_H_ */
