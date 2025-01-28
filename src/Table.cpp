#include "../inc/ode.hpp"

#include <fstream>

int getFileSize(char* path);

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
    /*  Moves the cursor up and i have to refase the code
            Receives:
            Return: 
    */
    int temp = _cursor;
    int i = 0;
    // Collum of _cursor
    while (getChar() != '\n') {
        if (_cursor == -1) {
            _cursor = temp;
            return;
        } else {
            _cursor--;
            i++;
        }
    }
    _cursor--;
    // Line before
    while (getChar() != '\n') {
        if (_cursor == -1) {
            break;
        }
        _cursor--;
    }
    _cursor++;
    // cursorRight(int number)
    for (int j = 0; j < i - 1; j++) {
        _cursor++;
        if (getChar() == '\n') {
            _cursor--;
            return;
        }
    }
}

void Table::cursorDown() {
    /*  Moves the cursor down and i have to refase the code
            Receives:
            Return: 
    */
    int temp = _cursor;
    int i = 0;
    // Collum of _cursor
    while (getChar() != '\n') {
        if (_cursor == -1) {
            break;
        } else {
            _cursor--;
            i++;
        }
    }
    _cursor = temp;
    // Line after
    while (getChar() != '\n') {
        _cursor++;
        if (_cursor > _fileSize) {
            _cursor = temp;
            return;
        }
    }
    _cursor++;
    // cursorRight(int number)
    for (int j = 0; j < i - 1; j++) {
        if (getChar() == '\n' || getChar() == '\0') {
            _cursor--;
            return;
        }
        _cursor++;
    }
}

void Table::cursorLeft() {
    /*  Moves the cursor to the left and if its in the start dont move or if it is a next line go left twice
            Receives:
            Return: 
    */
    if (_cursor > 0) {
        _cursor--;
    }
    if (getChar() == '\n') {
        _cursor--;
    }
}

void Table::cursorRight() {
    /*  Moves the cursor to the right and if its in the end dont move or if it is a next line go right twice
            Receives:
            Return: 
    */
    if (_cursor < _fileSize - 1) {
        _cursor++;
    }
    if (getChar() == '\n') {
        _cursor++;
    }
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