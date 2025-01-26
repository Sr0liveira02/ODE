#include "../inc/ode.hpp"

#include <fstream>

Table::Table(char* path) {
    std::ifstream filesize(path, std::ios::ate);
    int size = filesize.tellg();
    filesize.close();

    std::cout << "The file has " << size << " characters!\n";

    // TODO: Solve the problem where the file size is to big
    std::ifstream file(path, std::ios::in);
    char* content = (char*) malloc(sizeof(char) * (size + 1));
    file.read(content, size);
    content[size] = '\0';
    file.close();

    TableEntry* test = new TableEntry(content, 1, size);
    _contents = (TableEntry**) malloc(sizeof(TableEntry*) * 1);
    _contents[0] = test;

    _char = 0;
}

char Table::getChar(int charNumber) {
    return _contents[0]->getChar(charNumber);
}