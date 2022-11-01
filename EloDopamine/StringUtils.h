#pragma once
#include <string>
#include <algorithm>
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
}
