#include "orderBook.hpp"
#include "order.hpp"
#include "trade.hpp"

#include <cstdint>
#include <iostream>
#include <queue>
#include <sstream>
#include <stdexcept>
#include <string>

OrderBook::OrderBook(std::ostream &out) : out{out}, id{1} {}

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
            buyOrders.push(buy);
        }
        Trade trade{buy.id, sell.id, price, quantity};
        onTrade(trade);
    }
}

std::string OrderBook::getOrderBook() {
    std::ostringstream out;
    out << "Order Book:\n";
    out << "Buy Orders:\n";
    if (buyOrders.empty()) {
        out << "- None\n";
    }
    auto buyOrders_copy = buyOrders;
    while (!buyOrders_copy.empty()) {
        Order top = buyOrders_copy.top();
        out << "- Order ID: " << top.id << ", $" << top.price << " : "
            << top.quantity << " items\n";
        buyOrders_copy.pop();
    }
    out << "Sell Orders:\n";
    if (sellOrders.empty()) {
        out << "- None\n";
    }
    auto sellOrders_copy = sellOrders;
    while (!sellOrders_copy.empty()) {
        Order top = sellOrders_copy.top();
        out << "- Order ID: " << top.id << ", $" << top.price << " : "
            << top.quantity << " items\n";
        sellOrders_copy.pop();
    }
    return out.str();
}

Order OrderBook::queryOrder(uint64_t id) {
    // TODO: Implementation remaining
    throw std::runtime_error("Querying of Orders is not supported yet");
}

void OrderBook::onTrade(Trade trade) {
    out << "Trade executed:\n";
    out << "- Buy Order Id: " << trade.buyId << "\n";
    out << "- Sell Order Id: " << trade.sellId << "\n";
    out << "- Price: " << trade.price << "\n";
    out << "- Quantity: " << trade.quantity << "\n";
}
