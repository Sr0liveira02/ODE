#include "../inc/ode.hpp"

void Table::backSpace() {
    /*  Deletes the character to the left of the cursor by splitting the array in the correct position
            Receives:
            Return:
    */
    if (_cursor == 0) {
        return;
    }

    int i = getTableEntry(false);
    TableEntry* tableEntry = _contents[i];

    int preSize = tableEntry->getSize();
    // receive the content of the next part of the text if it was separated
    char* nextContent = tableEntry->backSpace(_cursor);
    int posSize = tableEntry->getSize();
    // update every number of the first char(in the table entry) after the one we spilted
    charNumberUpdate(i + 1);

    // if it was the last digit in that entry delete it
    if (posSize == 0) {
        _contents.erase(_contents.begin() + i);
        free(tableEntry);
    }
    int newSize = preSize - posSize - 1;
    
    // update cursor position
    _cursor--;
    if (nextContent == nullptr) {
        return;
    } else {
        TableEntry* next = new TableEntry(nextContent, _cursor,newSize);
        _contents.insert(_contents.begin() + i + 1, next);
        
    }
}

void Table::deleteChar() {
    /*  Deletes the character to the left of the cursor
            Receives:
            Return:
    */
    if (_cursor == _fileSize + 1) {
        return;
    }

    int i = getTableEntry(true);
    TableEntry* tableEntry = _contents[i];

    int preSize = tableEntry->getSize();
    // receive the content of the next part of the text if it was separated
    char* nextContent = tableEntry->deleteChar(_cursor);
    int posSize = tableEntry->getSize();
    // update every entry after the one we spilted
    charNumberUpdate(i + 1);

    // if it was the last digit in that entry delete it
    if (posSize == 0) {
        _contents.erase(_contents.begin() + i);
        i--;
        free(tableEntry);
    }

    int newSize = preSize - posSize - 1;  
    
    if (nextContent == nullptr) {
        charNumberUpdate(i + 1);
        return;
    } else {
        TableEntry* next = new TableEntry(nextContent, _cursor,newSize);
        _contents.insert(_contents.begin() + i + 1, next);
    }
}

void Table::charNumberUpdate(int i) {
    /*  Decreases the size of every Entry after i position by 1
            Receives:
            Return:
    */
    for (long unsigned int j = i; j < _contents.size(); j++) {
        _contents[j]->charUpdate();
    }
}