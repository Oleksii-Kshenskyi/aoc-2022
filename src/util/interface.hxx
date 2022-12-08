#ifndef _INTERFACE_HXX_
#define _INTERFACE_HXX_

#include <cstdint>
#include <iomanip>
#include <vector>
#include <sstream>
#include <fstream>
#include <filesystem>
#include <iterator>

#include "func.hxx"

namespace fs = std::filesystem;

namespace util {

    enum class InputType {
        SampleInput,
        PuzzleInput
    };
    using IT = util::InputType;

    template <typename T>
    void show_result(InputType type, uint16_t aoc_year, uint16_t day, uint16_t part, T result) {
        std::cout << "AoC " << aoc_year;
        std::cout << ", Day " << std::setfill('0') << std::setw(2) << day;
        std::cout << ", Part " << part << ", ";

        switch(type) {
            case InputType::SampleInput:
                std::cout << "sample input";
                break;
            case InputType::PuzzleInput:
                std::cout << "actual puzzle input";
                break;
        }

        std::cout << ": " << result
                  << "." << std::endl;
    }

    class Input {
        public:
            Input(InputType type, uint16_t day) {
                this->_filepath = construct_filepath(type, day);
            }

            StringPipe str() {
                std::ifstream ifs{this->_filepath.string()};
                return StringPipe(std::string(std::istreambuf_iterator<char>{ifs}, {}));
            }
            VectorPipe<std::string> lines() {
                return this->str().split("\n");
            }
            VectorPipe<VectorPipe<std::string>> groups() {
                VectorPipe<VectorPipe<std::string>> result;
                std::vector<std::string> lines = this->lines().to_vec();

                bool constructing = true;
                VectorPipe<std::string> worker;
                for(auto& item: lines) {
                    if(item.empty()) {
                        constructing = false;
                    } else {
                        worker.add(std::move(item));
                        constructing = true;
                    }
                    if(!constructing && !worker.empty()) {
                        result.add(std::move(worker));
                        worker.clear();
                    }
                }

                if(constructing && !worker.empty()) result.add(std::move(worker));

                return result;
            }
            // std::vector<uint64_t> uints() {}

            static bool exists(InputType type, uint16_t day) {
                return fs::exists(construct_filepath(type, day));
            }
        
        private:
            fs::path _filepath;
            static fs::path construct_filepath(InputType type, uint16_t day) {
                fs::path the_path;
                the_path = INPUTS_PATH;

                std::string day_str;
                std::stringstream day_ss;
                day_ss << std::setfill('0') << std::setw(2) << day;
                day_str = day_ss.str();
                the_path /= day_str;

                std::string type_str;
                switch(type) {
                    case IT::SampleInput:
                        type_str = "sample";
                        break;
                    case IT::PuzzleInput:
                        type_str = "puzzle";
                        break;
                }
                the_path /= type_str += ".txt";

                return the_path;
            }
    };
}

using IT = util::InputType;



#endif