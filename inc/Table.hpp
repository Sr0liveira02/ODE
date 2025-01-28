#ifndef TABLE_HPP
#define TABLE_HPP

#include "TableEntry.hpp"

class Table {
    public:
    Table(char * path);
    char getChar();
    void cursorUp();
    void cursorDown();
    void cursorLeft();
    void cursorRight();

    private:
    // TODO add a line
    int _fileSize;
    int _cursor;
    TableEntry** _contents;
    
};

#endif