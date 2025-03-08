#include "../inc/ode.hpp"

void Table::backSpace() {
    /*  Deletes the character to the left of the cursor by splitting the array in the correct position and then delting it
            Receives:
            Return:
    */
    if (_cursor == 0) {
        return;
    }

    splitOnCursor();

    int i = getTableEntry(false);
    TableEntry* tableEntry = _contents[i];

    tableEntry->deleteLastChar();

    // update every number of the first char(in the table entry) after the one we spilted
    charNumberUpdate(i + 1, -1);

    if (tableEntry->getSize() == 0) {
        _contents.erase(_contents.begin() + i);
        tableEntry->flush();
        free(tableEntry);
    }
    
    // update cursor position
    _cursor--;
    _fileSize--;
}

void Table::deleteChar() {
    /*  Deletes the character to the left of the cursor
            Receives:
            Return:
    */
    if (_cursor == _fileSize + 1) {
        return;
    }
    _cursor++;
    backSpace();
}
