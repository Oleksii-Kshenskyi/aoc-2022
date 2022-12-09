#ifndef _FUNC_HXX_
#define _FUNC_HXX_

#include <string>
#include <vector>
#include <regex>
#include <functional>
#include <algorithm>

namespace util {
    template<typename T>
    class VectorPipe {
        public:
            VectorPipe(const std::vector<T>& vec): _vec(vec) {};
            VectorPipe(): _vec() {};
            VectorPipe<T>& add(T&& new_elem) {
                this->_vec.emplace_back(new_elem);
                return *this;
            }
            VectorPipe<T>& copy_add(const T& copied_elem) {
                this->_vec.push_back(copied_elem);
                return *this;
            
            }
            VectorPipe<T>& sort_descending() {
                std::sort(this->_vec.begin(), this->_vec.end(), std::greater<T>());
                return *this;
            }

            void show() {
                for(const auto& item: this->_vec)
                    std::cout << item << "\n";
            };

            std::vector<T> to_vec() { return this->_vec; }
            bool empty() { return this->_vec.empty(); }
            size_t size() { return this->_vec.size(); }
            VectorPipe<T>& clear() {
                this->_vec.clear();
                return *this;
            }
            T& last() { return this->_vec.back(); }
            T& first() {return this-> vec.first(); }

            template<typename N>
            VectorPipe<N> map(const std::function<N(T)>& f) {
                VectorPipe<N> result;
                for(const auto& item: _vec)
                    result.copy_add(f(item));
                return result;
            }
            VectorPipe<T> take(uint64_t how_many) {
                return VectorPipe<T>(std::vector<T>(this->_vec.begin(), this->_vec.begin() + how_many));
            }
            VectorPipe<T> subvec(size_t begin, size_t end) {
                size_t end_offset = this->_vec.size() - end - 1;
                return VectorPipe<T>(std::vector<T>(this->_vec.begin() + begin, this->_vec.end() - end_offset));
            }
            VectorPipe<VectorPipe<T>> partition(size_t part_size) {
                VectorPipe<VectorPipe<T>> result;

                VectorPipe<T> group;
                for(size_t index = 0; index < this->_vec.size(); index++) {
                    group.copy_add(this->_vec[index]);

                    if(group.size() == part_size || index == this->_vec.size() - 1) {
                        result.add(std::move(group));
                        group.clear();
                    }
                }

                return result;
            }

            template <typename F>
            uint64_t count(const F& f) {
                return std::count_if(this->_vec.begin(), this->_vec.end(), f);
            }

            T reduce(const std::function<T(T, T)>& f, T init_value) {
                T acc = init_value;

                for(const auto& item: this->_vec)
                    acc = f(acc, item);

                return acc;
            }

            T sum() {
                return this->reduce([](auto a, auto b) { return a + b; }, 0);
            }

            T max() {
                return *std::max_element(this->_vec.begin(), this->_vec.end());
            }

            T at(size_t index) { return this->_vec[index]; }

        private:
            std::vector<T> _vec;
    };

    class StringPipe {
        public:
            StringPipe(const std::string& str): _str(str) {}
            VectorPipe<std::string> split(const std::string& separators) {
                std::regex rgx{std::string("[") + separators + std::string("]")};
                return VectorPipe<std::string>(
                    std::vector<std::string>(
                        std::sregex_token_iterator(this->_str.begin(), this->_str.end(), rgx, -1),
                        std::sregex_token_iterator()
                ));
            }
            std::string to_string() { return this->_str; }

        private:
            std::string _str;
    };
}

#endif