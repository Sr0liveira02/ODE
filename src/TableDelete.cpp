#include "../inc/ode.hpp"

void Table::backSpace() {
    /*  Deletes the character to the left
            Receives:
            Return:
    */
    if (_cursor == 0) {
        return;
    }
    int i = getTableEntry();
    TableEntry* tableEntry = _contents[i];

    int preSize = tableEntry->getSize();
    char* nextContent = tableEntry->backSpace(_cursor);
    int posSize = tableEntry->getSize();
    // if it was the last
    if (posSize == 0) {
        _contents.erase(_contents.begin() + i);
        free(tableEntry);
    }
    int newSize = preSize - posSize - 1;
    
    _cursor--;
    if (nextContent == nullptr) {
        return;
    } else {
        TableEntry* next = new TableEntry(nextContent, _cursor,newSize);
        _contents.insert(_contents.begin() + i + 1, next);
        
    }
}