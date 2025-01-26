#include "../inc/ode.hpp"

TableEntry::TableEntry(char* content, int charNumber, int size) {
    _content = content;
    _charNumber = charNumber;
    _size = size;
}

char TableEntry::getChar(int charNumber) {
    return _content[charNumber];
}