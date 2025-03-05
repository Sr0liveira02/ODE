#ifndef TABLEENTRY_HPP
#define TABLEENTRY_HPP

class TableEntry {
    public:
    TableEntry(char * content, int charNumber, int size);
    TableEntry(char * content, int charNumber, int size, int mallocSize);
    char getChar(int charNumber);
    int getStartingNumber();
    int getSize();
    char* splitContent(int cursor);
    void print();
    void printf(int cursor);
    void charUpdate(int add);
    void deleteLastChar();
    void addChar(char aux);
    bool isContentFull();
    void flush();

    private:
    int _charNumber;
    int _size;
    int _mallocSize;
    int _mallocOffset;
    char* _content;
    bool _splited;
    // i should add something like lines maybe a line start and line count and a vector of
};

#endif