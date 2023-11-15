#include "FileBuilder.h"

#include "time_helper.h"

#include "doctest.h"

#include <cassert>


 void FileBuilder::toFile(TextNote* note, std::string path) {
	 std::ofstream file = createFile(note->title(), path);

	 writeNote(file, note);
	 file.close();

}
 std::ofstream FileBuilder::createFile(std::string name, std::string path) {
	 std::ofstream file;
	 file.open(getFileName(name, path));
	 assert (!file.fail());
	 return file;
 }

 void FileBuilder::writeNote(std::ofstream& file, TextNote* note) {
	 writeCreationTime(file, note->_creation_time);
	 writeTitle(file, note->title());
	 writeText(file, note);
 }


 std::string FileBuilder::getFileName(std::string name, std::string path) {
	 return path + name + "." + TEXT_FILE_EXTENSION;
 }


 void FileBuilder::writeTitle(std::ofstream& file, std::string title) {
	 file << title << "\n";
 }
 void FileBuilder::writeCreationTime(std::ofstream& file, std::time_t creation_time) {
 	 file << time_to_string(creation_time) << "\n";
 }
 void FileBuilder::writeText(std::ofstream& file, TextNote* note) {
	 std::string line;
	 std::stringstream s;

	 s << note->text();

	 while (std::getline(s, line)) {

		 addEmptyLineCharIfEmpty(line);
		 file << line << "\n";
	 }

	 file << "\n";
 }
void FileBuilder::addEmptyLineCharIfEmpty(std::string& line) {
	 int i = 0;
	 while(line[i] == EMPTY_LINE_CHAR) {
		i++;
	 }
	 if (line[i] == '\0') {
		 line += EMPTY_LINE_CHAR;
	 }
}
TextNote FileBuilder::fromFile(std::string filename){
	 std::ifstream file = openFile(filename);
	 TextNote note = initTextNote(file);
	 file.close();
	 return note;
 }

std::ifstream FileBuilder::openFile(std::string filename) {
	std::ifstream file;
	//file.open(getFileName(filename)); // FIXME: only one parameter, requires two?
	file.open(filename);
	assert (!file.fail());
	return file;
}

TextNote FileBuilder::initTextNote(std::ifstream& file) {
	std::time_t creationTime = readCreationTime(file);
	std::string title = readTitle(file);
	std::string text = readText(file);

	return TextNote(title, text, creationTime);
}
std::string FileBuilder::readTitle(std::ifstream& file) {
	std::string title;
	std::getline(file, title);
	return title;
}
std::time_t FileBuilder::readCreationTime(std::ifstream& file) {
	std::string line;

	std::getline(file, line);
	std::time_t time = time_from_string(line);
	assert (time != -1);
	return time;
}

std::string FileBuilder::readText(std::ifstream& file) {
	std::string line;
	std::string noteText;

	while (std::getline(file, line)) {
		if (line.empty()) {
			break;
		}
		removeEmptyLineCharIfExtra(line);
		noteText += line;
		noteText += "\n";
	}
	return noteText;
}
void FileBuilder::removeEmptyLineCharIfExtra(std::string& line) {
	int i = 0;
	while (line[i] == EMPTY_LINE_CHAR) {
		i++;
	}
	if (line[i] == '\0') {
		line.pop_back();
	}
}

void FileBuilder::toFile(TextNoteCollection* collection, std::string path) {
	std::ofstream file = createFile(collection->title(), path);
	writeCreationTime(file, collection->creation_time());
	writeTitle(file, collection->title());
	writeCollectionNotes(file, collection);
}

void FileBuilder::writeCollectionNotes(std::ofstream& file, TextNoteCollection* collection) {
	for (std::size_t i = 0; i < collection->size(); i++) {
		TextNote note = collection->get(i);
		writeNote(file, &note);
	}
}
TextNoteCollection FileBuilder::collectionFromFile(std::string filename) {
	std::ifstream file = openFile(filename);

	std::time_t creationTime = readCreationTime(file);
	std::string title = readTitle(file);
	TextNoteCollection collection = TextNoteCollection(title, creationTime);
	readCollectionNotes(file, collection);
	return collection;
}

void FileBuilder::readCollectionNotes(std::ifstream& file, TextNoteCollection& collection) {
	while (file.peek() != EOF) {
		collection.add(initTextNote(file));
	}
}

TEST_CASE("save and load collection") {
  TextNote note("hello");

  TextNote note2("test1", "``Message``");
  TextNote note3("test2", "```");
  TextNote note4("test3", "Message\n\nwith newlines\n");

  TextNoteCollection collection("test");
  collection.add(note)->add(note2)->add(note3)->add(note4);

  Timestamp current = current_time();

  FileBuilder::toFile(&collection);


  TextNoteCollection collection2 = FileBuilder::collectionFromFile(FileBuilder::getFileName("test"));

  CHECK(collection2.title() == "test");
  CHECK(collection2.creation_time() == current);
  CHECK(collection2.size() == 4);
  TextNote child_note = collection2.get(0);
  CHECK(child_note.title() == "hello");
  CHECK(child_note.text() == "");
  CHECK(child_note.creation_time() == current);

  child_note = collection2.get(1);
  CHECK(child_note.title() == "test1");
  //CHECK(child_note.text() == "``Message``");
  CHECK(child_note.creation_time() == current);

  child_note = collection2.get(3);
  CHECK(child_note.title() == "test3");
  CHECK(child_note.text() == "Message\n\nwith newlines\n");
  CHECK(child_note.creation_time() == current);


}


