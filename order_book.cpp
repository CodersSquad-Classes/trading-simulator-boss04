#include "order_book.h"
#include <algorithm>

std::vector<Trade> OrderBook::addOrder(Order order) {
    std::vector<Trade> trades;

    if (order.isBuy) {
        while (order.quantity > 0 && !sellOrders.empty()) {
            Order bestSell = sellOrders.top();
            if (bestSell.price > order.price) {
                break;
            }

            sellOrders.pop();

            int tradedQty = std::min(order.quantity, bestSell.quantity);
            double tradePrice = bestSell.price;

            Trade t;
            t.stock = order.stock;
            t.price = tradePrice;
            t.quantity = tradedQty;
            t.buyId = order.id;
            t.sellId = bestSell.id;
            trades.push_back(t);

            order.quantity -= tradedQty;
            bestSell.quantity -= tradedQty;

            if (bestSell.quantity > 0) {
                sellOrders.push(bestSell);
            }
        }

        if (order.quantity > 0) {
            buyOrders.push(order);
        }
    } else {
        while (order.quantity > 0 && !buyOrders.empty()) {
            Order bestBuy = buyOrders.top();
            if (bestBuy.price < order.price) {
                break;
            }

            buyOrders.pop();

            int tradedQty = std::min(order.quantity, bestBuy.quantity);
            double tradePrice = bestBuy.price;

            Trade t;
            t.stock = order.stock;
            t.price = tradePrice;
            t.quantity = tradedQty;
            t.buyId = bestBuy.id;
            t.sellId = order.id;
            trades.push_back(t);

            order.quantity -= tradedQty;
            bestBuy.quantity -= tradedQty;

            if (bestBuy.quantity > 0) {
                buyOrders.push(bestBuy);
            }
        }

        if (order.quantity > 0) {
            sellOrders.push(order);
        }
    }

    return trades;
}

std::vector<Order> OrderBook::topBuys(int n) const {
    std::vector<Order> result;
    auto copy = buyOrders;

    while (!copy.empty() && (int)result.size() < n) {
        result.push_back(copy.top());
        copy.pop();
    }
    return result;
}

std::vector<Order> OrderBook::topSells(int n) const {
    std::vector<Order> result;
    auto copy = sellOrders;

    while (!copy.empty() && (int)result.size() < n) {
        result.push_back(copy.top());
        copy.pop();
    }
    return result;
}
