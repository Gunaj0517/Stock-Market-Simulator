#include <iostream>
#include <string>
#include <curl/curl.h>

// Callback to store the data returned by the API
static size_t WriteCallback(void *contents, size_t size, size_t nmemb, std::string *s)
{
    size_t newLength = size * nmemb;
    try
    {
        s->append((char *)contents, newLength);
    }
    catch (std::bad_alloc &e)
    {
        return 0;
    }
    return newLength;
}

// Function to fetch stock data using curl
std::string fetchStockData(const std::string &symbol, const std::string &apiKey)
{
    CURL *curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if (curl)
    {
        std::string url = "https://www.alphavantage.co/query?function=TIME_SERIES_INTRADAY&symbol=" + symbol +
                          "&interval=5min&apikey=" + apiKey;
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        // Disable SSL verification (Not recommended for production)
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        if (res != CURLE_OK)
        {
            std::cerr << "Error fetching data: " << curl_easy_strerror(res) << std::endl;
        }
    }
    return readBuffer;
}

int main()
{
    std::string symbol = "AAPL";             // Example stock symbol (Apple Inc.)
    std::string apiKey = "AWX362W64AMJLHG4"; // Replace with your Alpha Vantage API key
    std::string stockData = fetchStockData(symbol, apiKey);

    // Output the fetched data (JSON format)
    std::cout << stockData << std::endl;

    return 0;
}
