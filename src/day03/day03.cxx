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

char one_char_group(VectorPipe<std::string>& group) {
    uint16_t ool = 1;
    uint16_t olo = 2;
    uint16_t loo = 4;
    std::unordered_map<char, uint16_t> freqs;

    std::function<size_t(std::string)> sizef = [=](auto s) { return s.size(); };
    auto size_vec = group.map(sizef).to_vec();
    size_t max_size = *std::max_element(size_vec.begin(), size_vec.end());

    for(size_t index = 0; index < max_size; index++) {
        auto one_found = freqs.end();
        auto two_found = freqs.end();
        auto three_found = freqs.end();

        if(index < group.at(0).size()) {
            one_found = freqs.find(group.at(0)[index]);
            if(one_found == freqs.end()) freqs[group.at(0)[index]] = ool;
            else freqs[group.at(0)[index]] = freqs[group.at(0)[index]] | ool;
        }

        if(index < group.at(1).size()) {
            two_found = freqs.find(group.at(1)[index]);
            if(two_found == freqs.end()) freqs[group.at(1)[index]] = olo;
            else freqs[group.at(1)[index]] = freqs[group.at(1)[index]] | olo;
        }

        if(index < group.at(2).size()) {
            three_found = freqs.find(group.at(2)[index]);
            if(three_found == freqs.end()) freqs[group.at(2)[index]] = loo;
            else freqs[group.at(2)[index]] = freqs[group.at(2)[index]] | loo;
        }
    }

    for(auto item: freqs) {
        if(item.second == 0b111) { return item.first; }
    }

    std::cout << "Day 3, one_char_group(): No matches found..." << std::endl;
    throw "one_char_group()";
}
uint64_t part_two(VectorPipe<std::string>& input) {
    std::string result;
    for(auto& group: input.partition(3).to_vec()) {
        char ocg = one_char_group(group);
        result += ocg;
    }
    return code_sum(result);
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