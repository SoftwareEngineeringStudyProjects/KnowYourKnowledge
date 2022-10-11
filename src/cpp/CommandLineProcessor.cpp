#include "CommandLineProcessor.h"
#include "CommandLineProcessorConstants.h"
#include "FileBuilder.h"
#include "TextNote.h"
#include "TextNoteCollection.h"

#include "doctest.h"

void CommandLineProcessor::run(int argc, char **argv) {
    for (int i = 0; i < argc; i++) {
        if (argv[i] == ADD_NOTE_NAME) {
            std::cout<<"add mode"<<std::endl;
            std::string addNoteTitle(argv[++i]);
            addNote(addNoteTitle);
        }
        /*
        else if (argv[i] == SEARCH_NOTE_NAME) {
            // do something
        }
        */
    }
}

void CommandLineProcessor::addNote(const std::string &title) {
    // Reading a new text note from command line
    std::string text, line;
    std::cout << "Please, enter the text of a new note:" << std::endl;
    while (getline(std::cin, line) && !line.empty()) {
        text += line;
    }
    TextNote newTextNote(title, text);

    // Saving the text note to current collection
    TextNoteCollection currentCollection = FileBuilder::collectionFromFile(READ_FILE_NAME);
    currentCollection.add(newTextNote);

    // Saving current collection back to file
    FileBuilder::toFile(&currentCollection, SAVE_FILE_PATH_NAME);
}

//TEST_CASE("imitate CLI call - add note") {
//  char* simulatedArgv[3] = {"ky", "add", "note"};
//  CommandLineProcessor::run(3, simulatedArgv);
//}

