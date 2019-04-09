#pragma once
#include <string>
#include <unordered_map>
#include "../libaw101/ui/backend/tools/Timer.h"
#include "Synth.h"
#include <algorithm>
#include <numeric>
#include "foo/Average.h"
#include "foo/RingBuffer.h"

class TestModel {
protected:

public:
    TestModel() {
        foo = 0;
        str = "nibba";
    }
    int foo;
    std::string str;
    Timer timer;
    Timer loopTime;
    Average<50, long> m_average;
    std::unordered_map<std::string, std::string> generic_storage;
    Synth m_synth;
};


