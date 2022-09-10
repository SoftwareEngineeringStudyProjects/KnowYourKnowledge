/*
 * FileBuilder.h
 *
 *  Created on:  9 Sep. 2022
 *      Author: MouseCreateor
 */

#ifndef FILEBUILDER_H_
#define FILEBUILDER_H_

#include <fstream>

#include "TextNote.h"
#include "TextNoteCollection.h"
#include <ctime>

/*
 * File format is the following:
 * line 0: title
 * line 1: creation time (as time_t)
 * the rest is the text message of the note
 */

class FileBuilder {
public:
	static bool toFile(TextNote note, std::string path = "");
	static TextNote fromFile(std::string filename);
	static bool collectionToFile(TextNoteCollection collection, std::string path = "");

	static std::string toDateFormat(std::time_t time);
	static std::time_t fromDateFormat(std::string str);
	static std::string getFileName(std::string name, std::string path = "");
private:
	static constexpr const char* TEXT_FILE_EXTENSION = "txt";

	static std::ofstream createFile(std::string name, std::string path);

	static void writeNote(std::ofstream& file, TextNote note);
	static void writeTitle(std::ofstream& file, std::string title);
	static void writeCreationTime(std::ofstream& file, std::time_t creation_time);
	static void writeText(std::ofstream& file, TextNote note);

	static std::ifstream openFile(std::string path);
	static TextNote initTextNote(std::ifstream& file);
	static std::string readTitle(std::ifstream& file);
	static std::time_t readCreationTime(std::ifstream& file);
	static std::string readText(std::ifstream& file);
	static int countBrackets(std::string str);
	static void writeCollectionNotes(std::ofstream& file, TextNoteCollection collection);





};



#endif /* SRC_CPP_FILEBUILDER_H_ */
