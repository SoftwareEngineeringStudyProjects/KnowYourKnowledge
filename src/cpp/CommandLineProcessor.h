#ifndef KNOWYOURKNOWLEDGE_COMMANDLINEPROCESSOR_H
#define KNOWYOURKNOWLEDGE_COMMANDLINEPROCESSOR_H

#include <string>
#include <TextNote.h>

class CommandLineProcessor {
private:
    static void addNote(const std::string &title);
    // search_method(criteria);
public:
    static void run(int argc, char** argv);
};

#endif //KNOWYOURKNOWLEDGE_COMMANDLINEPROCESSOR_H
