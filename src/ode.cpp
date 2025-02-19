#include "../inc/ode.hpp"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Need at least the 1 arguments!\n";
        std::cout << "./ODE file\n";
        return 0;
    }

    Table* table = new Table(argv[1]);
    table->cursorRight(2);
    table->deleteChar();
    table->backSpace();
    table->backSpace();
    table->cursorRight(2);
    table->print();

    return 0;
}
