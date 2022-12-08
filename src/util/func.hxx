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