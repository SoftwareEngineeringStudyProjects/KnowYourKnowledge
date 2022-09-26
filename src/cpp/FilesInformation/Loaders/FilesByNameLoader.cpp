//
// Created by Dmytro Klishch on 9/22/22.
//

#include <vector>
#include "FilesByNameLoader.h"


File FilesByNameLoader::loadFile(const std::string &filepath) {
    std::string filename = getFileName(filepath);
    size_t point = filename.find_first_of('.');
    if (point == -1) return File(filepath, filename, "", isTextFile(filepath));
    return File(filepath, filename.substr(0, point), filename.substr(point + 1), isTextFile(filepath));
}

std::string FilesByNameLoader::getFileName(const std::string &filepath) {
    size_t slash = filepath.find_last_of(_separator);
    if (slash == -1) return {filepath};
    return filepath.substr(slash + 1);
}

FilesByNameLoader::FilesByNameLoader(const std::string &separator) : _separator(separator) {}

char* loadBuffer(std::fstream &file, int maximalSize = 4000) {
    file.seekg(0, file.end);
    int size = std::min(maximalSize, (int) file.tellg());
    char *buffer = new char[size];
    file.seekg(0, file.beg);
    file.read(buffer, size);
    return buffer;
}

bool FilesByNameLoader::isTextFile(const std::string &filepath) {
    std::fstream file(filepath, std::ios_base::binary | std::ios_base::in);
    if (!file.is_open()) return false;

    char* buffer = loadBuffer(file);

    AutoIt::Common::TextEncodingDetect::Encoding encoding = AutoIt::Common::TextEncodingDetect().DetectEncoding(buffer, size);
    return encoding != AutoIt::Common::TextEncodingDetect::None;
}

TEST_CASE("Full file path") {
    FilesByNameLoader loader = FilesByNameLoader();
    File file = loader.loadFile("C:/a/b/c/file.txt");
    CHECK(file.filename() == "file");
    CHECK(file.extension() == "txt");
}

TEST_CASE("Full file path with Windows separator") {
    FilesByNameLoader loader = FilesByNameLoader("\\");
    File file = loader.loadFile("C:\\a\\b\\c\\file.txt");
    CHECK(file.filename() == "file");
    CHECK(file.extension() == "txt");
}

TEST_CASE("Just file name") {
    FilesByNameLoader loader = FilesByNameLoader();
    File file = loader.loadFile("file.txt");
    CHECK(file.filename() == "file");
    CHECK(file.extension() == "txt");
}

TEST_CASE("Extension with several dots") {
    FilesByNameLoader loader = FilesByNameLoader();
    File file = loader.loadFile("C:/sd/fd/f/file.txt.txt");
    CHECK(file.filename() == "file");
    CHECK(file.extension() == "txt.txt");
}

TEST_CASE("Extension with several dots with Windows separator") {
    FilesByNameLoader loader = FilesByNameLoader("\\");
    File file = loader.loadFile("C:\\sd\\fd\\f\\file.txt.txt");
    CHECK(file.filename() == "file");
    CHECK(file.extension() == "txt.txt");
}

TEST_CASE("Existing file") {
    FilesByNameLoader loader = FilesByNameLoader();
    File file = loader.loadFile("resources/text.txt");
    CHECK(file.exists());
}

TEST_CASE("Existing text file is text check") {
    FilesByNameLoader loader = FilesByNameLoader();
    File file = loader.loadFile("resources/text.txt");
    CHECK(file.is_text_file());
}

TEST_CASE("Existing binary file is text check") {
    FilesByNameLoader loader = FilesByNameLoader();
    File file = loader.loadFile("resources/binary.bin");
    CHECK(!file.is_text_file());
}

TEST_CASE("Non Existing file") {
    FilesByNameLoader loader = FilesByNameLoader();
    File file = loader.loadFile("resources/text.txt.txt.txt");
    CHECK(!file.exists());
}