#include "ui.h"
#include <iostream>
#include <iomanip>

TerminalUI::TerminalUI(int rowsToShow) : rows(rowsToShow) {}

void TerminalUI::clearScreen() const {
    std::cout << "\033[2J\033[H";
}

void TerminalUI::draw(const MatchingEngine& engine, const std::vector<Trade>& lastTrades) {
    clearScreen();

    const std::string RESET = "\033[0m";
    const std::string RED = "\033[31m";
    const std::string GREEN = "\033[32m";
    const std::string CYAN = "\033[36m";
    const std::string YELLOW = "\033[33m";

    const OrderBook& book = engine.getBook();
    auto buys = book.topBuys(rows);
    auto sells = book.topSells(rows);

    std::cout << CYAN << "=== CONTINUOUS LIMIT ORDER BOOK (CLOB) ===" << RESET << "\n";
    std::cout << "Symbol: " << YELLOW << engine.getSymbol() << RESET << "\n\n";

    std::cout << CYAN
              << std::left << std::setw(8) << "ID"
              << std::setw(10) << "SIDE"
              << std::setw(10) << "QTY"
              << std::setw(10) << "PRICE"
              << RESET << "\n";

    std::cout << "----------------------------------------\n";

    std::cout << GREEN << "BUY ORDERS (best price on top)\n" << RESET;
    for (const auto& o : buys) {
        std::cout << std::left << std::setw(8) << o.id
                  << std::setw(10) << "BUY"
                  << std::setw(10) << o.quantity
                  << std::setw(10) << std::fixed << std::setprecision(2) << o.price
                  << "\n";
    }
    if (buys.empty()) {
        std::cout << "(no buy orders)\n";
    }

    std::cout << "\n";

    std::cout << RED << "SELL ORDERS (best price on top)\n" << RESET;
    for (const auto& o : sells) {
        std::cout << std::left << std::setw(8) << o.id
                  << std::setw(10) << "SELL"
                  << std::setw(10) << o.quantity
                  << std::setw(10) << std::fixed << std::setprecision(2) << o.price
                  << "\n";
    }
    if (sells.empty()) {
        std::cout << "(no sell orders)\n";
    }

    std::cout << "\n" << CYAN << "Last matches:\n" << RESET;
    if (lastTrades.empty()) {
        std::cout << "(no trades yet)\n";
    } else {
        for (const auto& t : lastTrades) {
            std::cout << "Trade " << t.stock
                      << " qty=" << t.quantity
                      << " price=" << std::fixed << std::setprecision(2) << t.price
                      << " [buyId=" << t.buyId
                      << ", sellId=" << t.sellId << "]\n";
        }
    }

    std::cout << "\nPress Ctrl+C to stop.\n";
}
