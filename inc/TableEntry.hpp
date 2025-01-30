#ifndef TABLEENTRY_HPP
#define TABLEENTRY_HPP

class TableEntry {
    public:
    TableEntry(char * content, int charNumber, int size);
    char getChar(int charNumber);
    int getStartingNumber();
    int getSize();
    char* backSpace(int cursor);
    char* deleteChar(int cursor);
    void print();

    private:
    int _charNumber;
    int _size;
    int _mallocSize;
    int _mallocOffset;
    char* _content;
    // i should add something like lines maybe a line start and line count and a vector of
};

#endif