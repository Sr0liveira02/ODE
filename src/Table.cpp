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
    char* content = (char*) malloc(sizeof(char) * (_fileSize + 1));
    file.read(content, _fileSize);
    content[_fileSize] = '\0';
    file.close();

    // Add it to an entry of the Table
    TableEntry* test = new TableEntry(content, 1, _fileSize);

    // Create the Vector(array) of entries in the table
    _contents = (TableEntry**) malloc(sizeof(TableEntry*) * 1);
    _contents[0] = test;

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
    if (getChar() == '\n') {
        _cursor--;
    }
}

void Table::cursorRight(int number) {
    /*  Moves the cursor to the right and if its in the end dont move or if it is a next line go right twice
            Receives:
            Return: 
    */
    if (_cursor + number < _fileSize - 1) {
        _cursor = _cursor + number;
    } else {
        _cursor = _fileSize - 2; // maybe on file size
    }
}

void Table::cursorRightInLine(int collumn) {
    /*  Moves the cursor to the right a certain number or until it reaches a '\n'
            Receives:
            Return: (int ret) the cursor for position + collumn until '\n'
    */
    for (int j = 0; j < collumn; j++) {
        _cursor++;
        if (getChar() == '\n' || getChar() == '\0') {
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