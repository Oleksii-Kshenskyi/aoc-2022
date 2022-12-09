#include <iostream>
#include <functional>
#include <unordered_map>
#include <cctype>
#include <regex>

#include "interface.hxx"

using util::VectorPipe;
using util::StringPipe;

class Range {
    public:
        Range(uint16_t from, uint16_t to): _from(from), _to(to) {}
        uint16_t from() { return this->_from; }
        uint16_t to() { return this->_to; }
    private:
        uint16_t _from;
        uint16_t _to;
};

class RangePairs {
    public:
        RangePairs(VectorPipe<std::string>& input) {
            for(auto& line: input.to_vec()) {
                std::regex range_rgx { "^(\\d+)\\-(\\d+),(\\d+)\\-(\\d+)$" };
                std::smatch matches;
                std::regex_search(line, matches, range_rgx);

                Range r1 {static_cast<uint16_t>(std::stoul(matches[1])), static_cast<uint16_t>(std::stoul(matches[2]))};
                Range r2 {static_cast<uint16_t>(std::stoul(matches[3])), static_cast<uint16_t>(std::stoul(matches[4]))};
                this->_ranges.add(std::make_pair(r1, r2));
            }
        }

        uint64_t inclusive_pairs() {
            return this->_ranges
                .count([](auto& pair)
                    { return (pair.first.from() <= pair.second.from() &&
                              pair.first.to() >= pair.second.to()) ||
                             (pair.first.from() >= pair.second.from() &&
                              pair.first.to() <= pair.second.to());
                });
        }
    private:
        VectorPipe<std::pair<Range, Range>> _ranges;
};

uint64_t part_one(VectorPipe<std::string>& input) {
    return RangePairs(input).inclusive_pairs();
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