//
// Created by Dmytro Klishch on 9/22/22.
//

#ifndef KNOWYOURKNOWLEDGEMYFORK_FILESBYNAMELOADER_H
#define KNOWYOURKNOWLEDGEMYFORK_FILESBYNAMELOADER_H


#include "FilesLoader.h"
#include "EncodingDetector/text_encoding_detect.h"
#include <fstream>

class FilesByNameLoader : public FilesLoader {
public:
    File loadFile(const std::string &filepath) override;

    FilesByNameLoader(const std::string &separator = "/");

    std::string separator() const;

private:
    std::string _separator;

    std::string getFileName(const std::string &filepath);

    bool isTextFile(const std::string &filepath);
};


#endif //KNOWYOURKNOWLEDGEMYFORK_FILESBYNAMELOADER_H
