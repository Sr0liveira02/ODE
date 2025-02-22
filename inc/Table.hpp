#ifndef TABLE_HPP
#define TABLE_HPP

#include "TableEntry.hpp"
#include <vector>

// size in chars of how many memory to alloc if a new letter is written in "position"
#define MID_SETENCE_ALLOC_SIZE 50
#define END_SETENCE_ALLOC_SIZE 1000
#define END_FILE_ALLOC_SIZE 2000

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
    void insertChar(char aux);
    void print();
    void printf();

    private:
    // TODO add a line
    int _fileSize;
    int _cursor;
    std::vector<TableEntry*> _contents;

    int getLineStart();
    int getNextLine();
    int getLineBefore();
    void splitOnCursor(); // splits the table entry into 2
    void createTableEntry(int i);

    int getTableEntry(bool equal);
    void charNumberUpdate(int i, int add);
    
};

#endif