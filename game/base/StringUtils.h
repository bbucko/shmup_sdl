#ifndef SHMUP_STRINGUTILS_H
#define SHMUP_STRINGUTILS_H

#include <string>

namespace StringUtils {

    static inline bool charsIgnoreCase(char a, char b) {
        return (toupper(a) == toupper(b));
    }

    static inline bool equalsIgnoreCase(const std::string &s1, const std::string &s2) {
        return ((s1.size() == s2.size()) && std::equal(s1.begin(), s1.end(), s2.begin(), charsIgnoreCase));
    }
}


#endif //SHMUP_STRINGUTILS_H
