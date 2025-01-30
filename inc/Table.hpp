#ifndef TABLE_HPP
#define TABLE_HPP

#include "TableEntry.hpp"

class Table {
    public:
    Table(char * path);

    char getChar();
    void cursorUp();
    void cursorDown();
    void cursorLeft(int number);
    void cursorRight(int number);
    void cursorRightInLine(int collumn);

    private:
    // TODO add a line
    int _fileSize;
    int _cursor;
    TableEntry** _contents;

    int getLineStart();
    int getNextLine();
    int getLineBefore();
    
};

#endif