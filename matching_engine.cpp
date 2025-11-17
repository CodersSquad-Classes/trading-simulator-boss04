#include "matching_engine.h"
#include <chrono>

MatchingEngine::MatchingEngine(const std::string& symbol)
    : symbol(symbol), nextTimestamp(0), nextOrderId(1) {
    auto seed = static_cast<unsigned long>(
        std::chrono::high_resolution_clock::now().time_since_epoch().count()
    );
    rng.seed(seed);
}

Order MatchingEngine::generateRandomOrder() {
    std::uniform_int_distribution<int> sideDist(0, 1);
    std::uniform_int_distribution<int> qtyDist(10, 500);
    std::uniform_real_distribution<double> priceDist(-2.0, 2.0);

    bool isBuy = sideDist(rng) == 1;
    double basePrice = 100.0;
    double price = basePrice + priceDist(rng);
    if (price < 1.0) price = 1.0;

    Order o;
    o.id = nextOrderId++;
    o.stock = symbol;
    o.isBuy = isBuy;
    o.quantity = qtyDist(rng);
    o.price = price;
    o.timestamp = nextTimestamp++;
    return o;
}

std::vector<Trade> MatchingEngine::submit(Order order) {
    if (order.timestamp < 0) {
        order.timestamp = nextTimestamp++;
    }
    return book.addOrder(order);
}
