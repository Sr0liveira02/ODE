#include "../inc/ode.hpp"

#include <fstream>

int getFileSize(char* path);
int getLineBefore();

Table::Table(char* path) {
    /* Creates a table based on a file by creating 1 entry with all the text
        Receives: (char* path) path to the file to be edited
        Returns:
    */
    _fileSize = getFileSize(path);

    // TODO: Solve the problem where the file size is to big
    // Get the content of the file
    std::ifstream file(path, std::ios::in);
    char* content = (char*) malloc(sizeof(char) * (_fileSize + 1));
    file.read(content, _fileSize);
    content[_fileSize] = '\n';
    file.close();

    // Add it to an entry of the Table
    TableEntry* test = new TableEntry(content, 0, _fileSize + 1);

    // Create the Vector of entries in the table
    _contents.push_back(test);

    // Initialize the Cursor
    _cursor = 0;
}

void Table::printf() {
    /*  Loops throw every Entry printing the text with the current character highlighted in red
            Receives:
            Return:
    */
#if DEBUG
        char a = getChar();
        if (a == '\n')
            a = 'N';
        std::cout << "Cursor: " << _cursor << " Char: " << a << "\n";
        std::cout << "Document:\n";
#endif
    long unsigned int i = (long unsigned int) getTableEntry(true);
    for (long unsigned int j = 0; j < i; j++) {
        _contents[j]->print();
    }
    _contents[i]->printf(_cursor);
    for (long unsigned int j = i+1; j < _contents.size(); j++) {
        _contents[j]->print();
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

void Table::charNumberUpdate(int i, int add) {
    /*  Adds <add> to the size of every Entry after position i
            Receives:
            Return:
    */
    for (long unsigned int j = i; j < _contents.size(); j++) {
        _contents[j]->charUpdate(add);
    }
}