#pragma once
#include "order.h"
#include <queue>
#include <vector>

struct Trade {
    std::string stock;
    double price;
    int quantity;
    int buyId;
    int sellId;
};

struct BuyComparator {
    bool operator()(const Order& a, const Order& b) const {
        if (a.price == b.price) {
            return a.timestamp > b.timestamp; // later = lower priority
        }
        return a.price < b.price; // lower price = lower priority
    }
};

struct SellComparator {
    bool operator()(const Order& a, const Order& b) const {
        if (a.price == b.price) {
            return a.timestamp > b.timestamp; // later = lower priority
        }
        return a.price > b.price; // higher price = lower priority
    }
};

class OrderBook {
public:
    std::vector<Trade> addOrder(Order order);

    std::vector<Order> topBuys(int n) const;
    std::vector<Order> topSells(int n) const;

private:
    std::priority_queue<Order, std::vector<Order>, BuyComparator> buyOrders;
    std::priority_queue<Order, std::vector<Order>, SellComparator> sellOrders;
};
