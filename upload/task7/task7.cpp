#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <cstring>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

using namespace std;

// Function to perform a simple HTTP GET request
string httpGet(const string& host, const string& path) {
    struct addrinfo hints, *res;
    int sockfd;

    // 1. DNS Resolution
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;    // Allow IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM; // TCP stream sockets

    int status = getaddrinfo(host.c_str(), "80", &hints, &res);
    if (status != 0) {
        cerr << "getaddrinfo error: " << gai_strerror(status) << endl;
        return "";
    }

    // 2. Socket Creation and Connection
    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (sockfd == -1) {
        perror("socket");
        freeaddrinfo(res);
        return "";
    }

    if (connect(sockfd, res->ai_addr, res->ai_addrlen) == -1) {
        perror("connect");
        close(sockfd);
        freeaddrinfo(res);
        return "";
    }

    freeaddrinfo(res); // All done with this structure

    // 3. Send Request
    string request = "GET " + path + " HTTP/1.1\r\n" +
                          "Host: " + host + "\r\n" +
                          "Connection: close\r\n\r\n";

    if (send(sockfd, request.c_str(), request.length(), 0) == -1) {
        perror("send");
        close(sockfd);
        return "";
    }

    // 4. Receive Response
    string response_str;
    vector<char> buffer(4096);
    ssize_t bytes_received;

    while ((bytes_received = recv(sockfd, buffer.data(), buffer.size(), 0)) > 0) {
        response_str.append(buffer.data(), bytes_received);
    }

    if (bytes_received == -1) {
        perror("recv");
    }

    // 5. Close Socket
    close(sockfd);

    return response_str;
}
double getEuroToUsdRate() {
    string host = "v6.exchangerate-api.com";
    string path = "/v6/latest/EUR";
    string response = httpGet(host, path);

    if (response.empty()) {
        cerr << "Failed to get HTTP response." << endl;
        return 0;
    }

    // Find the start of the JSON body
    size_t json_start = response.find("\r\n\r\n");
    if (json_start == string::npos) {
        cerr << "Invalid HTTP response." << endl;
        return 0;
    }
    string json_body = response.substr(json_start + 4);

    // Super simple JSON parsing to find the USD rate
    string search_str = "\"USD\":";
    size_t usd_pos = json_body.find(search_str);
    if (usd_pos == string::npos) {
        cerr << "Could not find USD rate in response." << endl;
        return 0;
    }

    size_t rate_start = usd_pos + search_str.length();
    size_t rate_end = json_body.find_first_of(",}", rate_start);
    if (rate_end == string::npos) {
        cerr << "Could not parse USD rate." << endl;
        return 0;
    }

    string usd_rate_str = json_body.substr(rate_start, rate_end - rate_start);
    try {
        return stod(usd_rate_str);
    } catch (const std::invalid_argument& ia) {
        cerr << "Invalid number format for USD rate: " << usd_rate_str << endl;
        return 0;
    }
}

int main() {
    double EUR_TO_USD = getEuroToUsdRate();

    if (EUR_TO_USD == 0) {
        cout << "Failed to fetch exchange rate. Using default rate." << endl;
        EUR_TO_USD = 1.08; // Fallback to a default rate
    }


    int choice;
    double amount;

    cout << "Currency Converter" << endl;
    cout << "Rates provided by exchangerate-api.com" << endl;
    cout << "1. Euros to Dollars" << endl;
    cout << "2. Dollars to Euros" << endl;
    cout << "Enter your choice (1 or 2): ";
    cin >> choice;

    cout << fixed << setprecision(2);

    if (choice == 1) {
        cout << "Enter amount in Euros: ";
        cin >> amount;
        cout << amount << " EUR is " << (amount * EUR_TO_USD) << " USD." << endl;
    } else if (choice == 2) {
        cout << "Enter amount in Dollars: ";
        cin >> amount;
        cout << amount << " USD is " << (amount / EUR_TO_USD) << " EUR." << endl;
    } else {
        cout << "Invalid choice." << endl;
    }

    return 0;
}
