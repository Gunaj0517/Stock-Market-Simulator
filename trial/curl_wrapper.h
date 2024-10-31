//curl_wrapper.h
#ifndef CURL_WRAPPER_H
#define CURL_WRAPPER_H

#include <string>
#include <vector>
#include "json.hpp"

using json = nlohmann::json;

json fetchStockData(const std::string& symbol, const std::string& apiKey);
void extractStockDetails(const json& stockData);
void displayRecentClosePrices(const json& stockData, const std::string& symbol, const std::vector<int>& intervals);

#endif // CURL_WRAPPER_H