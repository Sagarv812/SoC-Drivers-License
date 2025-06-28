#pragma once
#include <stdint.h>
#include "Memory.hpp"
#include "Config.hpp"
#include <string>

struct MMU {
    public:
    MMU(Memory& memory, Config& cfg);
    void storeVal(uint64_t vaddr, uint64_t val); // we expose only these objects and methods to the user
    uint64_t loadVal(uint64_t vaddr);

    private:
    Memory& mem;
    Config& config;
    uint64_t translate(uint64_t vaddr);
};

