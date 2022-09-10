/*
 * main.cpp
 *
 *  Created on: Sep 8, 2022
 *      Author: KZ
 */

#include "TextNote.h"
#include "FileBuilder.h"
#include <iostream>

int main() {
	std::cout<<"123"<<std::endl;
	TextNote note("hello");
	note.print();

	// TextNote wrong(""); // FAILS: assertion failure (empty title)

	TextNote note2("test", "some \n\n\tmessage\n\n");
	FileBuilder::toFile(note2);

	std::string path = FileBuilder::getFileName(note2.title());
	TextNote note3 = FileBuilder::fromFile(path);
	note3.print();
	return 0;
}

