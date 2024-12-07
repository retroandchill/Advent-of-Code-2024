import grid;
#include <iostream>

int main(int argc, char** argv) {
    if (argc <= 1) {
        std::cout << "Not enough arguments\n";
        return 1;
    }
    Grid grid(argv[1]);
    std::cout << grid.get_possible_obstructions() << " obstructions" << std::endl;
    return 0;
}
