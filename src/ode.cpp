#include "../inc/ode.hpp"

bool debug = false;

int main(int argc, char* argv[]) {
    if (argc != 2 && argc != 3) {
        std::cout << "Need at least the 1 arguments!\n";
        std::cout << "./ODE file\n";
        return 0;
    }

    if (argc == 3) {
        if (!strcmp(argv[2], "--debug"))
            debug = true;
    }

    Table* table = new Table(argv[1]);

    // i know its buggy
    char* action = (char*) malloc(sizeof(char) * 100);
    table->printf();
    std::cout << "action: \n";
    std::cin >> action;

    while(strncmp(action, "exit", 4)) {
        if (!strncmp(action, "left", 4)) {
            table->cursorLeft(1);
        } else
        if (!strncmp(action, "right", 5)) {
            table->cursorRight(1);
        } else
        if (!strncmp(action, "down", 4)) {
            table->cursorDown();
        } else
        if (!strncmp(action, "up", 1)) {
            table->cursorUp();
        } else
        if (!strncmp(action, "back", 4)) {
            table->backSpace();
        } else
        if (!strncmp(action, "delete", 6)) {
            table->deleteChar();
        } else 
        if (!strncmp(action, "enter", 5)) {
            table->insertChar('\n');
        } else {
            table->insertChar(action[0]);
        }
        table->printf();
        std::cout << "action: \n";
        std::cin >> action;
    }

    return 0;
}
