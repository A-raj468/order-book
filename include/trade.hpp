#pragma once

#include <cstdint>
struct Trade {
    uint64_t buyId;
    uint64_t sellId;
    uint64_t price;
    uint64_t quantity;
};
