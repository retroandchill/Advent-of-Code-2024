import grid;
#include <iostream>

int main(int argc, char** argv) {
    if (argc <= 1) {
        std::cout << "Not enough arguments\n";
        return 1;
    }
    Grid grid(argv[1]);
    std::cout << "Visited " << grid.get_squares_visited_by_guard() << " tiles" << std::endl;
    return 0;
}
