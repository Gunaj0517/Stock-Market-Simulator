#include <iostream>
#include <cstdlib>
#include <ctime>
#include <queue>
#include <unistd.h>
#include "fluctuator.h"  // Include the header file

using namespace std;

Stock::Stock(string symbol, double initialPrice) : symbol(symbol), price(initialPrice) {}

string Stock::getSymbol() const {
    return symbol;
}

double Stock::getPrice() const {
    return price;
}

void Stock::updatePrice(double newPrice) {
    price = newPrice;
}

void Stock::simulatePriceFluctuation() {
    double fluctuation = (rand() % 2001 - 1000) / 1000.0;  // Random fluctuation between -1.0 and 1.0
    double newPrice = price * (1 + fluctuation / 100);
    updatePrice(newPrice);
}

void simulateMarketFluctuationsWithQueue(queue<Stock>& stockQueue) {
    int size = stockQueue.size();
    for (int i = 0; i < size; ++i) {
        Stock currentStock = stockQueue.front();
        currentStock.simulatePriceFluctuation();
        stockQueue.pop();
        stockQueue.push(currentStock);
    }
}

int main() {
    srand(time(0));  // Seed random number generator

    int numStocks;
    cout << "Enter the number of stocks (max 10): ";
    cin >> numStocks;

    queue<Stock> stockQueue;

    for (int i = 0; i < numStocks; ++i) {
        if (stockQueue.size() >= 10) {
            cout << "Queue is full. No more than 10 stocks allowed." << endl;
            break;
        }

        string symbol;
        double price;

        cout << "Enter the symbol for stock " << i + 1 << ": ";
        cin >> symbol;

        cout << "Enter the initial price for stock " << symbol << ": ";
        cin >> price;

        Stock stock(symbol, price);
        stockQueue.push(stock);
    }

    int fluctuationCount = 0;

    while (fluctuationCount < 10) {
        simulateMarketFluctuationsWithQueue(stockQueue);

        cout << "\nQueue stocks after fluctuation #" << fluctuationCount + 1 << ":\n";
        queue<Stock> tempQueue = stockQueue;
        while (!tempQueue.empty()) {
            cout << "Symbol: " << tempQueue.front().getSymbol()
                 << " | Price: " << tempQueue.front().getPrice() << endl;
            tempQueue.pop();
        }

        sleep(10);  // Wait for 10 seconds

        fluctuationCount++;
    }

    cout << "\nSimulation complete." << endl;
    return 0;
}
 
/*g++ fluctuator.cpp simulator.cpp -o stock_simulator */