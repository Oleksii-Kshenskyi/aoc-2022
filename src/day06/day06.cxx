#include <iostream>
#include <functional>
#include <unordered_map>
#include <cctype>
#include <regex>
#include <array>

#include "interface.hxx"

using util::VectorPipe;
using util::StringPipe;


uint64_t part_one(std::string& input) {
    uint16_t result = 0;
    for(uint16_t window_start = 0; window_start < input.size() - 4; window_start++) {
        std::string window = input.substr(window_start, 4);
        std::sort(window.begin(), window.end());
        if((std::unique(window.begin(), window.end())) == window.end()) {
            return result + 4;
        } else {
            result++;
        }
    }

    return result;
}

uint64_t part_two(std::string& input) {
    uint16_t result = input.size(); 
    return result;
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