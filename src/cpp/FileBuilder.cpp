#include "FileBuilder.h"
#include <cassert>
 bool FileBuilder::toFile(TextNote note, std::string path) {
	 std::ofstream file = createFile(note, path);
	 if (file.fail())
		 return true;

	 writeFile(file, note);
	 file.close();

	 return false;

}

 void FileBuilder::writeFile(std::ofstream& file, TextNote note) {
	 writeTitle(file, note);
	 writeCreationTime(file, note);
	 writeText(file, note);
 }




 std::ofstream FileBuilder::createFile(TextNote note, std::string path) {
	 std::ofstream file;
	 file.open(getFileName(note, path));
	 return file;
 }
 std::string FileBuilder::getFileName(TextNote note,std::string path) {
	 return note.title() + "." +
			 TEXT_FILE_EXTENSION;
 }


 void FileBuilder::writeTitle(std::ofstream& file, TextNote note) {
	 file << note.title() << "\n";
 }
 void FileBuilder::writeCreationTime(std::ofstream& file, TextNote note) {
 	 file << note.creation_time() << "\n";
 }
 void FileBuilder::writeText(std::ofstream& file, TextNote note) {
	 file << note.text();
 }

TextNote FileBuilder::fromFile(std::string filename){
	 std::ifstream file = openFile(filename);
	 TextNote note = initTextNote(file);
	 file.close();
	 return note;
 }

std::ifstream FileBuilder::openFile(std::string filename) {
	std::ifstream file;
	file.open(filename);
	assert (!file.fail()); //file exists
	return file;
}

TextNote FileBuilder::initTextNote(std::ifstream& file) {
	std::string title = readTitle(file);
	std::time_t creationTime = readCreationTime(file);
	std::string text = readText(file);

	return TextNote(title, text, creationTime);
}
std::string FileBuilder::readTitle(std::ifstream& file) {
	std::string title;
	std::getline(file, title);
	return title;
}
std::time_t FileBuilder::readCreationTime(std::ifstream& file) {
	const int charsInDate = 12;
	std::time_t time;
	char date[charsInDate];

	file.getline(date, charsInDate);
	time = std::atoi(date);
	return time;
}

std::string FileBuilder::readText(std::ifstream& file) {
	std::string line;
	std::string noteText;

	while (std::getline(file, line)) {
		noteText += line;
		if (!file.eof()) {
			noteText += "\n";
		}
	}
	file.clear();
	return noteText;
}
