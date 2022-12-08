#include <iostream>
#include <functional>

#include "interface.hxx"

using util::VectorPipe;

uint64_t part_one(IT type, uint16_t day) {
    (void) type;
    return day;
}

uint64_t part_two(IT type, uint16_t day) {
    (void) type;
    return day;
}

int main() {
    if(util::Input::exists(IT::SampleInput, 2)) {
        util::show_result(IT::SampleInput, 2022, 2, 1, part_one(IT::SampleInput, 2));
        util::show_result(IT::SampleInput, 2022, 2, 2, part_two(IT::SampleInput, 2));
    } else {
        std::cout << "Sample input for Day 2 does not exist." << std::endl;
    }

    if(util::Input::exists(IT::PuzzleInput, 2)) {
        util::show_result(IT::PuzzleInput, 2022, 2, 1, part_one(IT::PuzzleInput, 2));
        util::show_result(IT::PuzzleInput, 2022, 2, 2, part_two(IT::PuzzleInput, 2));
    } else {
        std::cout << "Puzzle input for Day 2 does not exist." << std::endl;
    }
    return 0;
}