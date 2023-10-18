//
// Created by Dmytro Klishch on 9/22/22.
//
#include "FilesByNameLoader.h"
#include "../../doctest.h"


File *FilesByNameLoader::loadFile(const std::string &filepath) {
    std::string filename = getFileName(filepath);
    size_t point = filename.find_first_of('.');
    if (point == std::string::npos) return new File(filepath, filename, "", isTextFile(filepath));
    return new File(filepath, filename.substr(0, point), filename.substr(point + 1), isTextFile(filepath));
}

std::string FilesByNameLoader::getFileName(const std::string &filepath) {
    size_t slash = filepath.find_last_of(_separator);
    if (slash == std::string::npos) return {filepath};
    return filepath.substr(slash + 1);
}

FilesByNameLoader::FilesByNameLoader(const std::string &separator) : _separator(separator) {}

char *loadBuffer(std::fstream &file, int size) {
    char *buffer = new char[size];
    file.seekg(0, file.beg);
    file.read(buffer, size);
    return buffer;
}

bool FilesByNameLoader::isTextFile(const std::string &filepath) {
    std::fstream file(filepath, std::ios_base::binary | std::ios_base::in);
    if (!file.is_open()) return false;

    file.seekg(0, file.end);
    int size = std::min(4000, (int) file.tellg());

    char *buffer = loadBuffer(file, size);

    AutoIt::Common::TextEncodingDetect::Encoding encoding = AutoIt::Common::TextEncodingDetect().DetectEncoding(buffer,
                                                                                                                size);
    return encoding != AutoIt::Common::TextEncodingDetect::None;
}

TEST_CASE("Full file path") {
    FilesByNameLoader loader = FilesByNameLoader();
    File *file = loader.loadFile("C:/a/b/c/file.txt");
    CHECK(file->filename() == "file");
    CHECK(file->extension() == "txt");
    //CHECK(file->title() == "file.txt");
    delete file;
}

TEST_CASE("Full file path with Windows separator") {
    FilesByNameLoader loader = FilesByNameLoader("\\");
    File *file = loader.loadFile("C:\\a\\b\\c\\file.txt");
    CHECK(file->filename() == "file");
    CHECK(file->extension() == "txt");
    delete file;
}

TEST_CASE("Just file name") {
    FilesByNameLoader loader = FilesByNameLoader();
    File *file = loader.loadFile("file.txt");
    CHECK(file->filename() == "file");
    CHECK(file->extension() == "txt");
    delete file;
}

TEST_CASE("Extension with several dots") {
    FilesByNameLoader loader = FilesByNameLoader();
    File *file = loader.loadFile("C:/sd/fd/f/file.txt.txt");
    CHECK(file->filename() == "file");
    CHECK(file->extension() == "txt.txt");
    delete file;
}

TEST_CASE("Extension with several dots with Windows separator") {
    FilesByNameLoader loader = FilesByNameLoader("\\");
    File *file = loader.loadFile("C:\\sd\\fd\\f\\file.txt.txt");
    CHECK(file->filename() == "file");
    CHECK(file->extension() == "txt.txt");
    delete file;
}

TEST_CASE("Existing file") {
    FilesByNameLoader loader = FilesByNameLoader();
    File *file = loader.loadFile("./resources/text.txt");
    CHECK(file->exists());
    delete file;
}

TEST_CASE("Existing text file is text check") {
    FilesByNameLoader loader = FilesByNameLoader();
    File *file = loader.loadFile("resources/text.txt");
    CHECK(file->is_text_file());
    delete file;
}

TEST_CASE("Existing binary file is text check") {
    FilesByNameLoader loader = FilesByNameLoader();
    File *file = loader.loadFile("resources/binary.bin");
    CHECK(!file->is_text_file());
    delete file;
}

TEST_CASE("Non Existing file") {
    FilesByNameLoader loader = FilesByNameLoader();
    File *file = loader.loadFile("resources/text.txt.txt.txt");
    CHECK(!file->exists());
    delete file;
}

TEST_CASE("Non Existing directory") {
    FilesByNameLoader loader;
    Directory* directory = loader.loadDirectory("tmp");
    CHECK(directory == nullptr);

    delete directory; // in case test fails
}

TEST_CASE("Empty directory") {
    std::filesystem::create_directory("tmp");

    FilesByNameLoader loader;
    Directory* directory = loader.loadDirectory("tmp");
    CHECK(directory->title() == "tmp");
    CHECK(directory->size() == 0);
    delete directory;

    std::filesystem::remove("tmp");
}

TEST_CASE("Directory with directory") {
    std::filesystem::create_directory("tmp");
    std::filesystem::create_directory("tmp/tmp");

    FilesByNameLoader loader;
    Directory* directory = loader.loadDirectory("tmp");
    CHECK(directory->size() == 1);
    CHECK(dynamic_cast<Directory*>((*directory)[0]) != nullptr);

    delete directory;
    std::filesystem::remove("tmp/tmp");
    std::filesystem::remove("tmp");
}

TEST_CASE("Directory with file") {
    std::filesystem::create_directory("tmp");
    std::fstream file("tmp/tmp.txt", std::ios_base::out);

    FilesByNameLoader loader;
    Directory* directory = loader.loadDirectory("tmp");
    CHECK(directory->size() == 1);
    CHECK(dynamic_cast<File*>((*directory)[0]) != nullptr);

    delete directory;
    file.close();
    std::filesystem::remove("tmp/tmp.txt");
    std::filesystem::remove("tmp");
}

TEST_CASE("Directory with file and directory") {
    std::filesystem::create_directory("tmp");
    std::filesystem::create_directory("tmp/tmp");
    std::fstream file("tmp/tmp.txt", std::ios_base::out);

    FilesByNameLoader loader;
    Directory* directory = loader.loadDirectory("tmp");
    CHECK(directory->size() == 2);

    // order of items is not fixed
    KnowledgeItemPtr directoryChild = (*directory)[0];
    KnowledgeItemPtr fileChild = (*directory)[1];
    //FIXME: title should contain just name, not path
    if (directoryChild->title() == "tmp/tmp") { //directory, then file
        // expected order - same as created
    } else { // file, then directory
      directoryChild = (*directory)[1];
      fileChild = (*directory)[0];
    }
    CHECK(directoryChild->title() == "tmp/tmp");
    //CHECK(fileChild->title() == "tmp/tmp.txt");
    CHECK(dynamic_cast<File*>(fileChild) != nullptr);
    CHECK(dynamic_cast<Directory*>(directoryChild) != nullptr);

    delete directory;
    file.close();
    std::filesystem::remove("tmp/tmp.txt");
    std::filesystem::remove("tmp/tmp");
    std::filesystem::remove("tmp");
}

TEST_CASE("Provided path to file not directory") {
    std::fstream file("tmp.txt", std::ios_base::out);

    FilesByNameLoader loader;
    Directory* directory = loader.loadDirectory("tmp");
    CHECK(directory == nullptr);

    file.close();
    delete directory; // in case test fails
}
