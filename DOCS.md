# Trading Simulator — Documentation

## 1. Introduction

This project implements a **Continuous Limit Order Book (CLOB)** for a simple stock trading simulator.  
The goal is to simulate how real stock exchanges match **limit orders** from buyers and sellers using:

- **Price priority**: better prices are matched first.
- **Time priority**: older orders are executed before newer ones when prices are equal.

The simulator runs directly in the terminal and displays:

- The top buy orders.
- The top sell orders.
- Recently executed trades.

All logic is implemented in C++ using **priority queues**, which makes the behavior relatively realistic compared to simplified market models.

---

## 2. Research on Stock Exchanges

Modern Exchanges such as NASDAQ and NYSE operate using **electronic limit order books**, not floor trading like in the past.  
The trading model is simple in theory but complex in practice:

### **Limit Orders**
- **Buy Limit:** Buy *at or below* a specified price.  
- **Sell Limit:** Sell *at or above* a specified price.

### **CLOB — Continuous Limit Order Book**
A CLOB keeps two dynamic lists:

- **Bids (Buy Orders)**  
- **Asks (Sell Orders)**  

Orders are sorted using:

1. **Price Priority**  
   - Highest bid first  
   - Lowest ask first  

2. **Time Priority**  
   - Earlier orders at the same price get matched first  

When a compatible order arrives, the matching engine executes a trade:

- Quantity traded = minimum of both order quantities  
- Remaining parts of orders (if any) stay in the book  

This simulator is a simplified model inspired by actual electronic trading systems (ECNs) used by modern exchanges.

---

## 3. Software Design and Implementation

Below is the high-level design of the system, split into components.

---

### 3.1 Architecture Diagram

```text
                        ┌──────────────────────┐
                        │     MatchingEngine    │
                        │  - generates orders   │
                        │  - submits to book    │
                        └───────────┬──────────┘
                                    │
                                    │
                        ┌──────────────────────┐
                        │      OrderBook        │
                        │  Buy PQ ←──────────┐  │
                        │                    │  │
                        │  Sell PQ────────→  │  │
                        │                    │  │
                        │  Matching Logic     │
                        └───────────┬──────────┘
                                    │
                                    │ Trades
                                    ▼
                        ┌──────────────────────┐
                        │       TerminalUI      │
                        │ Shows order book +    │
                        │ recent executed trades │
                        └──────────────────────┘
````

### 3.2 Component Overview

#### **Order**
Represents a single limit order containing:
- `id`
- `symbol`
- `price`
- `quantity`
- `side` (buy/sell)
- `timestamp`

---

#### **OrderBook**
Handles the storage and matching of orders using two priority queues:

- **buyOrders:**  
  Sorted by highest price first → oldest timestamp first  
- **sellOrders:**  
  Sorted by lowest price first → oldest timestamp first  

Implements the matching logic between compatible buy and sell orders.

---

#### **MatchingEngine**
Responsible for driving the simulation:
- Generates random limit orders to simulate real market flow.
- Sends orders to the `OrderBook`.
- Receives a list of trades produced by the matching process.

---

#### **TerminalUI**
Displays real-time market information such as:
- Top buy orders  
- Top sell orders  
- Last executed trades  

Uses ANSI colors and a refreshing terminal display to emulate a live trading dashboard.

---

#### **main.cpp**
Implements the simulation loop:
1. Generate a random order  
2. Submit it to the matching engine  
3. Update and draw the user interface  
4. Wait ~300 ms before the next cycle  

---

### 3.3 Priority Queues (Core Data Structure)

#### **Buy Priority Queue**

```cpp
std::priority_queue<Order, std::vector<Order>, BuyComparator> buyOrders;

struct BuyComparator {
    bool operator()(const Order& a, const Order& b) const {
        if (a.price == b.price) {
            return a.timestamp > b.timestamp; // older order wins
        }
        return a.price < b.price; // higher price = higher priority
    }
};
```

### Sell Priority Queue
```
std::priority_queue<Order, std::vector<Order>, SellComparator> sellOrders;

struct SellComparator {
    bool operator()(const Order& a, const Order& b) const {
        if (a.price == b.price) {
            return a.timestamp > b.timestamp; // older order wins
        }
        return a.price > b.price; // lower price = higher priority
    }
};

```
### 3.4 Matching Algorithm (High-Level)
When a new buy order arrives:
```
while buy has quantity:
    check best sell
    if sell.price > buy.price → stop
    trade = min(buy.qty, sell.qty)
    update quantities
    remove empty orders
if buy still has quantity → push into buy PQ

```
### When a new sell order arrives:

Same logic, but against the buy priority queue using price ≥ sell.price.

## 4. Conclusions and Learnings

This project was a personal challenge, not just a homework assignment.
I had to study a lot on my own to fully understand:

- How modern electronic exchanges work

- How price–time priority truly functions

- How priority queues can simulate a CLOB

- How matching engines operate internally

Even though this is a simplified version of a real stock exchange, building it helped me connect my interest in finance, a field I almost chose as my major, with my current career in computer science.

Designing this simulator let me imagine how systems behind the NYSE or NASDAQ operate under the hood. I enjoyed the process of breaking down a financial mechanism, modeling it with data structures, and turning it into a functional real-time simulation.

Overall, this was one of the most enjoyable assignments because it combines two areas I’m passionate about:

- finance, trading systems, order books

- technology, algorithms, system design

Building a mini-matching engine made me appreciate how complex real financial markets are, and how powerful data structures become when used in real-world systems.
