#ifndef KNOWYOURKNOWLEDGE_COMMANDLINEPROCESSOR_H
#define KNOWYOURKNOWLEDGE_COMMANDLINEPROCESSOR_H

#include <string>

class CommandLineProcessor {
private:
    static void addNote(const std::string &title);
    static void setConfigParameter(const std::string &key, const std::string &value);
    static void addCollection(const std::string &title, const std::string &path);
    // search_method(criteria);
public:
    static void run(int argc, char** argv);
};

#endif //KNOWYOURKNOWLEDGE_COMMANDLINEPROCESSOR_H
