#include <iostream>
#include <string>
#include <curl/curl.h>

// Callback function to handle the API response
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* s) {
    size_t newLength = size * nmemb;
    s->append((char*)contents, newLength);
    return newLength;
}

int main() {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    // Initialize CURL
    curl = curl_easy_init();
    if(curl) {
        // Replace with your API key and stock symbol
        std::string api_key = "BTXJ5RYYF9RN16HR";  
        std::string symbol = "IBM";  // Replace with desired stock symbol
        std::string url = "https://www.alphavantage.co/query?function=TIME_SERIES_INTRADAY&symbol=" 
                          + symbol + "&interval=1min&apikey=" + api_key;

        // Set CURL options
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        // Perform the request
        res = curl_easy_perform(curl);

        // Check for errors
        if(res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        } else {
            // Print the response (raw JSON)
            std::cout << readBuffer << std::endl;
        }

        // Clean up
        curl_easy_cleanup(curl);
    }
    return 0;
}
