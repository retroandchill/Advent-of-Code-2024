#include <filesystem>
#include <iostream>
import common;

int main() {
    try {
        auto input_file = request_input_file();
        auto file_path = std::filesystem::current_path() / input_file;
        NumberLists number_lists(file_path);
        int similarity = number_lists.get_similarity();
        std::cout << "The similarity score is: " << similarity << std::endl;

        return 0;
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
}