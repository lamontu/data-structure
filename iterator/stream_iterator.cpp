
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

//#include <iosfwd>

const std::string WHITESPACE = " \n\r\t\f\v";

std::string ltrim(const std::string& s)
{
    size_t start = s.find_first_not_of(WHITESPACE);
    return (start == std::string::npos) ? "" : s.substr(start);
}

std::string rtrim(const std::string& s)
{
    size_t end = s.find_last_not_of(WHITESPACE);
    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}

std::string trim(const std::string& s) {
    return rtrim(ltrim(s));
}

class Solution {

public:
    Solution(std::istream& in_stream) : file_(in_stream) {

    }

    class iterator {
    public:
        iterator(std::istream& file) : file_(&file), value_(0) {
            next();
        }
        iterator() : file_(nullptr), value_(0) {

        }

        //const std::string& operator*() const {
        //    return line_;
        //}

        int operator*() const {
            return value_;
        }

        iterator& operator++() {
            next();
            return *this;
        }

        bool operator!=(const iterator& other) const {
            return file_ != other.file_;
        }

    private:
        void next() {
            if (file_->eof()) {
                file_ = nullptr;
                return;
            }
            std::string line;
            int num = 0;
            do {
                std::getline(*file_, line);

            } while (!line2Int(line, num));
            value_ = num;
        }
        
        bool line2Int(const std::string line, int& value) {
            std::string trimLine = trim(line);
            size_t size = trimLine.size();
            if (size == 0)
                return false;
            int count = 0;
            bool negative = false;
            int i = 0;
            if (trimLine[0] == '+') {
                ++i;
            }
            else if (trimLine[0] == '-') {
                ++i;
                negative = true;
            }
            long long res = 0;
            for (; i < size; ++i) {
                if (trimLine[i] >= '0' && trimLine[i] <= '9') {
                    char digit = trimLine[i] - '0';
                    res = res * 10 + (int)digit;
                }
                else {
                    break;
                }
            }
            if (i < size || res > 1000000000) {
                return false;
            }
            value = static_cast<int>(negative ? (res * -1) : res);
            return true;
        }
        std::istream* file_;
        //std::string line_;
        int value_;
    };

    iterator begin() {
        return iterator(file_);
    }
    iterator end() {
        return iterator{};
    }

private:

private:
    std::istream& file_;
};


//137
//- 104
//2 58
//+ 0
//++3
//+ 1
//23.9
//2000000000
//- 0
//five
//- 1
//
//
//[137, -104, 0, 1, 0, -1]

int main()
{
    std::ifstream infile(R"(./input.txt)");
    Solution sol(infile);
    for (Solution::iterator it = sol.begin(); it != sol.end(); ++it) {
        int x = *it;
        std::cout << x << std::endl;
        
    }
    std::cout << "Hello World!\n";
}