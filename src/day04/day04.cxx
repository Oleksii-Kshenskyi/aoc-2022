#include <iostream>
#include <functional>
#include <unordered_map>
#include <cctype>

#include "interface.hxx"

using util::VectorPipe;
using util::StringPipe;


uint64_t part_one(VectorPipe<std::string>& input) {
    (void) input;
    return 0;
}

uint64_t part_two(VectorPipe<std::string>& input) {
    (void) input;
    return 0;
}

int main() {
    if(util::Input::exists(IT::SampleInput, 4)) {
        VectorPipe<std::string> input = util::Input(IT::SampleInput, 4).lines();
        util::show_result(IT::SampleInput, 2022, 4, 1, part_one(input));
        util::show_result(IT::SampleInput, 2022, 4, 2, part_two(input));
    } else {
        std::cout << "Sample input for Day 4 does not exist." << std::endl;
    }

    if(util::Input::exists(IT::PuzzleInput, 4)) {
        VectorPipe<std::string> input = util::Input(IT::PuzzleInput, 4).lines();
        util::show_result(IT::PuzzleInput, 2022, 4, 1, part_one(input));
        util::show_result(IT::PuzzleInput, 2022, 4, 2, part_two(input));
    } else {
        std::cout << "Puzzle input for Day 4 does not exist." << std::endl;
    }
    return 0;
}