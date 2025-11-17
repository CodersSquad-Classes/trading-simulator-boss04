#pragma once
#include <string>

struct Order {
    int id;
    std::string stock;
    double price;
    int quantity;
    bool isBuy;        // true = buy, false = sell
    long long timestamp;
};
