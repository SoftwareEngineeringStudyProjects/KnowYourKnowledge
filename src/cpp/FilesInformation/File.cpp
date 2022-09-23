//
// Created by Dmytro Klishch on 9/22/22.
//

#include "File.h"

#include <utility>
#include <fstream>

std::string File::filename() const {
    return _filename;
}

std::string File::extension() const {
    return _extension;
}


File::File(const std::string &filepath, const std::string & filename, const std::string &extension) : _filepath(filepath),
                                                                                                      _extension(extension),
                                                                                                      _filename(filename) {}

std::string File::filepath() const {
    return _filepath;
}

bool File::exists() const {
    std::fstream file(_filepath.c_str());
    return file.good();
}

bool File::is_text_file() const {
    return _extension == "txt";
}