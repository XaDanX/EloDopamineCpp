#pragma once
#include <string>
#include <algorithm>
#include <random>

inline namespace StringUtils {
    inline bool IsASCII(const char *buff, int maxSize) {
        for (int i = 0; i < maxSize; ++i) {
            if (buff[i] == 0)
                return true;
            if ((unsigned char) buff[i] > 127)
                return false;
        }
        return true;
    }

    inline std::string ToLower(std::string str) {
        std::string strLower;
        strLower.resize(str.size());

        std::transform(str.begin(),
                       str.end(),
                       strLower.begin(),
                       ::tolower);

        return strLower;
    }

    inline std::string RandomString(std::string::size_type length) {
        static auto& chrs = "0123456789"
            "abcdefghijklmnopqrstuvwxyz"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

        thread_local static std::mt19937 rg{ std::random_device{}() };
        thread_local static std::uniform_int_distribution<std::string::size_type> pick(0, sizeof(chrs) - 2);

        std::string s;

        s.reserve(length);

        while (length--)
            s += chrs[pick(rg)];

        return s;
    }
}
