#pragma once
#include <vector>
#include <stdint.h>

struct Config {
    int addressWidth;
    int pageSize;
    int pageTableLevels;
    std::vector<int> bitsPerLevel;
    uint64_t systemMemory;
};

