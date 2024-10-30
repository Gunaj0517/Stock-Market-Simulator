#include <iostream>
#include <vector>
#include "curl_wrapper.h"

int main() {
    std::vector<std::string> symbols = {"AAPL", "GOOGL", "MSFT", "AMZN", "META", "TSLA", "NFLX", "NVDA", "DIS", "JPM"};
    std::string apiKey = "9D667TJ28IKVDI27"; // Replace with your actual API key

    for (const auto& symbol : symbols) {
        std::cout << "\nFetching data for " << symbol << ":\n";
        json stockData = fetchStockData(symbol, apiKey);
        extractStockDetails(stockData); // This will display the latest stock data for each symbol
        displayRecentClosePrices(stockData, symbol, {5, 10, 15}); // Fetch closing prices for past intervals
    }
    
    return 0;
}


/*
g++ -I"C:\curl-8.10.1_7-win64-mingw\include" -L"C:\curl-8.10.1_7-win64-mingw\lib" -o StockMarketSimulator.exe main_trial.cpp curl_wrapper.cpp -lcurl
.\StockMarketSimulator.exe
*/