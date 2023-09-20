#include "CommandLineProcessor.h"
#include "CommandLineProcessorConstants.h"
#include "Config.h"
#include "FileBuilder.h"
#include "TextNote.h"
#include "TextNoteCollection.h"

#include <sstream>
#include <utility> //std::pair

#include <cstring>

#include "doctest.h"



void CommandLineProcessor::run(int argc, char **argv, std::istream& instream) {
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
            addNote(addNoteTitle, instream);
        }
        /*
        else if (argv[i] == SEARCH_NOTE_NAME) {
            // do something
        }
        */
    }
}

std::pair<std::string, std::string> get_current_collection_path_and_dir() {
  // Loading current collection name from config
  Config config;
  config.readFromFile(CONFIG_FILE_PATH_NAME);

  std::string currentCollectionTitle = config.get(COLLECTION_KEY);
  std::string collectionDir = config.get(COLLECTION_DIR_KEY);
  std::string collectionFilePath = FileBuilder::getFileName(currentCollectionTitle,collectionDir);

//    std::cout<<"loading collection from "<<collectionFilePath<<std::endl;
  return {collectionFilePath, collectionDir};
}

void CommandLineProcessor::addNote(const std::string &title, std::istream& instream) {
    // Reading a new text note from command line
    std::string text, line;
    std::cout << "Please, enter the text of a new note:" << std::endl;
    while (getline(instream, line) && !line.empty()) {
        text += line+'\n';
    }
    TextNote newTextNote(title, text);

    auto path_and_dir = get_current_collection_path_and_dir();
    std::string collectionFilePath = path_and_dir.first;
    std::string collectionDir = path_and_dir.second;

    // Saving the text note to current collection
    TextNoteCollection currentCollection = FileBuilder::collectionFromFile(collectionFilePath);
    currentCollection.add(newTextNote);

    // Saving current collection back to file
//    std::cout<<"saving collection with title "<<currentCollection.title()
//        <<" to directory "<<collectionDir<<std::endl;
    FileBuilder::toFile(&currentCollection, collectionDir);
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
  config.readFromFile(CONFIG_FILE_PATH_NAME);
  config.set(key, value);
  config.writeToFile(CONFIG_FILE_PATH_NAME);
  std::cout<<"Set config parameter key="<<key<<", value="<<value<<std::endl;
}

TEST_CASE("imitate CLI call - add note") {
  char* simulatedArgv[3] = {"ky", "add", "note"};
  std::string expected_text = "note body from std::stringstream\nused in test\nshould be added as note\n";
  std::stringstream instream {expected_text + "\n"};
  CommandLineProcessor::run(3, simulatedArgv, instream); // requires user input

  auto path_and_dir = get_current_collection_path_and_dir();
  std::string collectionFilePath = path_and_dir.first;
  TextNoteCollection currentCollection = FileBuilder::collectionFromFile(collectionFilePath);
  TextNote lastNote = currentCollection.get(currentCollection.size()-1);
  CHECK(lastNote.title() == "note");
  CHECK(lastNote.text() == expected_text);



}

