#include "CommandLineProcessor.h"
#include "CommandLineProcessorConstants.h"
#include "Config.h"
#include "FileBuilder.h"
#include "TextNote.h"
#include "TextNoteCollection.h"

#include <sstream>
#include <utility> //std::pair
#include <vector>
#include <stdexcept>

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

std::vector<std::string> readLinesFromFile(const std::string& filename) {
    std::vector<std::string> lines;
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + filename);
        return lines;
    }
    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    file.close();
    return lines;
}

TEST_CASE("reading file throws exception for non-existant file") {
  CHECK_THROWS_WITH_AS(readLinesFromFile("none.none"),  "Cannot open file: none.none", std::runtime_error);
}

template<typename T>
bool is_prefix_vector(const std::vector<T>& vector1, const std::vector<T>& vector2) {
  if (vector1.size() > vector2.size() ) {
    std::cout << "prefix size = "<< vector1.size() << " greater than other size = " << vector2.size() << std::endl;
    return false; // size of prefix can't be greater
  }
  for(std::size_t i = 0; i < vector1.size(); i++) {
    T item1 = vector1[i];
    T item2 = vector2[i];
    if (item1 != item2) {
      std::cout<< "first difference at index " << i <<", prefix item = " << item1 << ", other item = " << item2 << std::endl;
      return false; // items don't match
    }
  }
  return true;
}

TEST_CASE("comparing vector prefix") {
  std::vector<int> vec1 {1,2,3,4,5};
  std::vector<int> vec2 {1,2,3,4};
  std::vector<int> vec3 {1,2,3,4,7};

  CHECK(is_prefix_vector(vec2, vec1));
  CHECK(is_prefix_vector(vec2, vec3));
  CHECK(! is_prefix_vector(vec1, vec3));
  CHECK(! is_prefix_vector(vec1, vec2));
}

TEST_CASE("imitate CLI call - add note") {
  auto path_and_dir = get_current_collection_path_and_dir();
  std::string collectionFilePath = path_and_dir.first;

  std::vector<std::string> linesBefore = readLinesFromFile(collectionFilePath);

  char* simulatedArgv[3] = {"ky", "add", "note"};
  std::string expected_text = "note body from std::stringstream\nused in test\nshould be added as note\n";
  std::stringstream instream {expected_text + "\n"};
  CommandLineProcessor::run(3, simulatedArgv, instream); // requires user input

  std::vector<std::string> linesAfter = readLinesFromFile(collectionFilePath);

  TextNoteCollection currentCollection = FileBuilder::collectionFromFile(collectionFilePath);
  TextNote lastNote = currentCollection.get(currentCollection.size()-1);
  CHECK(lastNote.title() == "note");
  CHECK(lastNote.text() == expected_text);

  CHECK(is_prefix_vector(linesBefore, linesAfter)); // can add new lines, but can't change existing lines




}

