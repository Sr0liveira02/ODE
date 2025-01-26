#ifndef TABLEENTRY_HPP
#define TABLEENTRY_HPP

class TableEntry {
    public:
    TableEntry(char * content, int charNumber, int size);
    char getChar(int charNumber);

    private:
    int _charNumber;
    int _size;
    char* _content;
    // i should add something like lines maybe a line start and line count and a vector of
};

#endif