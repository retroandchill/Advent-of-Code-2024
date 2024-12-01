#include <filesystem>
#include <iostream>
import common;

constexpr auto INPUT_DIR = "problem1";

int main() {
    try {
        auto input_file = request_input_file();
        auto file_path = std::filesystem::current_path() / INPUT_DIR / input_file;
        NumberLists number_lists(file_path);
        int sum = number_lists.get_distance_sum();
        std::cout << "The sum is: " << sum << std::endl;

        return 0;
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
}
