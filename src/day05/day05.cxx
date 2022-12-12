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
            this->_crates.resize(size);
        }
        void push_crate(size_t row, char crate) {
            if (this->_crates.size() <= row) this->_crates.reserve(row * 2);
            this->_crates[row].push_back(crate);
        }
        void show() {
            std::cout << "===CRATES===" << std::endl << std::endl;
            for(size_t row_index = 0; row_index < this->_crates.size(); row_index++) {
                std::cout << "ROW " << row_index << ": " << this->_crates[row_index] << std::endl;
            }
            std::cout << "===END CRATES===" << std::endl << std::endl; 
        }
        size_t size() { return _crates.size(); }
        Crates& move_stack(uint16_t quantity, uint16_t from, uint16_t to) {
            for(uint16_t time = 0; time < quantity; time++)
                this->move_crate(from, to);
            return *this;
        }
        Crates& move_crate(uint16_t from, uint16_t to) {
            char crate = this->_crates[from].back();
            this->_crates[from].pop_back();
            this->_crates[to].push_back(crate);
            return *this;
        }
        std::string top_message() {
            std::string message = "";
            for(auto& stack: this->_crates) {
                message += stack.back();
            }
            return message;
        }
    private:
        std::vector<std::string> _crates;
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
        size_t size() { return _instructions.size(); }
        std::vector<Instruction>& vec() { return this->_instructions; }
    private:
        std::vector<Instruction> _instructions;
};

class Game {
    public:
        Game(VectorPipe<std::string>& input) {
            VectorPipe<std::string> raw_crates { this->raw_crates(input) };
            std::string labels { input.at(raw_crates.size()) };
            this->_labels_map = this->produce_labels_map(labels);
            VectorPipe<std::string> raw_instructions { this->raw_instructions(input, raw_crates.size() + 2) };
            size_t columns_count = this->get_columns_count();
            this->parse_crates(raw_crates, columns_count);
            this->parse_instructions(raw_instructions);
        }

        std::string run() {
            return this->execute_instructions().message();
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
                char nospace = line[line.find_first_not_of(" ")];
                if(nospace != '[') break;
                result.push_back(line);
            }

            return result;
        }
        VectorPipe<std::string> raw_instructions(VectorPipe<std::string>& input, size_t offset) {
            return input.subvec(offset, input.size() - 1);
        }

        std::unordered_map<uint16_t, uint16_t> produce_labels_map(std::string& raw) {
            std::unordered_map<uint16_t, uint16_t> result;
            for(size_t index = 0; index < raw.size(); index++) {
                if(raw[index] != ' ') result[index] = (raw[index] - 0x30) - 1;
            }
            return result;
        }

        void parse_crates(VectorPipe<std::string>& raw, uint16_t columns_count) {
            auto raw_vec = raw.to_vec();
            this->_crates.set_size(columns_count);
            for(int64_t row_index = raw_vec.size() - 1; row_index >= 0; row_index--) {
                for(uint16_t col_index = 0; col_index < raw_vec[0].size(); col_index++) {
                    if(std::isalpha(raw_vec[row_index][col_index])) {
                        auto col = this->_labels_map[col_index];
                        this->_crates.push_crate(col, raw_vec[row_index][col_index]);
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

        uint16_t get_columns_count() {
            return this->_labels_map.size();
        }

        Game& execute_instructions() {
            for(auto& instr: this->_instructions.vec()) {
                this->_crates.move_stack(instr.quantity, instr.from, instr.to);
            }
            return *this;
        }

        std::string message() {
            return this->_crates.top_message();
        }
};


std::string part_one(VectorPipe<std::string>& input) {
    return Game(input).run();
}

std::string part_two(VectorPipe<std::string>& input) {
    (void) input;
    return "KEKW";
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