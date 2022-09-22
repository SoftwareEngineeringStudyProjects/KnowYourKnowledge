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

    FilesByNameLoader(const std::string &separator = "/");

    std::string separator() const;

private:
    std::string getFileName(const std::string &filepath);
    std::string _separator;
};


#endif //KNOWYOURKNOWLEDGEMYFORK_FILESBYNAMELOADER_H
