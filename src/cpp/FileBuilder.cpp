#include "FileBuilder.h"
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
	 writeCreationTime(file, note->creation_time());
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
 	 file << toDateFormat(creation_time) << "\n";
 }
 void FileBuilder::writeText(std::ofstream& file, TextNote* note) {
	 file << note->text() << END_CHAR << "\n";
 }

TextNote FileBuilder::fromFile(std::string filename){
	 std::ifstream file = openFile(filename);
	 TextNote note = initTextNote(file);
	 file.close();
	 return note;
 }

std::ifstream FileBuilder::openFile(std::string filename) {
	std::ifstream file;
	file.open(getFileName(filename));
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
	std::time_t time = fromDateFormat(line);
	assert (time != -1);
	return time;
}

std::string FileBuilder::readText(std::ifstream& file) {
	std::string line;
	std::string noteText;

	while (std::getline(file, line)) {
		noteText += line;
		if (containsEndChar(line)) {
			noteText.pop_back();
			break;
		}
		noteText += "\n";
	}
	return noteText;
}

bool FileBuilder::containsEndChar(std::string line){
	return line.find(END_CHAR) != std::string::npos;
}

std::string FileBuilder::toDateFormat(std::time_t time) {
	const unsigned int maxChar = 20;
	char date[maxChar];
	std::strftime(date, sizeof(date), "%Y.%m.%d %H:%M:%S", std::localtime(&time));
	return std::string(date);
}

std::time_t FileBuilder::fromDateFormat(std::string str) {
	struct std::tm tm;
	std::sscanf(str.c_str(), "%d.%d.%d %d:%d:%d", &tm.tm_year,
			&tm.tm_mon, &tm.tm_mday, &tm.tm_hour, &tm.tm_min, &tm.tm_sec);

	tm.tm_year -= 1900; //1900 -> 0, 2022 -> 122
	tm.tm_mon -= 1; //January = 0
	return std::mktime(&tm);
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

