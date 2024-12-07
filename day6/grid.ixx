module;

#include <optional>
#include <string_view>
#include <vector>

export module grid;

enum class Cell {
    Empty,
    Object,
    GuardUp,
    GuardDown,
    GuardLeft,
    GuardRight
};

export class Grid {
public:
    explicit Grid(std::string_view filename);

    uint32_t get_squares_visited_by_guard() const;

    uint32_t get_possible_obstructions() const;

private:
    std::optional<uint32_t> calculate_squares_visited_by_guard(
        std::vector<std::vector<std::pair<Cell, bool>>> &grid_copy) const;

    std::vector<std::vector<std::pair<Cell, bool>>> content;
    std::pair<size_t, size_t> guard_position;
};