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

	TextNote note2("test1", "Listen to");
	TextNote note3("test2", " the wind\n\n");
	TextNote note4("test3", "of changes");

	TextNoteCollection collection("test");
	collection.add(note)->add(note2)->add(note3)->add(note4);
	FileBuilder::toFile(&collection);


	TextNoteCollection collection2 = FileBuilder::collectionFromFile("test");
	collection2.print();
	return 0;
}

