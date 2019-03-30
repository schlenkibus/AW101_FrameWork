#pragma once
#include <string>

class UIID {
public:
    UIID();
    UIID(const std::string& str);
    std::string id;
    static int last;
};
