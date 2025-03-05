#include "../inc/ode.hpp"

extern bool debug;

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
    /*  Deletes the last char by putting a \0 on the end
            Receives:
            Return:
    */
    _size--;
}

void TableEntry::addChar(char aux) {
    /*  Deletes the last char by putting a \0 on the end
            Receives:
            Return:
    */
    _content[_size] = aux;
    _size++;
}

void TableEntry::print() {
    if (debug)
        std::printf("CharNumber: %d Size: %d | ", _charNumber, _size);
    std::printf("%.*s", _size, _content);
    if (debug)
        std::printf("\n");
}

void TableEntry::printf(int cursor) {
    if (debug)
        std::printf("CharNumber: %d Size: %d | ", _charNumber, _size);
    for (int i = 0; i < cursor - _charNumber; i++) {
        std::printf("%.1s", _content + i);
    }
    if (_content[cursor - _charNumber] == '\n')
        std::printf("\033[;31mN\033[m\n");
    else
        std::printf("\033[;31m%c\033[m", _content[cursor - _charNumber]);
    std::printf("%.*s", _size - cursor + _charNumber - 1, _content + cursor - _charNumber + 1);
    if (debug)
        std::printf("\n");
}

void TableEntry::charUpdate(int add) {
    _charNumber += add;
}

char* TableEntry::splitContent(int cursor) {
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
    return _size == _mallocSize;
}

void TableEntry::flush() {
    if (!_splited) {
        free(_content);
    }
}