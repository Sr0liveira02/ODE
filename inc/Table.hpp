#ifndef TABLE_HPP
#define TABLE_HPP

#include "TableEntry.hpp"

class Table {
    public:
    Table(char * path);
    char getChar(int charNumber);

    private:
    // TODO add a line
    int _char;
    TableEntry** _contents;
    
};

#endif