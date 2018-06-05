#ifndef SHMUP_STRINGUTILS_H
#define SHMUP_STRINGUTILS_H

#include <string>
#include <algorithm>

namespace StringUtils {
    using namespace std;

    static inline bool charsIgnoreCase(char a, char b) {
        return (toupper(a) == toupper(b));
    }

    static inline bool equalsIgnoreCase(const string &s1, const string &s2) {
        return ((s1.size() == s2.size()) && equal(s1.begin(), s1.end(), s2.begin(), charsIgnoreCase));
    }

    static inline string trim(string &str) {
        str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
        str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
        return str;
    }
}


#endif //SHMUP_STRINGUTILS_H
