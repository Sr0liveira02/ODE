#include "../inc/ode.hpp"

int Table::getLineStart() {
    /*  Get the cursor back until finds a '\n'
            Receives:
            Return: (int size) the cursor int where the line start is
    */
    if (_cursor == 0)
        return 0;
    int temp = _cursor;
    int ret;
    _cursor--;
    while (getChar() != '\n') {
        _cursor--;
        if (_cursor == -1)
            break;
    }
    _cursor++;
    ret = _cursor;
    _cursor = temp;
    return ret;
}

int Table::getNextLine() {
    /*  Get the cursor forward until finds a '\n'
            Receives:
            Return: (int size) the cursor int where the next line start is
    */
    if (_cursor == _fileSize) {
        return -1;
    }
    int temp = _cursor;
    int ret = -1;
    while (getChar() != '\n') {
        _cursor++;
        if (_cursor > _fileSize) {
            _cursor = temp;
            return ret;
        }
    }
    _cursor++;
    ret = _cursor;
    _cursor = temp;
    return ret;
}

int Table::getLineBefore() {
    /*  Get the cursor forward until finds a '\n'
            Receives:
            Return: (int size) the cursor int where the next line start is
    */
    int temp = _cursor;
    _cursor = getLineStart();
    if (_cursor - 2 > 0)
        _cursor = _cursor - 2;
    else
        return -1;
    int ret = getLineStart();
    _cursor = temp;
    return ret;
}

int Table::getTableEntry(bool equal) {
    /*  Loops throw the Table entries trying to find wich one contains the _cursor
            Receives: (bool equal) if equal is false it returns the tableEntry of the _cusor -= 1
            Return: (TableEntry* ret) The Table entry that contains the character in teh Cursor
    */
    int ret = -1;
    for (int i = _contents.size() - 1; i >= 0; i--) {
        TableEntry* temp = _contents[i];
        if (temp->getStartingNumber() <= _cursor) {
            // if u dont want the < to be equal it will return the one before this
            if (_cursor == temp->getStartingNumber() && !equal) {
                ret = i - 1;
            } else {
                ret = i;
            }
            return ret;
        }
    }
    return ret;
}

char Table::getChar() {
    /*  Acess the Char in the (charNumber) position going through the various Table Entries
            Receives:
            Return: (char) The char in _cursor
    */
    return _contents[getTableEntry(true)]->getChar(_cursor);
}

void Table::splitOnCursor() {
    /*  Splits the TableEntry on the cursor and creates a new tableEntry right after
        Receives:
        Return: (int) -1 if it did not split 0 otherwise
    */
    int i = getTableEntry(false);
    TableEntry* tableEntry = _contents[i];

    int preSize = tableEntry->getSize();
    // receive the content of the next part of the text if it was separated
    char* nextContent = tableEntry->splitContent(_cursor);
    int posSize = tableEntry->getSize();

    int newSize = preSize - posSize;

    if (nextContent == nullptr) {
        return;
    } else {
        TableEntry* next = new TableEntry(nextContent, _cursor,newSize);
        _contents.insert(_contents.begin() + i + 1, next);
    }
}
