#include "Utils.h"
#include <iostream>

// split 함수
std::vector<std::string> UtilsSplit(std::string str, std::string del) {
    std::vector<std::string> ret;

    char *next_s;
    char *s = strtok_r(const_cast<char*>(str.c_str()), del.c_str(), &next_s);

    while (s) {
        ret.push_back(s);

        s = strtok_r(nullptr, del.c_str(), &next_s);
    }
    return (ret);
}

// 유효성 검사 부분 기능에 넣기
bool UtilsStringIsNumber(const std::string &str) {
    if (str.size() == 0) {
        return (false);
    }
    for (auto & ch : str) {
        // if ch is numeric char => none-zero
        if (std::isdigit(static_cast<unsigned char>(ch)) == 0) {
            std::cout << "not number\n";
            return (false);
        }
    }
    return (true);
}
