#include "../inc/ode.hpp"

TableEntry::TableEntry(char* content, int charNumber, int size) {
    _content = content;
    _charNumber = charNumber;
    _mallocSize = size;
    _size = size;
    _mallocOffset = 0;
    _splited = false;
}

TableEntry::TableEntry(char* content, int charNumber, int size, int mallocSize) {
    _content = content;
    _charNumber = charNumber;
    _mallocSize = mallocSize;
    _size = size;
    _mallocOffset = 0;
    _splited = false;
}

char TableEntry::getChar(int charNumber) {
    /*  Acess the Char in the (charNumber) position
            Receives: (int charNumber) Number of the position the char you wish has
            Return: (char) The char in question
    */
    return _content[charNumber - _charNumber];
}

int TableEntry::getStartingNumber() {
    /*  Get Function
            Receives:
            Return: (int) The number of the First character
    */
    return _charNumber;
}

int TableEntry::getSize() {
    /*  Get Function
            Receives:
            Return: (int) The number of the First character
    */
    return _size;
}

void TableEntry::deleteLastChar() {
    /*  Deletes the last char by decreasing the size
            Receives:
            Return:
    */
    _size--;
}

void TableEntry::addChar(char aux) {
    /*  Adds a new char and increases the size
            Receives:
            Return:
    */
    _content[_size] = aux;
    _size++;
}

void TableEntry::print() {
    /* Prints the content of this Table Entry
        Receives:
        Returns:
    */
#if DEBUG
    std::printf("CharNumber: %d Size: %d | ", _charNumber, _size);
#endif    
    std::printf("%.*s", _size, _content);
#if DEBUG
    std::printf("\n");
#endif
}

void TableEntry::printf(int cursor) {
    /* Prints the content of this TableEntry but if the cursor is in the content it prints it in red
        Receives: (int cursor) the cursor position
        Returns:
    */
#if DEBUG
    std::printf("CharNumber: %d Size: %d | ", _charNumber, _size);
#endif
    for (int i = 0; i < cursor - _charNumber; i++) {
        std::printf("%.1s", _content + i);
    }
    if (_content[cursor - _charNumber] == '\n')
        std::printf("\033[;31mN\033[m\n");
    else
        std::printf("\033[;31m%c\033[m", _content[cursor - _charNumber]);
    std::printf("%.*s", _size - cursor + _charNumber - 1, _content + cursor - _charNumber + 1);
#if DEBUG
std::printf("\n");
#endif
}

void TableEntry::charUpdate(int add) {
    /* Updates the _charNumber variable by add
        Receives: (int add) the value to add
        Returns:
    */
    _charNumber += add;
}

char* TableEntry::splitContent(int cursor) {
    /* Splits the char* in the cursor and returns the rest of it
        Receives: (int cursor) the cursor position
        Returns: (char* content) the content that was left out by the split 
    */
    if (cursor == _size + _charNumber) {
        return nullptr;
    } else {
        _splited = true;
        _size = cursor - _charNumber; 
        _mallocSize = cursor - _charNumber;
        return _content + _size;
    }
}

bool TableEntry::isContentFull() {
    /* Checks if content is full
        Receives:
        Returns: (bool) if the content char* is full
    */
    return _size == _mallocSize;
}

void TableEntry::flush() {
    /* frees the _content based on if it was spilted before or no
        Receives:
        Returns:
    */
    if (!_splited) {
        free(_content);
    }
}