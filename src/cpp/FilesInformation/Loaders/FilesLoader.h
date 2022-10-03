//
// Created by Dmytro Klishch on 9/22/22.
//

#ifndef KNOWYOURKNOWLEDGEMYFORK_FILESLOADER_H
#define KNOWYOURKNOWLEDGEMYFORK_FILESLOADER_H


#include "../File.h"

class FilesLoader {
public:
    virtual File loadFile(const std::string &filepath) = 0;
};


#endif //KNOWYOURKNOWLEDGEMYFORK_FILESLOADER_H
