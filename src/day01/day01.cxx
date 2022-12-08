#include <iostream>
#include <functional>

#include "interface.hxx"

using util::VectorPipe;

uint64_t part_one(IT type, uint16_t day) {
    std::function<uint64_t(VectorPipe<uint64_t>)> sumf = [](auto item) { return item.sum(); };
    std::function<uint64_t(std::string)> convf = [](auto item) { return stoull(item); };
    std::function<VectorPipe<uint64_t>(VectorPipe<std::string>)> vecconvf = [=](auto item) { return item.map(convf); };
    return util::Input(type, day)
            .groups()
            .map(vecconvf)
            .map(sumf)
            .max();
}

uint64_t part_two(IT type, uint16_t day) {
    std::function<uint64_t(VectorPipe<uint64_t>)> sumf = [](auto item) { return item.sum(); };
    std::function<uint64_t(std::string)> convf = [](auto item) { return stoull(item); };
    std::function<VectorPipe<uint64_t>(VectorPipe<std::string>)> vecconvf = [=](auto item) { return item.map(convf); };
    return util::Input(type, day)
            .groups()
            .map(vecconvf)
            .map(sumf)
            .sort_descending()
            .take(3)
            .sum();
}

int main() {
    if(util::Input::exists(IT::SampleInput, 1)) {
        util::show_result(IT::SampleInput, 2022, 1, 1, part_one(IT::SampleInput, 1));
        util::show_result(IT::SampleInput, 2022, 1, 2, part_two(IT::SampleInput, 1));
    } else {
        std::cout << "Sample input for Day 1 does not exist." << std::endl;
    }

    if(util::Input::exists(IT::PuzzleInput, 1)) {
        util::show_result(IT::PuzzleInput, 2022, 1, 1, part_one(IT::PuzzleInput, 1));
        util::show_result(IT::PuzzleInput, 2022, 1, 2, part_two(IT::PuzzleInput, 1));
    } else {
        std::cout << "Puzzle input for Day 1 does not exist." << std::endl;
    }
    return 0;
}