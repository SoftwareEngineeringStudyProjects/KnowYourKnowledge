/*
 * main.cpp
 *
 *  Created on: Sep 8, 2022
 *      Author: KZ
 */

#include "TextNote.h"

#include <iostream>

int main() {
	std::cout<<"123"<<std::endl;
	TextNote note("hello");
	std::cout<<"title="<<note.title()<<", text="<<note.text()<<",created="<<note.creation_time_string()<<std::endl;

	return 0;
}

