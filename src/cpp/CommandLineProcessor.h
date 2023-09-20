#ifndef KNOWYOURKNOWLEDGE_COMMANDLINEPROCESSOR_H
#define KNOWYOURKNOWLEDGE_COMMANDLINEPROCESSOR_H

#include <string>
#include <iostream>
#include <istream>

class CommandLineProcessor {
private:
    static void addNote(const std::string &title, std::istream& instream= std::cin);
    static void setConfigParameter(const std::string &key, const std::string &value);
    static void addCollection(const std::string &title, const std::string &path);
    // search_method(criteria);
public:
    static void run(int argc, char** argv, std::istream& instream = std::cin);
};

#endif //KNOWYOURKNOWLEDGE_COMMANDLINEPROCESSOR_H
