/*
 * Title: Collatz Sequence Performance Analysis
 *
 * Description:
 * This program evaluates the Collatz sequence for odd integers from 1 to 1×10^9.
 * For each value, it applies the standard transformation rules (n/2 if even,
 * 3n + 1 if odd) until reaching 1 or an early termination condition when the
 * sequence falls below the initial value. Execution time is measured using the
 * C++ <chrono> library to assess computational performance.
 *
 * Inputs:
 * None (all parameters are defined within the program).
 *
 * Outputs:
 * Prints total program execution time in milliseconds to the console.
 *
 * Dependencies:
 * <iostream>, <chrono>
 */
 
#include <iostream>
#include <chrono>

int main() {
    auto time_start = std::chrono::high_resolution_clock::now();
    std::uint64_t num = 1;
    std::uint64_t end = 1e6;
    for (num; num <= end; num += 2) {
        std::uint64_t current_num = num;
        while (current_num != 1) {
            if (current_num < num) {
                break;
            } else if ((current_num % 2) == 0) {
                current_num /= 2;
                // std::cout << current_num << std::endl;
            } else {
                current_num = (current_num * 3) + 1;
                // std::cout << current_num << std::endl;
            }
        }
    }
    // Time Tracking
    auto time_end = std::chrono::high_resolution_clock::now();
    // auto time_duration = std::chrono::duration_cast<std::chrono::microseconds>(time_end - time_start);
    auto time_duration = std::chrono::duration_cast<std::chrono::milliseconds>(time_end - time_start);
    // auto time_duration = std::chrono::duration_cast<std::chrono::seconds>(time_end - time_start);
    
    
    // std::cout << "Program runtime: " << time_duration.count() << " microseconds" << std::endl;
    std::cout << "Program runtime: " << time_duration.count() << " milliseconds" << std::endl;
    // std::cout << "Program runtime: " << time_duration.count() << " seconds" << std::endl;
    
    return 0;
}