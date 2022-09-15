/*
 * main.cpp
 *
 *  Created on: Sep 8, 2022
 *      Author: KZ
 */

#include "Config.h"
#include "TextNote.h"

#include <iostream>

int main() {
	std::cout<<"123"<<std::endl;
	TextNote note("hello");
	std::cout<<"title="<<note.title()<<", text="<<note.text()<<",created="<<note.creation_time_string()<<std::endl;

	Config config;
	config.set("current_collection", "MyNotes");
	std::cout<<config.get("current_collection")<<std::endl;

	config.set("current_collection", "Another with space");
	std::cout<<config.get("current_collection")<<std::endl;
	config.set("something","anything");
	std::cout<<config.get("something")<<std::endl;

	config.write_to_file("config.txt");

	Config config2;
	config2.read_from_file("config.txt");
	std::cout<<config2.get("current_collection")<<std::endl;
	std::cout<<config2.get("something")<<std::endl;

	// TextNote wrong(""); // FAILS: assertion failure (empty title)

	/*
	 *
int main () {
  ofstream myfile;
  myfile.open ("ourfile.txt");
  if ( myfile.is_open() ) {
myfile >> mystring;
cout << mystring;
  myfile.close();
  return 0;
}
	 *
	 */

	return 0;
}

