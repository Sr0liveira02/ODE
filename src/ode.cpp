#include "../inc/ode.hpp"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Need at least the 1 arguments!\n";
        std::cout << "./ODE file\n";
        return 0;
    }

    Table* table = new Table(argv[1]);
    table->cursorDown();
    table->cursorDown();
    table->cursorRight();
    table->cursorRight();
    table->cursorRight();
    table->cursorUp();
    table->cursorUp();
    std::cout << "Char = " << table->getChar() << "\n";

    return 0;
}
