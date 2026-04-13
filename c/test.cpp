#include <iostream>
#include <chrono>

int main() {
    auto time_start = std::chrono::high_resolution_clock::now();
    std::uint64_t num = 1;
    std::uint64_t end = 5e9;
    for (num; num <= end; num += 2) {
        std::uint64_t current_num = num;
        while (current_num != 1) {
            if ((current_num & 1) == 0) {
                current_num >>= 1;
                // std::cout << current_num << std::endl;
            } else {
                current_num = (current_num * 3 + 1) >> 1;
                // std::cout << current_num << std::endl;
            }
            if (current_num < num) {
                break;
            }
        }
    }
    // Time Tracking
    auto time_end = std::chrono::high_resolution_clock::now();
    // auto time_duration = std::chrono::duration_cast<std::chrono::microseconds>(time_end - time_start);
    // auto time_duration = std::chrono::duration_cast<std::chrono::milliseconds>(time_end - time_start);
    auto time_duration = std::chrono::duration_cast<std::chrono::seconds>(time_end - time_start);
    
    
    // std::cout << "Program runtime: " << time_duration.count() << " microseconds" << std::endl;
    // std::cout << "Program runtime: " << time_duration.count() << " milliseconds" << std::endl;
    std::cout << "Program runtime: " << time_duration.count() << " seconds" << std::endl;
    
    return 0;
}