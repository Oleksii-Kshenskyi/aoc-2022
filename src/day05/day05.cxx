#include <iostream>
#include <functional>
#include <unordered_map>
#include <cctype>
#include <regex>

#include "interface.hxx"

using util::VectorPipe;
using util::StringPipe;


uint64_t part_one(VectorPipe<std::string>& input) {
    (void) input;
    return 69;
}

uint64_t part_two(VectorPipe<std::string>& input) {
    (void) input;
    return 69;
}

int main() {
    if(util::Input::exists(IT::SampleInput, 5)) {
        auto input = util::Input(IT::SampleInput, 5).lines();
        util::show_result(IT::SampleInput, 2022, 5, 1, part_one(input));
        util::show_result(IT::SampleInput, 2022, 5, 2, part_two(input));
    } else {
        std::cout << "Sample input for Day 5 does not exist." << std::endl;
    }

    if(util::Input::exists(IT::PuzzleInput, 5)) {
        auto input = util::Input(IT::PuzzleInput, 5).lines();
        util::show_result(IT::PuzzleInput, 2022, 5, 1, part_one(input));
        util::show_result(IT::PuzzleInput, 2022, 5, 2, part_two(input));
    } else {
        std::cout << "Puzzle input for Day 5 does not exist." << std::endl;
    }
    return 0;
}