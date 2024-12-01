#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>
#include <ranges>
#include <algorithm>
#include <cassert>
#include <numeric>

int main() {
    std::string input_file;
    std::cout << "Enter the file name: ";
    std::cin >> input_file;
    std::ifstream input(std::filesystem::current_path().parent_path() / input_file);

    if (!input.is_open()) {
        std::cerr << "Failed to open file " << input_file << std::endl;
        return 1;
    }

    std::vector<int> list1;
    std::vector<int> list2;
    while (!input.eof()) {
        int value1;
        int value2;
        input >> value1 >> value2;
        list1.push_back(value1);
        list2.push_back(value2);
    }
    assert(list1.size() == list2.size());

    std::ranges::sort(list1, std::greater());
    std::ranges::sort(list2, std::greater());

    std::vector<int> diffs;
    for (int i = 0; i < list1.size(); i++) {
        diffs.push_back(std::abs(list1[i] - list2[i]));
    }
    int sum = std::accumulate(diffs.begin(), diffs.end(), 0);
    std::cout << "The sum is: " << sum << std::endl;

    return 0;
}
