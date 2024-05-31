#include <cstring>
#include <iostream>

extern "C" __declspec(dllexport) bool CharSearch(const char* inputString, const char* searchChars) {
    int len = strlen(searchChars);
    for (int i = 0; i < len; i++) {
        const char* found = strchr(inputString, searchChars[i]);
        if (!found) {
            return false;
        }
    }
    return true;
}
