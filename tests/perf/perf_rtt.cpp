#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <algorithm>
#include <chrono>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
using namespace std::chrono;

static void die(const char* msg) {
    perror(msg);
    exit(1);
}

int main() {
    const char* HOST = "127.0.0.1";
    const int PORT   = 9000;
    const int ITER   = 20000;

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) die("socket");

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port   = htons(PORT);
    inet_pton(AF_INET, HOST, &addr.sin_addr);

    if (connect(sock, (sockaddr*)&addr, sizeof(addr)) < 0) {
        die("connect");
    }

    cout << "Connected to " << HOST << ":" << PORT << endl;

    string msg = "{\"type\":\"NEW_ORDER\",\"symbol\":\"AAPL\","
                 "\"side\":\"BUY\",\"price\":100.5,\"qty\":1}\n";

    vector<long long> rtts;
    rtts.reserve(ITER);

    char buffer[4096];

    for (int i = 0; i < ITER; i++) {
        auto start = high_resolution_clock::now();

        ssize_t n = send(sock, msg.c_str(), msg.size(), 0);
        if (n <= 0) die("send");

        ssize_t rn = recv(sock, buffer, sizeof(buffer) - 1, 0);
        if (rn <= 0) die("recv");
        buffer[rn] = '\0';
        auto end = high_resolution_clock::now();

        long long ns = duration_cast<nanoseconds>(end - start).count();
        rtts.push_back(ns);
    }

    close(sock);

    sort(rtts.begin(), rtts.end());
    auto pct = [&](double p) {
        return rtts[(size_t)(p * rtts.size())];
    };

    cout << "\n===== RTT Benchmark Results =====\n";
    cout << "Samples = " << rtts.size() << "\n";
    cout << "p50  = " << pct(0.50)  / 1000.0 << " us\n";
    cout << "p95  = " << pct(0.95)  / 1000.0 << " us\n";
    cout << "p99  = " << pct(0.99)  / 1000.0 << " us\n";
    cout << "p999 = " << pct(0.999) / 1000.0 << " us\n";
    cout << "max  = " << rtts.back() / 1000.0 << " us\n";

    return 0;
}
