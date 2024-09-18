#include "market.h"
#include "stock.h"
int main() {
    Market market;

    // Adding stocks
    Stock stock1("Apple", "Technology", 150.0, 100, 0.5);
    Stock stock2("Tesla", "Automobile", 800.0, 50, 0.3);
    Stock stock3("Amazon", "E-Commerce", 3500.0, 20, 0.4);

    market.addStock(stock1);
    market.addStock(stock2);
    market.addStock(stock3);

    // Display the market
    cout << "Current Market:" << endl;
    market.displayMarket();

    // Update stock price
    market.updateMarketPrice("Tesla", 820.0);

    // Display updated market
    cout << "\nUpdated Market:" << endl;
    market.displayMarket();

    return 0;
}
