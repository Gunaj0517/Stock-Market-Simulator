#include <iostream>
#include <string>
#include <vector>
#include <curl/curl.h>
#include "json.hpp"
#include "curl_wrapper.h"

using json = nlohmann::json;

// Callback function to handle data received from the CURL request
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp) {
    size_t totalSize = size * nmemb;
    userp->append((char*)contents, totalSize);
    return totalSize;
}

// Function to fetch stock data
json fetchStockData(const std::string& stockSymbol, const std::string& apiKey) {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;
    json stockData;

    curl = curl_easy_init();
    if (curl) {
        std::string url = "https://www.alphavantage.co/query?function=TIME_SERIES_INTRADAY&symbol=" + stockSymbol + "&interval=5min&apikey=" + apiKey;
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        // Reduced verbosity settings in fetchStockData
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 0L);  // Set verbose to 0 to reduce logs
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L); // For debugging: Disable SSL peer verification (can remove once working)

        // Display essential connection message only
        std::cout << "Fetching data for " << stockSymbol << "..." << std::endl;

        // Perform the CURL request
        res = curl_easy_perform(curl);

        // Check for successful response
        long response_code;
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
        if (res == CURLE_OK && response_code == 200) {
            stockData = json::parse(readBuffer);
        } else {
            std::cerr << "Failed to fetch data for " << stockSymbol << std::endl;
        }

        curl_easy_cleanup(curl);
    }

    return stockData;
}

// Function to extract latest stock details
void extractStockDetails(const json& stockData) {
    if (stockData.contains("Meta Data") && stockData["Meta Data"].contains("3. Last Refreshed")) {
        std::string latestTime = stockData["Meta Data"]["3. Last Refreshed"];
        auto latestData = stockData["Time Series (5min)"][latestTime];

        // Extract stock details
        std::string stockName = stockData["Meta Data"]["2. Symbol"];
        double openPrice = std::stod(latestData["1. open"].get<std::string>());
        double highPrice = std::stod(latestData["2. high"].get<std::string>());
        double lowPrice = std::stod(latestData["3. low"].get<std::string>());
        double closePrice = std::stod(latestData["4. close"].get<std::string>());
        double volume = std::stod(latestData["5. volume"].get<std::string>());

        // Display extracted stock details
        std::cout << "Stock: " << stockName << std::endl;
        std::cout << "Latest Time: " << latestTime << std::endl;
        std::cout << "Open Price: " << openPrice << std::endl;
        std::cout << "High Price: " << highPrice << std::endl;
        std::cout << "Low Price: " << lowPrice << std::endl;
        std::cout << "Close Price: " << closePrice << std::endl;
        std::cout << "Volume: " << volume << std::endl;
    }
    else {
        std::cerr << "Invalid stock data received." << std::endl;
    }
}

// Function to display close prices at given intervals
void displayRecentClosePrices(const json& stockData, const std::string& symbol, const std::vector<int>& intervals) {
    if (!stockData.contains("Time Series (5min)")) {
        std::cerr << "No time series data available for " << symbol << std::endl;
        return;
    }

    auto& timeSeries = stockData["Time Series (5min)"];
    int intervalIndex = 0;
    int elapsedTime = 0;

    std::cout << "Closing prices for " << symbol << " at specified intervals:\n";

    for (const auto& [time, data] : timeSeries.items()) {
        if (elapsedTime == intervals[intervalIndex]) {
            double closePrice = std::stod(data["4. close"].get<std::string>());
            std::cout << " - " << elapsedTime << " minutes ago: " << closePrice << std::endl;

            intervalIndex++;
            if (intervalIndex >= intervals.size()) break;
        }
        elapsedTime += 5;
    }

    if (intervalIndex < intervals.size()) {
        std::cerr << "Warning: Not enough data to display all intervals for " << symbol << std::endl;
    }
}
