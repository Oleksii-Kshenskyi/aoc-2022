#include <iostream>
#include <functional>
#include <unordered_map>
#include <cctype>

#include "interface.hxx"

using util::VectorPipe;
using util::StringPipe;

char one_char(const std::string& line) {
    std::unordered_map<char, size_t> freqs;
    std::string one(line.begin(), line.begin() + (line.size() / 2));
    std::string two(line.begin() + (line.size() / 2), line.end());

    for(size_t index = 0; index < one.size(); index++) {
        auto one_found = freqs.find(one[index]);
        if(one_found == freqs.end()) freqs[one[index]] = 1;
        else if((one_found->second) == 2) return one[index];

        auto two_found = freqs.find(two[index]);
        if(two_found == freqs.end()) freqs[two[index]] = 2;
        else if(two_found->second == 1) return two[index];
    }

    throw "Day 3, one_char(): reached the end, duplicate not found!";
}
uint64_t code_sum(const std::string& codes) {
    uint64_t acc = 0;
    for(char ch: codes) {
        if(std::isupper(ch)) acc += (ch - 0x40) + 26;
        else if(std::islower(ch)) acc += (ch - 0x60);
        else throw "Day 3, code_sum(): NOT UPPER OR LOWER?!";
    }
    return acc;
}
uint64_t part_one(VectorPipe<std::string>& input) {
    std::string result;
    for(const auto& line: input.to_vec()) {
        result += one_char(line);
    }
    return code_sum(result);
}

uint64_t part_two(VectorPipe<std::string>& input) {
    (void) input;
    return 1;
}

int main() {
    if(util::Input::exists(IT::SampleInput, 3)) {
        VectorPipe<std::string> input = util::Input(IT::SampleInput, 3).lines();
        util::show_result(IT::SampleInput, 2022, 3, 1, part_one(input));
        util::show_result(IT::SampleInput, 2022, 3, 2, part_two(input));
    } else {
        std::cout << "Sample input for Day 3 does not exist." << std::endl;
    }

    if(util::Input::exists(IT::PuzzleInput, 3)) {
        VectorPipe<std::string> input = util::Input(IT::PuzzleInput, 3).lines();
        util::show_result(IT::PuzzleInput, 2022, 3, 1, part_one(input));
        util::show_result(IT::PuzzleInput, 2022, 3, 2, part_two(input));
    } else {
        std::cout << "Puzzle input for Day 3 does not exist." << std::endl;
    }
    return 0;
}