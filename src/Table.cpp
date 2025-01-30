#include "../inc/ode.hpp"

#include <fstream>

int getFileSize(char* path);
int getLineBefore();

Table::Table(char* path) {
    _fileSize = getFileSize(path);

    // std::cout << "The file has " << _fileSize << " characters!\n";

    // TODO: Solve the problem where the file size is to big
    // Get the content of the file
    std::ifstream file(path, std::ios::in);
    char* content = (char*) malloc(sizeof(char) * (_fileSize + 2));
    file.read(content, _fileSize);
    content[_fileSize] = '\n';
    content[_fileSize + 1] = '\0';
    file.close();

    // Add it to an entry of the Table
    TableEntry* test = new TableEntry(content, 0, _fileSize + 1);

    // Create the Vector of entries in the table
    _contents.push_back(test);

    // Initialize the Cursor
    _cursor = 0;
}

void Table::print() {
    /*  Prints the cursor position the char it is highlighting and then print the entire file
            Receives:
            Return: (char) The char in _cursor
    */
    char a = getChar();
    if (a == '\n')
        a = 'N';
    if(a == '\0')
        a =  'M';
    std::cout << "Cursor: " << _cursor << " Char: " << a << "\n";
    std::cout << "Document:\n";
    for(TableEntry* a : _contents) {
        a->print();
    }
    std::cout << "\n";
}

int getFileSize(char* path) {
    /*  Open file in append mode and ask how far is the cursor
            Receives: (char* path) path to the file
            Return: (int size) file size in number of characters
    */
    std::ifstream filesize(path, std::ios::ate);
    int size = filesize.tellg();
    filesize.close();
    return size;
}
