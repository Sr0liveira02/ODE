#include "../inc/ode.hpp"

#include <fstream>

int getFileSize(char* path);
int getLineBefore();

Table::Table(char* path) {
    _fileSize = getFileSize(path);

    // std::cout << "The file has " << _fileSize << " characters!\n";

    // TODO: Solve the problem where the file size is to big
    // Get the content of the file
    std::ifstream file(path, std::ios::in);
    char* content = (char*) malloc(sizeof(char) * (_fileSize + 2));
    file.read(content, _fileSize);
    content[_fileSize] = '\n';
    content[_fileSize + 1] = '\0';
    file.close();

    // Add it to an entry of the Table
    TableEntry* test = new TableEntry(content, 0, _fileSize + 1);

    // Create the Vector of entries in the table
    _contents.push_back(test);

    // Initialize the Cursor
    _cursor = 0;
}

char Table::getChar() {
    /*  Acess the Char in the (charNumber) position going through the various Table Entries
            Receives:
            Return: (char) The char in _cursor
    */
    return _contents[0]->getChar(_cursor);
}

void Table::cursorUp() {
    /*  Receives the Line Start than makes the diff to know what is the offset in line then
        search for the line before and jump collumn characters
            Receives:
            Return: 
    */
    int lineStart =  getLineStart();
    if (lineStart == 0) {
        return;
    }
    int collumn = _cursor - lineStart;
    int lineBefore = getLineBefore();
    _cursor = lineBefore;
    cursorRightInLine(collumn);
}

void Table::cursorDown() {
    /*  Receives the Line Start than makes the diff to know what is the offset in line then
        search for the line after and jump collumn characters
            Receives:
            Return: 
    */
    int collumn = _cursor - getLineStart();
    int nextLine = getNextLine();
    if (nextLine == -1) {
        _cursor = _fileSize;
        return;
    }
    _cursor = nextLine;
    cursorRightInLine(collumn);
}

void Table::cursorLeft(int number) {
    /*  Moves the cursor to the left and if its in the start dont move or if it is a next line go left twice
            Receives:
            Return: 
    */
    if (_cursor - number > 0) {
        _cursor = _cursor - number;
    } else {
        _cursor = 0;
    }
}

void Table::cursorRight(int number) {
    /*  Moves the cursor to the right and if its in the end dont move or if it is a next line go right twice
            Receives:
            Return: 
    */
    if (_cursor + number < _fileSize) {
        _cursor = _cursor + number;
    } else {
        _cursor = _fileSize; // maybe on file size
    }
}

void Table::cursorRightInLine(int collumn) {
    /*  Moves the cursor to the right a certain number or until it reaches a '\n'
            Receives:
            Return: (int ret) the cursor for position + collumn until '\n'
    */
    for (int j = 0; j < collumn; j++) {
        _cursor++;
        if (getChar() == '\n') {
            return;
        }
    }
}

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
    char* content = tableEntry->backSpace(_cursor);
    int posSize = tableEntry->getSize();
    _cursor--;
    if (content == nullptr) {
        return;
    } else {
        TableEntry* next = new TableEntry(content, _cursor, preSize - posSize - 1);
        _contents.insert(_contents.begin() + i + 1, next);
        if (posSize == 0) {
            _contents.erase(_contents.begin() + i);
            free(tableEntry);
        }
    }
}

int Table::getTableEntry() {
    /*  Loops throw the Table entries trying to find wich one contains the _cursor
            Receives:
            Return: (TableEntry* ret) The Table entry that contains the character in teh Cursor
    */
    int ret = -1;
    for (int i = _contents.size() - 1; i >= 0; i--) {
        TableEntry* temp = _contents[i];
        if (temp->getStartingNumber() < _cursor) {
            ret = i;
            return ret;
        }
    }
    return ret;
}

void Table::print() {
    for(TableEntry* a : _contents) {
        a->print();
    }
    std::cout << "\n";
}

int getFileSize(char* path) {
    /*  Open file in append mode and ask how far is the cursor
            Receives: (char* path) path to the file
            Return: (int size) file size in number of characters
    */
    std::ifstream filesize(path, std::ios::ate);
    int size = filesize.tellg();
    filesize.close();
    return size;
}

