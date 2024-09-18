#ifndef MARKET_H
#define MARKET_H

#include "stock.h"

// StockNode class for linked list
struct StockNode {
    Stock data;
    StockNode* next;

    StockNode(Stock s) : data(s), next(nullptr) {}
};

// Market class
class Market {
private:
    StockNode* head;

public:
    Market() : head(nullptr) {}

    ~Market() {
        StockNode* current = head;
        while (current != nullptr) {
            StockNode* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }

    // Add a stock to the market
    void addStock(Stock s) {
        StockNode* newStock = new StockNode(s);
        newStock->next = head;
        head = newStock;
    }

    // Update stock price
    void updateMarketPrice(string stockName, double newPrice) {
        StockNode* temp = head;
        while (temp != nullptr) {
            if (temp->data.getName() == stockName) {
                temp->data.updatePrice(newPrice);
                return;
            }
            temp = temp->next;
        }
        cout << "Stock not found!" << endl;
    }

    // Display all stocks in the market
    void displayMarket() const {
        StockNode* temp = head;
        while (temp != nullptr) {
            temp->data.display();
            temp = temp->next;
        }
    }
};

#endif
