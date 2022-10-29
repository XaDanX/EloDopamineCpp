#pragma once
#include <string>
#include <algorithm>
namespace StringUtils {
    bool IsASCII(const char *buff, int maxSize) {
        for (int i = 0; i < maxSize; ++i) {
            if (buff[i] == 0)
                return true;
            if ((unsigned char) buff[i] > 127)
                return false;
        }
        return true;
    }

    std::string ToLower(std::string str) {
        std::string strLower;
        strLower.resize(str.size());

        std::transform(str.begin(),
                       str.end(),
                       strLower.begin(),
                       ::tolower);

        return strLower;
    }
}
