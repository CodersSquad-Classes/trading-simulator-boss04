#include "matching_engine.h"
#include "ui.h"
#include <thread>
#include <chrono>

int main() {
    MatchingEngine engine("ACME");
    TerminalUI ui(10);

    std::vector<Trade> lastTrades;

    while (true) {
        Order o = engine.generateRandomOrder();
        auto trades = engine.submit(o);
        if (!trades.empty()) {
            lastTrades = trades;
        }

        ui.draw(engine, lastTrades);

        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }

    return 0;
}
