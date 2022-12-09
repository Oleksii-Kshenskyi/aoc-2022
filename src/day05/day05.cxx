#include <iostream>
#include <functional>
#include <unordered_map>
#include <cctype>
#include <regex>
#include <array>

#include "interface.hxx"

using util::VectorPipe;
using util::StringPipe;

class Crates {
    public:
        Crates(): _crates() {}
        void set_size(size_t size) {
            for(size_t index = 0; index < size; index++) {
                std::vector<char> row(size, 0);
                this->_crates.push_back(row);
            }
        }
        void set_crate(size_t row, size_t column, char crate) {
            this->_crates[row][column] = crate;
        }
        void show() {
            std::cout << "===CRATES===" << std::endl << std::endl;
            for(size_t row_index = 0; row_index < this->_crates.size(); row_index++) {
                for(size_t column_index = 0; column_index < this->_crates[0].size(); column_index++) {
                    std::cout << this->_crates[row_index][column_index] << " ";
                }
                std::cout << std::endl;
            }
            std::cout << "===END CRATES===" << std::endl << std::endl; 
        }
    private:
        std::vector<std::vector<char>> _crates;
};

struct Instruction {
    Instruction(uint16_t quantity, uint16_t from, uint16_t to)
        : quantity(quantity), from(from - 1), to(to - 1) {}

    uint16_t quantity;
    uint16_t from;
    uint16_t to;
};

class Instructions {
    public:
        Instructions(): _instructions() {}
        void add(Instruction&& new_instr) {
            this->_instructions.emplace_back(new_instr);
        }
        const Instruction& at(size_t index) { return this->_instructions[index]; }
        void show() {
            std::cout << "===INSTRUCTIONS===" << std::endl << std::endl;
            for(auto& instr: this->_instructions) {
                std::cout << "Quantity: " << instr.quantity << ";" << std::endl;
                std::cout << "From: " << instr.from << ";" << std::endl;
                std::cout << "To: " << instr.to << ";" << std::endl << std::endl;
            }
            std::cout << "===END INSTRUCTIONS===" << std::endl;
        }
    private:
        std::vector<Instruction> _instructions;
};

class Game {
    public:
        Game(VectorPipe<std::string>& input) {
            VectorPipe<std::string> raw_crates { this->raw_crates(input) };
            std::string labels { input.at(raw_crates.size()) };
            this->_labels_map = this->produce_labels_map(labels);
            VectorPipe<std::string> raw_instructions { this->raw_instructions(input, raw_crates.size() + 1) };
            this->parse_crates(raw_crates);
            this->parse_instructions(raw_instructions);
        }

        Game& show_instructions() {
            this->_instructions.show();
            return *this;
        }
        Game& show_crates() {
            this->_crates.show();
            return *this;
        }
    private:
        Crates _crates;
        Instructions _instructions;
        std::unordered_map<uint16_t, uint16_t> _labels_map;

        std::vector<std::string> raw_crates(VectorPipe<std::string>& input) {
            std::vector<std::string> result;
            for(auto& line: input.to_vec()) {
                if(line[0] != '[') break;
                result.push_back(line);
            }
            return result;
        }
        VectorPipe<std::string> raw_instructions(VectorPipe<std::string>& input, size_t offset) {
            return input.subvec(offset, input.size());
        }

        std::unordered_map<uint16_t, uint16_t> produce_labels_map(std::string& raw) {
            std::unordered_map<uint16_t, uint16_t> result;
            for(size_t index = 0; index < raw.size(); index++) {
                if(raw[index] != ' ') result[index] = (raw[index] - 0x30) - 1;
            }
            return result;
        }

        void parse_crates(VectorPipe<std::string>& raw) {
            this->_crates.set_size(raw.size());
            auto raw_vec = raw.to_vec();
            for(size_t row_index = 0; row_index < raw_vec.size(); row_index++) {
                for(size_t index = 0; index < raw_vec[row_index].size(); index++) {
                    if(std::isalpha(raw_vec[row_index][index])) {
                        size_t crate_row = row_index;
                        size_t crate_col = this->_labels_map[index];
                        this->_crates.set_crate(crate_row, crate_col, raw_vec[row_index][index]);
                    }
                }
            }
        }

        void parse_instructions(VectorPipe<std::string>& raw) {
            for(auto& instr: raw.to_vec()) {
                std::regex instr_rgx { "^move (\\d+) from (\\d+) to (\\d+)$" };
                std::smatch matches;
                std::regex_search(instr, matches, instr_rgx);

                this->_instructions.add(Instruction(static_cast<uint16_t>(stoul(matches[1])),
                                                    static_cast<uint16_t>(stoul(matches[2])),
                                                    static_cast<uint16_t>(stoul(matches[3]))));
            }
        }
};


uint64_t part_one(VectorPipe<std::string>& input) {
    Game(input).show_crates().show_instructions();
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