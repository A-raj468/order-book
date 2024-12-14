#include "orderBook.hpp"
#include "order.hpp"
#include "trade.hpp"

#include <cstdint>
#include <iostream>
#include <queue>
#include <stdexcept>

OrderBook::OrderBook() : id{1} {}

uint64_t OrderBook::addOrder(BOOKTYPE type, uint64_t price, uint64_t quantity) {
    Order order{id, type, price, quantity};
    id = id + 1;
    if (type == BOOKTYPE::BUY) {
        buyOrders.push(order);
    } else {
        sellOrders.push(order);
    }
    matchOrder();
    return order.id;
}

bool OrderBook::cancelOrder(uint64_t id) {
    // TODO: Implementation remaining
    throw std::runtime_error("Canceling of Orders is not supported yet");
}

void OrderBook::matchOrder() {
    while (!buyOrders.empty() && !sellOrders.empty()) {
        Order buy = buyOrders.top();
        Order sell = sellOrders.top();
        if (buy.price < sell.price) {
            break;
        }
        buyOrders.pop();
        sellOrders.pop();
        uint64_t price =
            buy.timestamp > sell.timestamp ? sell.price : buy.price;
        uint64_t quantity = buy.quantity;
        if (buy.quantity < sell.quantity) {
            quantity = buy.quantity;
            sell.quantity -= buy.quantity;
            sellOrders.push(sell);
        } else if (buy.quantity > sell.quantity) {
            quantity = sell.quantity;
            buy.quantity -= sell.quantity;
            sellOrders.push(buy);
        }
        Trade trade{buy.id, sell.id, price, quantity};
        onTrade(trade);
    }
}

void OrderBook::getOrderBook() {
    std::cout << "Order Book:\n";
    std::cout << "Buy Orders:\n";
    if (buyOrders.empty()) {
        std::cout << "- None\n";
    }
    auto buyOrders_copy = buyOrders;
    while (!buyOrders_copy.empty()) {
        Order top = buyOrders_copy.top();
        std::cout << "Order ID: " << top.id << ", $" << top.price << " : "
                  << top.quantity << " items";
        buyOrders_copy.pop();
    }
    std::cout << "Sell Orders:\n";
    if (sellOrders.empty()) {
        std::cout << "- None\n";
    }
    auto sellOrders_copy = sellOrders;
    while (!sellOrders_copy.empty()) {
        Order top = sellOrders_copy.top();
        std::cout << "Order ID: " << top.id << ", $" << top.price << " : "
                  << top.quantity << " items";
        sellOrders_copy.pop();
    }
}

Order OrderBook::queryOrder(uint64_t id) {
    // TODO: Implementation remaining
    throw std::runtime_error("Querying of Orders is not supported yet");
}

void OrderBook::onTrade(Trade trade) {
    std::cout << "Trade executed:\n";
    std::cout << "- Buy Order Id: " << trade.buyId << "\n";
    std::cout << "- Sell Order Id: " << trade.sellId << "\n";
    std::cout << "- Price: " << trade.price << "\n";
    std::cout << "- Quantity: " << trade.quantity << "\n";
}
