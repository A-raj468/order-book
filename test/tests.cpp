#include <iostream>
#include <order.hpp>
#include <orderBook.hpp>

#define ASSERT(condition, msg)                                                 \
    do {                                                                       \
        if (!(condition)) {                                                    \
            std::cerr << "Assertion failed: " << msg << "\n"                   \
                      << "File: " << __FILE__ << "\n"                          \
                      << "Line: " << __LINE__ << "\n"                          \
                      << "Function: " << __func__ << "\n";                     \
            std::abort();                                                      \
        }                                                                      \
    } while (false)

const std::string GREEN_TEXT = "\033[32m";
const std::string RESET_TEXT = "\033[0m";

void testAddOrders() {
    std::cout << "Running test: testAddOrders\n";
    OrderBook orderBook;
    std::string book;
    book = orderBook.getOrderBook();
    bool init = (book == "Order Book:\n"
                         "Buy Orders:\n"
                         "- None\n"
                         "Sell Orders:\n"
                         "- None\n");
    ASSERT(init, "Orderbook initial details are wrong");
    orderBook.addOrder(BOOKTYPE::BUY, 100, 10);
    orderBook.addOrder(BOOKTYPE::SELL, 110, 5);
    book = orderBook.getOrderBook();
    bool final = (book == "Order Book:\n"
                          "Buy Orders:\n"
                          "- Order ID: 1, $100 : 10 items\n"
                          "Sell Orders:\n"
                          "- Order ID: 2, $110 : 5 items\n");
    ASSERT(final, "Orderbook final details are wrong");
    std::cout << GREEN_TEXT << "testAddOrders Passed!" << RESET_TEXT << "\n";
}

void testMatchOrders() {
    std::cout << "Running test: testMatchOrders\n";
    OrderBook orderBook;
    std::string book;
    book = orderBook.getOrderBook();
    bool init = (book == "Order Book:\n"
                         "Buy Orders:\n"
                         "- None\n"
                         "Sell Orders:\n"
                         "- None\n");
    ASSERT(init, "Orderbook initial details are wrong");
    orderBook.addOrder(BOOKTYPE::BUY, 100, 10);
    orderBook.addOrder(BOOKTYPE::SELL, 95, 5);
    book = orderBook.getOrderBook();
    bool final = (book == "Order Book:\n"
                          "Buy Orders:\n"
                          "- Order ID: 1, $100 : 5 items\n"
                          "Sell Orders:\n"
                          "- None\n");
    ASSERT(final, "Orderbook final details are wrong");
    std::cout << GREEN_TEXT << "testMatchOrders Passed!" << RESET_TEXT << "\n";
}

int main() {
    testAddOrders();
    testMatchOrders();
    return 0;
}
