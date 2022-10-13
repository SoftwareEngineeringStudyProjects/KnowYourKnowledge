#include "CommandLineProcessor.h"
#include "CommandLineProcessorConstants.h"
#include "Config.h"
#include "FileBuilder.h"
#include "TextNote.h"
#include "TextNoteCollection.h"
#include <iostream>
#include <cstring>

#include "doctest.h"



void CommandLineProcessor::run(int argc, char **argv) {
  if (strcmp(argv[1], SET_PARAMETER_NAME) == 0)   {
    if (argc != 4) {
      std::cerr<<"set command requires two additional parameters: set <key> <value>"<<std::endl;
      return;
    }
    setConfigParameter(argv[2], argv[3]);
    return;
  }
  if (strcmp(argv[1], ADD_COLLECTION_NAME) == 0)   {
    if (argc != 4) {
      std::cerr<<ADD_COLLECTION_NAME<<" command requires two additional parameters: "
          << ADD_COLLECTION_NAME<<" <title> <dirpath>"<<std::endl;
      return;
    }
    addCollection(argv[2], argv[3]);
    return;
  }
  for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], ADD_NOTE_NAME) == 0) {
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

    // Loading current collection name from config
    Config config;
    config.read_from_file(CONFIG_FILE_PATH_NAME);

    // CONFIG MUST RETURN FILE PATH NOT NAME
    std::string currentCollectionPath = config.get(COLLECTION_KEY);

    // Saving the text note to current collection
    TextNoteCollection currentCollection = FileBuilder::collectionFromFile(currentCollectionPath);
    currentCollection.add(newTextNote);

    // Saving current collection back to file
    FileBuilder::toFile(&currentCollection, currentCollectionPath);
}

void CommandLineProcessor::addCollection(const std::string &title,
    const std::string &path) {
  TextNoteCollection newCollection {title};
  FileBuilder::toFile(&newCollection,path);
  std::cout<<"created collection with title="<<title<<" in directory="<<path<<std::endl;
}

void CommandLineProcessor::setConfigParameter(const std::string &key,
    const std::string &value) {

  Config config;
  config.read_from_file(CONFIG_FILE_PATH_NAME);
  config.set(key, value);
  config.write_to_file(CONFIG_FILE_PATH_NAME);
  std::cout<<"Set config parameter key="<<key<<", value="<<value<<std::endl;
}

//TEST_CASE("imitate CLI call - add note") {
//  char* simulatedArgv[3] = {"ky", "add", "note"};
//  CommandLineProcessor::run(3, simulatedArgv);
//}

