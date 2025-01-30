#include "../inc/ode.hpp"

int Table::getLineStart() {
    /*  Get the cursor back until finds a '\n'
            Receives:
            Return: (int size) the cursor int where the line start is
    */
    int temp = _cursor;
    int ret;
    _cursor--;
    while (getChar() != '\n') {
        if (_cursor == -1) {
            break;
        } else {
            _cursor--;
        }
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
            Receives:
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