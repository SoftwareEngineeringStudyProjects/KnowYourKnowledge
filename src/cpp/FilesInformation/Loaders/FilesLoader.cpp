//
// Created by Dmytro Klishch on 10/4/22.
//

#include "FilesLoader.h"
#include "../../doctest.h"
#include <filesystem>

Directory *FilesLoader::loadDirectory(const std::string &filepath) {
    if (!std::filesystem::exists(filepath)) return nullptr;
    if (!std::filesystem::is_directory(filepath)) return nullptr;

    Directory *directory = new Directory(filepath);
    for (const auto &entry: std::filesystem::directory_iterator(filepath)) {
        if (entry.is_directory()) {
            directory->add(loadDirectory(entry.path().generic_string()));
        } else {
            directory->add(loadFile(entry.path().generic_string()));
        }
    }
    return directory;
}
