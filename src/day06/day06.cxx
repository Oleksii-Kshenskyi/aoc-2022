#include <iostream>
#include <functional>
#include <unordered_map>
#include <cctype>
#include <regex>
#include <array>

#include "interface.hxx"

using util::VectorPipe;
using util::StringPipe;

uint64_t first_unique(std::string& input, uint16_t window_size) {
    uint16_t result = 0;
    for(uint16_t window_start = 0; window_start < input.size() - window_size; window_start++) {
        std::string window = input.substr(window_start, window_size);
        std::sort(window.begin(), window.end());
        if((std::unique(window.begin(), window.end())) == window.end()) {
            return result + window_size;
        } else {
            result++;
        }
    }

    return result;
}

uint64_t part_one(std::string& input) {
    return first_unique(input, 4);
}

uint64_t part_two(std::string& input) {
    return first_unique(input, 14);
}

int main() {
    if(util::Input::exists(IT::SampleInput, 6)) {
        auto input = util::Input(IT::SampleInput, 6).str().to_string();
        util::show_result(IT::SampleInput, 2022, 6, 1, part_one(input));
        util::show_result(IT::SampleInput, 2022, 6, 2, part_two(input));
    } else {
        std::cout << "Sample input for Day 6 does not exist." << std::endl;
    }

    if(util::Input::exists(IT::PuzzleInput, 6)) {
        auto input = util::Input(IT::PuzzleInput, 6).str().to_string();
        util::show_result(IT::PuzzleInput, 2022, 6, 1, part_one(input));
        util::show_result(IT::PuzzleInput, 2022, 6, 2, part_two(input));
    } else {
        std::cout << "Puzzle input for Day 6 does not exist." << std::endl;
    }
    return 0;
}