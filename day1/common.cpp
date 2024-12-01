/**
 * @file common.cpp
 * @brief Implementation for the common code.
 *
 * @author Retro & Chill
 * https://github.com/retroandchill
 */
module;

#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>
#include <numeric>

module common;

NumberLists::NumberLists(const std::filesystem::path &path) {
    {
        std::ifstream input(path);

        if (!input.is_open()) {
            std::cerr << "Failed to open file " << path.relative_path() << std::endl;
            auto message = std::format("Failed to open file!");
            throw std::filesystem::filesystem_error(message, path, std::make_error_code(std::errc::no_such_file_or_directory));
        }

        while (!input.eof()) {
            int value1;
            int value2;
            input >> value1 >> value2;
            list1.push_back(value1);
            list2.push_back(value2);
        }

        if (list1.size() != list2.size()) {
            throw std::invalid_argument("Numbers lists have different size");
        }
    }
}

int NumberLists::get_distance_sum() {
    {
        std::ranges::sort(list1, std::greater());
        std::ranges::sort(list2, std::greater());

        std::vector<int> diffs;
        for (int i = 0; i < list1.size(); i++) {
            diffs.push_back(std::abs(list1[i] - list2[i]));
        }
        return std::accumulate(diffs.begin(), diffs.end(), 0);
    }
}

std::string request_input_file() {
    std::string input_file;
    std::cout << "Enter the file name: ";
    std::cin >> input_file;
    return input_file;
}
