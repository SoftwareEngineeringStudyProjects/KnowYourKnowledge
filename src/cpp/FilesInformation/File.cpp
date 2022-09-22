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


File::File(std::string filepath, std::string filename, std::string extension) : _filepath(std::move(filepath)),
                                                                                _extension(std::move(extension)),
                                                                                _filename(std::move(filename)) {

}

std::string File::filepath() const {
    return _filepath;
}

bool File::exists() {
    std::fstream file(_filepath.c_str());
    return file.good();
}
