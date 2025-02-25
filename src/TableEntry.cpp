#include "../inc/ode.hpp"

#define ESC "\033["
#define RESET "\033[m"

TableEntry::TableEntry(char* content, int charNumber, int size) {
    _content = content;
    _charNumber = charNumber;
    _mallocSize = size;
    _size = size;
    _mallocOffset = 0;
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

char* TableEntry::backSpace(int cursor) {
    /*  If it is the last character just reduce the char* otherwise return the rest of the array
            Receives: (int cursor)
            Return: (char*) pointer to the char that we left behind
    */
    if (cursor == _size + _charNumber) {
        _content[cursor - _charNumber - 1] = '\0';
        _size--;
        // ajusta-se o mallocSize????
        return nullptr;
    } else {
        _content[cursor - _charNumber - 1] = '\0';
        _size = cursor - 1 - _charNumber; 
        _mallocSize = cursor - 1 - _charNumber;
        return _content + _size + 1;
    }
}

char* TableEntry::deleteChar(int cursor) {
    /*  If it is the first character just increase +1 the char* otherwise return the rest of the array
            Receives: (int cursor)
            Return: (char*) pointer to the char that we left behind
    */
    if (cursor == _charNumber) {
        _content++;
        _mallocOffset++;
        _size--;
        // ajusta-se o mallocSize????
        return nullptr;
    } else {
        _content[cursor - _charNumber] = '\0';
        _size = cursor - _charNumber; 
        _mallocSize = cursor - 1 - _charNumber;
        return _content + _size + 1;
    }
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

void TableEntry::charUpdate() {
    _charNumber--;
}