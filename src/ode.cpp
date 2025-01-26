#include "../inc/ode.hpp"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cout << "Need at least the 2 arguments!\n";
        std::cout << "./ODE file charNumber\n";
        return 0;
    }

    Table* table = new Table(argv[1]);
    std::cout << "Char = " << table->getChar(atoi(argv[2]) - 1) << "\n";

    return 0;
}
