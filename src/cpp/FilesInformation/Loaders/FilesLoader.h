//
// Created by Dmytro Klishch on 9/22/22.
//

#ifndef KNOWYOURKNOWLEDGEMYFORK_FILESLOADER_H
#define KNOWYOURKNOWLEDGEMYFORK_FILESLOADER_H


#include "../File.h"
#include "../../Directory.h"


class FilesLoader {
public:
    virtual File *loadFile(const std::string &filepath) = 0;

    Directory *loadDirectory(const std::string &filepath);

    virtual ~FilesLoader() = default;
};


#endif //KNOWYOURKNOWLEDGEMYFORK_FILESLOADER_H
