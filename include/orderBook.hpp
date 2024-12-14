#include "order.hpp"
#include "trade.hpp"

#include <cstdint>
#include <functional>
#include <queue>
#include <string>
#include <vector>

class OrderBook {
  public:
    OrderBook();

    uint64_t addOrder(BOOKTYPE type, uint64_t price, uint64_t quantity);
    bool cancelOrder(uint64_t id);
    void matchOrder();
    std::string getOrderBook();
    Order queryOrder(uint64_t id);
    std::string onTrade(Trade trade);

  private:
    uint64_t id;
    std::priority_queue<Order, std::vector<Order>, std::less<Order>> buyOrders;
    std::priority_queue<Order, std::vector<Order>, std::greater<Order>>
        sellOrders;
};
