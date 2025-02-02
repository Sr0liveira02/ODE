#include "../inc/ode.hpp"

void Table::backSpace() {
    /*  Deletes the character to the left of the cursor
            Receives:
            Return:
    */
    if (_cursor == 0) {
        return;
    }
    int i = getTableEntry(false);
    TableEntry* tableEntry = _contents[i];

    int preSize = tableEntry->getSize();
    char* nextContent = tableEntry->backSpace(_cursor);
    int posSize = tableEntry->getSize();
    // if it was the last
    if (posSize == 0) {
        _contents.erase(_contents.begin() + i);
        i--;
        free(tableEntry);
    }
    int newSize = preSize - posSize - 1;
    
    _cursor--;
    if (nextContent == nullptr) {
        charNumberUpdate(i + 1);
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
    char* nextContent = tableEntry->deleteChar(_cursor);
    int posSize = tableEntry->getSize();
    // if it was the last digit on the Entry
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