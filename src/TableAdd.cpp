#include "../inc/ode.hpp"

void Table::insertChar(char aux) {
    /* Creates a new entry(if needed) and adds aux char
        Receives: (char aux)
        Returns: 
    */

    // create new table entry if needed
    if (_cursor == 0) {
        createTableEntry(-1);
        TableEntry* tableEntry = _contents[0];
        tableEntry->addChar(aux);
        charNumberUpdate(1, +1);
        _cursor++;
        return;
    }

    splitOnCursor();

    int i = getTableEntry(false);
    TableEntry* tableEntry = _contents[i];

    // if tableEntry is full create a new one otherwise just write the character 
    if (tableEntry->isContentFull()) {
        createTableEntry(i);
        tableEntry = _contents[i + 1];
        tableEntry->addChar(aux);
        charNumberUpdate(i + 2, +1);
    } else {
        tableEntry->addChar(aux);
        charNumberUpdate(i + 1, +1);
    }
    
    // update cursor position
    _fileSize++;
    _cursor++;
}

void Table::createTableEntry(int i) {
    /* Creates a new tableEntry with char* of size according to the last character
        Receives: (int i) index of the TableEntry to be added
        Returns: 
    */
    // get Last Char
    char lastChar;
    if (_cursor == 0) {
        lastChar = '\n';
    } else {
        _cursor--;
        lastChar = getChar();
        _cursor++;
    }
    
    // create the char* based on last char
    int mallocSize;
    if (lastChar == '\n') {
        mallocSize = END_SETENCE_ALLOC_SIZE;
    } else {
        mallocSize = MID_SETENCE_ALLOC_SIZE;
    }
    char* _content = (char*) malloc(mallocSize * sizeof(char));

    TableEntry* next = new TableEntry(_content, _cursor, 0, mallocSize);
    _contents.insert(_contents.begin() + i + 1, next);
}
