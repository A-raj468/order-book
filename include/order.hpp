#pragma once

#include <chrono>
#include <cstdint>

enum class BOOKTYPE {
    BUY,
    SELL,
};

struct Order {
    Order(uint64_t id, BOOKTYPE type, uint64_t price, uint64_t quantity)
        : id{id}, type{type}, price{price}, quantity{quantity} {
        timestamp = std::chrono::duration_cast<std::chrono::nanoseconds>(
                        std::chrono::system_clock::now().time_since_epoch())
                        .count();
    }
    uint64_t id;
    BOOKTYPE type;
    uint64_t price;
    uint64_t quantity;
    uint64_t timestamp;

    bool operator<(const Order &other) {
        return (price < other.price) ||
               (price == other.price && timestamp < other.timestamp);
    }

    bool operator>(const Order &other) {
        return (price > other.price) ||
               (price == other.price && timestamp > other.timestamp);
    }
};
