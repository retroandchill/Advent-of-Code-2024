/**
 * @file common.ixx
 * @brief Module with the common code for the advent of code problem
 *
 * @author Retro & Chill
 * https://github.com/retroandchill
 */
module;

#include <filesystem>
#include <vector>

export module common;

export class NumberLists {
    public:
        explicit NumberLists(const std::filesystem::path &path);

    int get_distance_sum();
    int get_similarity();

    private:
        std::vector<int> list1;
        std::vector<int> list2;
};

export std::string request_input_file();
