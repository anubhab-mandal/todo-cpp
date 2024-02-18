#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
#include <chrono>
#include <thread>
#include <stdexcept>
#include <filesystem>
namespace fs = std::filesystem;
#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif
#define WIDTH 50
void xFnY(double x, std::ostream& y) {
    int xInt = static_cast<int>(x * 100);
    int xLeftPad = static_cast<int>(x * WIDTH);
    int xRightPad = WIDTH - xLeftPad;
    const std::string xColor = "\033[36m";
    const std::string xBold = "\033[1m";
    const std::string xReset = "\033[0m";
    std::string xBar;
    for (int i = 0; i < xLeftPad; ++i) {
        xBar += '|';
    }
    y << "\r\n" << xBold << std::setw(3) << xInt << "% [ " << xColor << xBar << xReset << std::string(xRightPad, ' ') << " ]\n" << std::flush;
}
void aZ(std::vector<std::string>& b) {
    std::string c;
    std::cout << "Load existing txt file? (Press 1 for yes, 0 to continue without loading): ";
    int d;
    std::cin >> d;
    if (d == 1) {
        std::cout << "Enter the directory of the text file: ";
        std::cin >> c;
        if (fs::is_directory(c)) {
            std::cerr << "Error: The directory path should include the file name and extension." << std::endl;
            std::cout << "Please try again." << std::endl;
            aZ(b);
            return;
        }
        if (fs::path(c).extension() != ".txt") {
            std::cerr << "Error: Only use TXT files." << std::endl;
            return;
        }
        std::ifstream e(c);
        try {
            if (!e) {
                throw std::invalid_argument("File not found or directory path is incorrect.");
            }
            std::string f;
            int g = 1;
            while (getline(e, f)) {
                b.push_back(std::to_string(g++) + ". " + f);
            }
            std::cout << "File loaded successfully." << std::endl;
            e.close();
        } catch (const std::invalid_argument& h) {
            std::cerr << "Error: " << h.what() << std::endl;
            std::cout << "Please try again." << std::endl;
            aZ(b);
        }
    }
}
int main() {
    std::vector<std::string> i;
    aZ(i);
    int j = i.size();
    int k = 0;
    int l = 0, m = i.size();
    std::string n = "1";
    bool o = true;
    while (n == "1" && l > 0) {
        std::cout << "\nEnter list name:\n\t";
        getline(std::cin, n, '\n');
        if (n != "0") {
            m += 1;
            n = std::to_string(m) + ". " + n;
            i.push_back(n);
            n = "1";
            if (o) {
                l = l - 1;
            }
        } else {
            n = "0";
        }
    }
    system(CLEAR);
    for (size_t p = 0; p < i.size(); ++p) {
        std::cout << "\033[1;31m" << i[p] << "\033[0m" << std::endl;
    }
    std::cout << std::endl;
    int q;
    std::vector<bool> r(i.size(), false);
    while (true) {
        std::cout << "\n\nEnter the index of the item (multiple indexes separated by a whitespace) you want to display in bold (starting from 1), or 0 to finish: \n";
        std::cin >> q;
        if (q == 0) {
            break;
        }
        if (q > 0 && q <= static_cast<int>(i.size())) {
            r[q - 1] = !r[q - 1];
            if (r[q - 1]) {
                k++;
            } else {
                k--;
            }
            system(CLEAR);
            for (size_t p = 0; p < i.size(); ++p) {
                if (r[p]) {
                    std::cout << "\033[1;32m" << i[p] << "\033[0m" << std::endl;
                } else {
                    std::cout << "\033[1;31m" << i[p] << "\033[0m" << std::endl;
                }
            }
            double s = static_cast<double>(k) / j;
            xFnY(s, std::cout);
            if (s >= 1.0) {
                std::cout << "\n\033[1m";
                std::cout << std::setw(50) << std::right << "You have done it, you pig!" << std::endl;
                std::cout << std::setw(50) << std::right << "Good job." << std::endl;
                std::cout << "\033[0m";
                return 0;
            }
        } else {
            std::cout << "Invalid index! Please enter a valid index or 0 to finish." << std::endl;
        }
    }
    return 0;
}

