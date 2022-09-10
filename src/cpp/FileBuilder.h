/*
 * FileBuilder.h
 *
 *  Created on:  9 Sep. 2022 р.
 *      Author: MouseCreateor
 */

#ifndef FILEBUILDER_H_
#define FILEBUILDER_H_

#include <fstream>

#include "TextNote.h"
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
	static std::string getFileName(TextNote note, std::string path = "");
	static TextNote fromFile(std::string filename);
private:
	static constexpr const char* TEXT_FILE_EXTENSION = "txt";

	static std::ofstream createFile(TextNote note, std::string path);
	static void writeFile(std::ofstream& file, TextNote note);
	static void writeTitle(std::ofstream& file, TextNote note);
	static void writeCreationTime(std::ofstream& file, TextNote note);
	static void writeText(std::ofstream& file, TextNote note);

	static std::ifstream openFile(std::string path);
	static TextNote initTextNote(std::ifstream& file);
	static std::string readTitle(std::ifstream& file);
	static std::time_t readCreationTime(std::ifstream& file);
	static std::string readText(std::ifstream& file);





};



#endif /* SRC_CPP_FILEBUILDER_H_ */
