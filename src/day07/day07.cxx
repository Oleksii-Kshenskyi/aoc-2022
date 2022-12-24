#include <iostream>
#include <functional>
#include <algorithm>
#include <unordered_map>
#include <cctype>
#include <stdexcept>

#include "interface.hxx"

using util::VectorPipe;
using util::StringPipe;

class Path {
    public:
        Path(): _dir_path("/") {}
        Path& up() {
            if(this->_dir_path == "/") return *this;
            uint16_t last_sep = this->_dir_path.find_last_of('/');
            if(last_sep == 0) {
                this->_dir_path = "/";
                return *this;
            }

            this->_dir_path.erase(this->_dir_path.begin() + last_sep - 1, this->_dir_path.end());
            return *this;
        }
        Path& into(std::string& folder) {
            if(folder == "/") {
                this->_dir_path = "/";
                return *this;
            }
            if(this->_dir_path == "/") {
                this->_dir_path += folder;
                return *this;
            }
            this->_dir_path += std::string("/") + folder;
            return *this;
        }
        std::string path() { return this->_dir_path; };

        uint16_t max_level() {
            return std::count(this->_dir_path.begin(), this->_dir_path.end(), '/');
        }

        std::string level(uint16_t level_num) {
            if(level_num == 0) return "/";
            auto level_map = this->level_map();
            uint16_t start = level_map[level_num - 1] + 1;
            uint16_t count = level_map[level_num] - start;
            std::string level_name = this->_dir_path.substr(start, count);
            return level_name;
        }
    private:
        std::string _dir_path;

        std::unordered_map<uint16_t, uint16_t> level_map() {
            std::unordered_map<uint16_t, uint16_t> result;
            uint16_t level = 0;
            for(size_t index = 0; index < this->_dir_path.size(); index++) {
                if(this->_dir_path[index] == '/') result[level] = index;
                level++;
            }
            result[level] = this->_dir_path.size();
            return result;
        }
};

enum class FileType {
    Dir,
    File
};

class FileNode {
    public:
        FileNode(): name("/"), children(), type(FileType::Dir), size(0) {}

        void add_file(std::vector<std::string>& entity) {
            FileNode new_entity;
            new_entity.name = entity[1];
            if(entity[0] == "dir") new_entity.type = FileType::Dir;
            else {
                new_entity.type = FileType::File;
                new_entity.size = std::stoull(entity[0]);
            }
            this->children.push_back(new_entity);
        }

        FileNode& seek(Path& seek_path) {
            FileNode* found = this;
            if(seek_path.path() == "/") return *found;
            for(uint16_t cur_level = 1; cur_level <= seek_path.max_level(); cur_level++) {
                std::string looking_for_name = seek_path.level(cur_level);
                if(found != nullptr) {
                    auto found_it = std::find_if(found->children.begin(), found->children.end(), [=](auto& c){ return c.name == looking_for_name; });
                    if(found_it != found->children.end()) found = &(*found_it);
                }
            }
            if(found == nullptr) {
                std::cout << "WARNING: seek for path '" << seek_path.path() << "' resulted in nullptr." << std::endl;
            }
            return *found;
        }


        void ls_file() {
            std::cout << "FILE '" << this->name << "', size: " << this->size << "B;" << std::endl;
        }
        void ls_dir() {
            std::cout << "=> DIR '" << this->name << "':" << std::endl;
            for(auto& child: this->children) {
                std::cout << "\t";
                if(child.type == FileType::Dir) child.ls_dir();
                else child.ls_file();
            }
            std::cout << "=> END DIR '" << this->name << "'." << std::endl << std::endl;
        }
        void ls() {
            if(this->type == FileType::Dir) this->ls_dir();
            else this->ls_file();
        }

        std::string name;
        std::vector<FileNode> children;
        FileType type;
        uint64_t size;
};

struct FileSystem {
    Path current_directory;
    FileNode root;
};

class Computer {
    public:
        Computer(VectorPipe<std::string>& input) {
            for(auto& line: input.to_vec()) {
                auto line_split = StringPipe(line).split(" ").to_vec();
                if(line_split[0] == "$") this->execute_command(line_split);
                else {
                    FileNode& add_here = this->_fs.root.seek(this->_fs.current_directory);
                    add_here.add_file(line_split);
                }
            }
        }

        VectorPipe<uint64_t> dir_sizes() {
            std::vector<uint64_t> sizes;
            uint64_t root_size = 0;
            for(auto& child: this->_fs.root.children) {
                if(child.type == FileType::File) root_size += this->size_of_file(child);
                else if(child.type == FileType::Dir) {
                    uint64_t dir_size = this->size_of_dir(child, sizes);
                    root_size += dir_size;
                    sizes.push_back(dir_size);
                }
            }
            sizes.push_back(root_size);
            return VectorPipe{sizes};
        }
    private:
        FileSystem _fs;

        void execute_command(std::vector<std::string>& command_vec) {
            if(command_vec[1] == "cd") {
                if(command_vec[2] == "..") this->_fs.current_directory.up();
                else this->_fs.current_directory.into(command_vec[2]);
            } else if(command_vec[1] == "ls") {
            } else {
                std::cout << "ERROR: UNKNOWN COMMAND '" << command_vec[1] << "'?!" << std::endl;
                throw std::logic_error("Computer::execute_command(): UNKNOWN COMMAND");
            }
        }

        uint64_t size_of_file(FileNode& file) {
            if(file.type != FileType::File) {
                std::string err = "ERROR: Computer::size_of_file() got a FileNode that's not a file!";
                std::cout << err << std::endl;
                throw err;
            }

            return file.size;
        }

        uint64_t size_of_dir(FileNode& dir, std::vector<uint64_t>& sizes) {
            if(dir.type != FileType::Dir) {
                std::string err = "ERROR: Computer::size_of_dir() got a FileNode that's not a dir!";
                std::cout << err << std::endl;
                throw err;
            }

            uint64_t the_size = 0;
            for(auto& node: dir.children) {
                if(node.type == FileType::File) the_size += this->size_of_file(node);
                else if(node.type == FileType::Dir) {
                    uint64_t dir_size = this->size_of_dir(node, sizes);
                    the_size += dir_size;
                    sizes.push_back(dir_size);
                }
            }
            
            return the_size;
        }
};


uint64_t part_one(VectorPipe<std::string>& input) {
    auto sizes {Computer(input)
        .dir_sizes()};
    return sizes
        .filter([](auto x) { return x <= 100000; })
        .sum();
}

uint64_t part_two(VectorPipe<std::string>& input) {
    (void) input;
    return 3;
}

int main() {
    if(util::Input::exists(IT::SampleInput, 7)) {
        auto input = util::Input(IT::SampleInput, 7).lines();
        util::show_result(IT::SampleInput, 2022, 7, 1, part_one(input));
        util::show_result(IT::SampleInput, 2022, 7, 2, part_two(input));
    } else {
        std::cout << "Sample input for Day 7 does not exist." << std::endl;
    }

    if(util::Input::exists(IT::PuzzleInput, 7)) {
        auto input = util::Input(IT::PuzzleInput, 7).lines();
        util::show_result(IT::PuzzleInput, 2022, 7, 1, part_one(input));
        util::show_result(IT::PuzzleInput, 2022, 7, 2, part_two(input));
    } else {
        std::cout << "Puzzle input for Day 7 does not exist." << std::endl;
    }
    return 0;
}