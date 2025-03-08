#include "../inc/ode.hpp"

void Table::cursorUp() {
    /*  Receives the Line Start than makes the diff to know what is the offset in line then
        search for the line before and jump collumn characters
            Receives:
            Return: 
    */
    int lineStart = getLineStart();
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
    if (_cursor + number < _fileSize + 1) {
        _cursor = _cursor + number;
    } else {
        _cursor = _fileSize;
    }
}

void Table::cursorRightInLine(int collumn) {
    /*  Moves the cursor to the right a certain number or until it reaches a '\n'
            Receives:
            Return: (int ret) the cursor for position + collumn until '\n'
    */
    for (int j = 0; j < collumn; j++) {
        if (getChar() == '\n') {
            return;
        }
        _cursor++;
    }
}