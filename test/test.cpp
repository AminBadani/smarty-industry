#include <iostream>
#include <chrono>

// See: https://stackoverflow.com/questions/2808398/easily-measure-elapsed-time/27739925#27739925
int main() {
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    while (true) {
        std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::seconds>(end - begin).count() << "s" << std::endl;
        end = std::chrono::steady_clock::now();
        system("clear");
    }
}