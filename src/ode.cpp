#include "../inc/ode.hpp"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Need at least the 1 arguments!\n";
        std::cout << "./ODE file\n";
        return 0;
    }

    Table* table = new Table(argv[1]);
    table->cursorLeft(1);
    table->cursorDown();
    table->cursorDown();
    char a = table->getChar();
    if (a == '\n')
        a = 'N';
    if (a == '\0')
        a = 'M';
    std::cout << "Char = " << a << "\n";

    return 0;
}
