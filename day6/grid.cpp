module;

#include <string>
#include <fstream>
#include <iostream>
#include <map>
#include <optional>
#include <ranges>
#include <set>

module grid;

Cell turn_90_degrees(Cell current_position) {
    switch (current_position) {
        case Cell::GuardUp:
            return Cell::GuardRight;
        case Cell::GuardDown:
            return Cell::GuardLeft;
        case Cell::GuardLeft:
            return Cell::GuardUp;
        case Cell::GuardRight:
            return Cell::GuardDown;
        default:
            throw std::invalid_argument("Invalid cell info");
    }
}

std::optional<std::pair<size_t, size_t>> move_guard(const std::vector<std::vector<std::pair<Cell, bool>>> &content, std::pair<size_t, size_t> current_position, Cell direction) {
    switch (direction) {
        case Cell::GuardUp:
            if (current_position.first > 0 && content[current_position.first - 1][current_position.second].first == Cell::Empty) {
                current_position.first--;
            } else if (current_position.first == 0) {
                return std::nullopt;
            }
        break;
        case Cell::GuardDown:
            if (current_position.first < content.size() - 1 && content[current_position.first + 1][current_position.second].first == Cell::Empty) {
                current_position.first++;
            } else if (current_position.first == content.size() - 1) {
                return std::nullopt;
            }
        break;
        case Cell::GuardLeft:
            if (current_position.second > 0 && content[current_position.first][current_position.second - 1].first == Cell::Empty) {
                current_position.second--;
            } else if (current_position.second == 0) {
                return std::nullopt;
            }
        break;
        case Cell::GuardRight:
            if (current_position.second < content[current_position.first].size() - 1 && content[current_position.first][current_position.second + 1].first == Cell::Empty) {
                current_position.second++;
            } else if (current_position.second == content[current_position.first].size() - 1) {
                return std::nullopt;
            }
        break;
        default:
            throw std::invalid_argument("Bad cell position");
    }

    return current_position;
}

void print_grid(const std::vector<std::vector<std::pair<Cell, bool>>> &grid) {
    std::cout << "Current state:\n";
    for (const auto &row : grid) {
        for (const auto &[cell, visited]: row) {
            switch (cell) {
                case Cell::Empty:
                    if (visited) {
                        std::cout << "X";
                    } else {
                        std::cout << ".";
                    }
                    break;
                case Cell::Object:
                    std::cout << "#";
                    break;
                case Cell::GuardUp:
                    std::cout << "^";
                    break;
                case Cell::GuardLeft:
                    std::cout << "<";
                break;
                case Cell::GuardRight:
                    std::cout << ">";
                    break;
                case Cell::GuardDown:
                    std::cout << "v";
            }
        }

        std::cout << "\n";
    }
}

Grid::Grid(std::string_view filename) {
    std::ifstream fin(filename.data());
    if (!fin.is_open()) {
        throw std::invalid_argument("Could not open file");
    }

    std::string line;
    while (std::getline(fin, line)) {
        std::vector<std::pair<Cell, bool>> row;
        for (char c : line) {
            switch (c) {
                case '.':
                    row.emplace_back(Cell::Empty, false);
                    break;
                case '#':
                    row.emplace_back(Cell::Object, false);
                    break;
                case '^':
                    guard_position = { content.size(), row.size() };
                    row.emplace_back(Cell::GuardUp, true);
                    break;
                case '>':
                    guard_position = { row.size(), content.size() };
                    row.emplace_back(Cell::GuardDown, true);
                    break;
                case '<':
                    guard_position = { row.size(), content.size() };
                    row.emplace_back(Cell::GuardLeft, true);
                    break;
                case 'v':
                    guard_position = { row.size(), content.size() };
                    row.emplace_back(Cell::GuardRight, true);
                    break;
            }
        }
        if ( !row.empty()) {
            content.push_back(std::move(row));
        }
    }
}

uint32_t Grid::get_squares_visited_by_guard() const {
    auto grid_copy = content;
    auto visited = calculate_squares_visited_by_guard(grid_copy).value_or(0);
    print_grid(grid_copy);
    return visited;
}

uint32_t Grid::get_possible_obstructions() const {
    auto grid_copy = content;
    calculate_squares_visited_by_guard(grid_copy);

    uint32_t obstructions = 0;
    for (size_t i = 0; i < content.size(); i++) {
        for (size_t j = 0; j < content[i].size(); j++) {
            if (content[i][j].first != Cell::Empty || !grid_copy[i][j].second) {
                continue;
            }

            std::cout << "Checking " << i << " " << j << std::endl;

            auto additional_copy = content;
            additional_copy[i][j].first = Cell::Object;
            auto result = calculate_squares_visited_by_guard(additional_copy);
            if (!result.has_value()) {
                obstructions++;
            }
        }
    }

    return obstructions;
}

std::optional<uint32_t> Grid::calculate_squares_visited_by_guard(std::vector<std::vector<std::pair<Cell, bool>>> &grid_copy) const {
    auto current_position = guard_position;
    std::set<std::pair<std::pair<size_t, size_t>, Cell>> turned_at;
    uint32_t squares_visited_by_guard = 0;
    while (true) {
        auto &[cell, _] = grid_copy[current_position.first][current_position.second];
        auto result = move_guard(grid_copy, current_position, cell);
        if (!result.has_value()) {
            squares_visited_by_guard++;
            break;
        }
        auto &facing_tile = *result;
        if (facing_tile == current_position) {
            if (turned_at.contains({facing_tile, cell})) {
                return std::nullopt;
            }
            turned_at.insert({facing_tile, cell});
            cell = turn_90_degrees(cell);
            continue;
        }

        auto &[facing_cell, visited] = grid_copy[facing_tile.first][facing_tile.second];
        std::swap(facing_cell, cell);
        if ( !visited) {
            squares_visited_by_guard++;
        }
        visited = true;
        current_position = facing_tile;
    }
    return squares_visited_by_guard;
}