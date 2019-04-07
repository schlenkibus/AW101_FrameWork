#pragma once
#include <string>

class KeyEventTarget {
public:
    virtual void onKeyDown(const std::string& key) = 0;
    virtual void onKeyUp(const std::string& key) = 0;
};


