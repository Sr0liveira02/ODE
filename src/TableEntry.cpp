#include "../inc/ode.hpp"

TableEntry::TableEntry(char* content, int charNumber, int size) {
    _content = content;
    _charNumber = charNumber;
    _size = size;
}

char TableEntry::getChar(int charNumber) {
    /*  Acess the Char in the (charNumber) position
            Receives: (int charNumber) Number of the position the char you wish has
            Return: (char) The char in question
    */
    return _content[charNumber];
}