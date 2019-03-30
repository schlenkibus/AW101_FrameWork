#include "UIID.h"

int UIID::last{0};

UIID::UIID() {
    id = "UIID:" + std::to_string(++UIID::last);
}

UIID::UIID(const std::string &str) {
    id = str;
}
