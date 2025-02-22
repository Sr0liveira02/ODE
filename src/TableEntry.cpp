#include "../inc/ode.hpp"

#define ESC "\033["
#define RESET "\033[m"

TableEntry::TableEntry(char* content, int charNumber, int size) {
    _content = content;
    _charNumber = charNumber;
    _mallocSize = size;
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
    _content[_size - 1] = '\0';
    _size--;
}

void TableEntry::addChar(char aux) {
    /*  Deletes the last char by putting a \0 on the end
            Receives:
            Return:
    */
    _content[_size] = aux;
    _content[_size + 1] = '\0';
    _size++;
}

void TableEntry::print() {
    std::cout << "CharNumber: " << _charNumber << " Size: " << _size << " | " << _content << "\n";
    // std::cout << _content;
}

void TableEntry::printf(int cursor) {
    for (int i = 0; i < cursor - _charNumber; i++) {
        std::cout << _content[i];
    }
    std::cout << ESC << ";" << "31" <<"m"<< _content[cursor - _charNumber] << RESET;
    std::cout << _content + cursor - _charNumber + 1;
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
    return _size == _mallocSize - 1;
}

void TableEntry::flush() {
    if (!_splited) {
        free(_content);
    }
}