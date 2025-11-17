#pragma once
#include "matching_engine.h"
#include <vector>

class TerminalUI {
public:
    explicit TerminalUI(int rowsToShow);

    void draw(const MatchingEngine& engine, const std::vector<Trade>& lastTrades);

private:
    int rows;
    void clearScreen() const;
};
