#pragma once
#include "order_book.h"
#include <random>
#include <string>
#include <vector>

class MatchingEngine {
public:
    MatchingEngine(const std::string& symbol);

    Order generateRandomOrder();
    std::vector<Trade> submit(Order order);

    const OrderBook& getBook() const { return book; }
    const std::string& getSymbol() const { return symbol; }

private:
    std::string symbol;
    OrderBook book;
    long long nextTimestamp;
    int nextOrderId;
    std::mt19937 rng;
};
