//
// Created by Dmytro Klishch on 9/22/22.
//

#ifndef KNOWYOURKNOWLEDGEMYFORK_FILE_H
#define KNOWYOURKNOWLEDGEMYFORK_FILE_H


#include <string>

class File {
public:
    File(std::string filepath, std::string filename, std::string extension);

    std::string filename() const;

    std::string extension() const;

    std::string filepath() const;

    bool exists();

private:
    std::string _filename;
    std::string _extension;
    std::string _filepath;
};


#endif //KNOWYOURKNOWLEDGEMYFORK_FILE_H
