/*
 * main.cpp
 *
 *  Created on: Sep 8, 2022
 *      Author: KZ
 */

#include "Config.h"
#include "TextNote.h"

#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

#include <iostream>

int main(int argc, char** argv) {

    doctest::Context context;

    context.applyCommandLine(argc, argv);

    int res = context.run(); // run

    if(context.shouldExit()) {// important - query flags (and --exit) rely on the user doing this
        return res;          // propagate the result of the tests
    }

    int client_stuff_return_code = 0;
    // your program - if the testing framework is integrated in your production code





	std::cout<<"123"<<std::endl;
	TextNote note("hello");
	std::cout<<"title="<<note.title()<<", text="<<note.text()<<",created="<<note.creation_time_string()<<std::endl;

	// TextNote wrong(""); // FAILS: assertion failure (empty title)

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





	return res + client_stuff_return_code; // the result from doctest is propagated here as well
}

