# Trading Simulator — DOCS

## 1. Introduction

This project implements a Continuous Limit Order Book (CLOB) for a simple stock trading simulator.  
The goal is to simulate how real stock exchanges match limit orders from buyers and sellers using:

- Price priority: better prices first.
- Time priority: older orders first when prices are equal.

The system runs in the terminal and shows a small dashboard with:

- Top buy orders.
- Top sell orders.
- Recently executed trades.

Everything is implemented in C++ using priority queues.

---

## 2. Research on Stock Exchanges

Modern stock exchanges use electronic trading systems instead of floor trading.

A limit order is:

- Buy: order to buy a quantity at or below a given price.
- Sell: order to sell a quantity at or above a given price.

A Continuous Limit Order Book (CLOB):

- Keeps two lists (books):
  - Bids (buy orders)
  - Asks (sell orders)
- Orders are ranked:
  - By price (best prices at the top)
  - Then by time (first order in when prices are equal)
- When a new order arrives, the engine:
  - Checks if it can match against existing orders on the other side.
  - If compatible, trades are executed immediately.
  - Remaining quantity (if any) stays in the book.

This simulator is a simplified version of the CLOBs used in real systems such as electronic communication networks (ECNs).

---

## 3. Software Design and Implementation

### 3.1 Main Components

- `Order`
  - Basic data for an order (id, stock, price, quantity, side, timestamp).

- `OrderBook`
  - Stores orders in two priority queues:
    - `buyOrders`: best highest price first, then earliest time.
    - `sellOrders`: best lowest price first, then earliest time.
  - Matches new orders against the opposite side.

- `MatchingEngine`
  - Wraps a single `OrderBook` for one symbol (e.g., `ACME`).
  - Generates random orders to simulate traders.
  - Submits orders to the book and returns executed trades.

- `TerminalUI`
  - Clears the screen and prints:
    - Top N buy orders.
    - Top N sell orders.
    - Last trades.
  - Uses ANSI colors (green for buys, red for sells, cyan for headers).

- `main`
  - Main loop:
    - Generate random order.
    - Submit to engine.
    - Update and redraw UI.
    - Sleep for a short delay.

### 3.2 Data Structures

**Buy priority queue:**

```cpp
std::priority_queue<Order, std::vector<Order>, BuyComparator> buyOrders;

struct BuyComparator {
    bool operator()(const Order& a, const Order& b) const {
        if (a.price == b.price) {
            return a.timestamp > b.timestamp; // older order wins
        }
        return a.price < b.price; // higher price gets higher priority
    }
};

### Sell priority queue:

````
std::priority_queue<Order, std::vector<Order>, SellComparator> sellOrders;

struct SellComparator {
    bool operator()(const Order& a, const Order& b) const {
        if (a.price == b.price) {
            return a.timestamp > b.timestamp; // older order wins
        }
        return a.price > b.price; // lower price gets higher priority
    }
};

## 3.3 Matching Algorithm (High-Level)

### For a new buy order:

While there is quantity remaining and there are sell orders:

Take the best sell (top of sellOrders).

If bestSell.price > buy.price, stop (no more matches).

Otherwise:

tradedQty = min(buy.quantity, bestSell.quantity).

Create a Trade record.

Decrease quantities.

Remove orders that reach zero quantity from the queue.

If the buy order still has quantity left, push it into buyOrders.

For a new sell order, the algorithm is symmetric using buyOrders.

## 4. Conclusions and Learnings
Working on this project helped me understand how a real-time trading system can be modeled with basic data structures like priority queues. I learned how price-time priority is implemented in code using custom comparators, and how limit orders are matched step by step in a continuous limit order book. I also practiced building a simple text-based UI using ANSI escape codes, which made the simulator feel more dynamic. Overall, this assignment connected concepts from financial markets with core topics from data structures in C++.
