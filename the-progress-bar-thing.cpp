#include <iostream>
#include <iomanip>
#include <string>
#include <chrono>
#include <thread>
#define PBSTR "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
#define PBWIDTH 100
void px(double p) {
    int v = static_cast<int>(p * 100);
    int l = static_cast<int>(p * PBWIDTH);
    int r = PBWIDTH - l;
    std::cout << "\r" << std::setw(3) << v << "% [" << std::string(l, '|') << std::string(r, ' ') << "]";
    std::cout.flush();
}
int main() {
    double p = 0.0;
    const double m = 1.0;
    while (p < m) {
        px(p);
        std::this_thread::sleep_for(std::chrono::seconds(1));
        p += 0.1;
        if (p > m) {
            p = m;
        }
    }
    px(p);
    return 0;
}

