#ifndef TABLE_HPP
#define TABLE_HPP

#include "TableEntry.hpp"
#include <vector>

class Table {
    public:
    Table(char * path);

    char getChar();
    void cursorUp();
    void cursorDown();
    void cursorLeft(int number);
    void cursorRight(int number);
    void cursorRightInLine(int collumn);
    void backSpace();
    void deleteChar();
    void print();

    private:
    // TODO add a line
    int _fileSize;
    int _cursor;
    std::vector<TableEntry*> _contents;

    int getLineStart();
    int getNextLine();
    int getLineBefore();

    int getTableEntry(bool equal);
    void charNumberUpdate(int i);
    
};

#endif