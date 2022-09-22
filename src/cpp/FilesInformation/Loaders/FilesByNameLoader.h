//
// Created by Dmytro Klishch on 9/22/22.
//

#ifndef KNOWYOURKNOWLEDGEMYFORK_FILESBYNAMELOADER_H
#define KNOWYOURKNOWLEDGEMYFORK_FILESBYNAMELOADER_H


#include "FilesLoader.h"
#include "doctest.h"

class FilesByNameLoader : public FilesLoader {
public:
    File loadFile(const std::string &filepath) override;

private:
    static std::string getFileName(const std::string &filepath);
};


#endif //KNOWYOURKNOWLEDGEMYFORK_FILESBYNAMELOADER_H
