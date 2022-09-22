//
// Created by Dmytro Klishch on 9/22/22.
//

#ifndef KNOWYOURKNOWLEDGEMYFORK_FILESLOADER_H
#define KNOWYOURKNOWLEDGEMYFORK_FILESLOADER_H


#include "FilesInformation/File.h"
#include "doctest.h"

class FilesLoader {
public:
    virtual File loadFile(const std::string &filepath) = 0;
};


#endif //KNOWYOURKNOWLEDGEMYFORK_FILESLOADER_H
