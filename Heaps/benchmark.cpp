#include <iostream>
#include <iomanip> 
#include <random>
#include "heap.hpp"

void benchmark_heaps(std::mt19937 gen) {
    std::array<size_t, 6> sizes = {10000, 100000, 1000000, 10000000, 100000000, 1000000000};
    int num_trials = 5; // Reduced for quicker testing across multiple sizes, adjust as needed

    std::cout << std::left << std::setw(12) << "Size"
              << std::setw(25) << "Avg Heapify (s)"
              << std::setw(25) << "Avg Heapify_sift_up (s)"
              << std::setw(15) << "Speedup" << "\n";
    std::cout << std::string(77, '-') << "\n"; // Separator line

    // Time Make-Heaps/Heapify
    for (size_t current_size : sizes) {
        std::uniform_int_distribution<> distrib(1, current_size);
        double total_duration1 = 0.0;
        double total_duration2 = 0.0;
        
        // Repeat measurements with num_trials for given size
        for (int i = 0; i < num_trials; ++i) {
            std::vector<int> vec1(current_size);
            std::vector<int> vec2(current_size);

            // Create two duplicate random vectors
            for (size_t j = 0; j < current_size; ++j) {
                int num = distrib(gen);
                vec1[j] = num;
                vec2[j] = num;
            }

            // The order we do this in does not seem to affect the final result
            auto start1 = std::chrono::high_resolution_clock::now();
            heapify(vec1);
            auto end1 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> duration1 = end1 - start1;
            total_duration1 += duration1.count();

            auto start2 = std::chrono::high_resolution_clock::now();
            heapify_sift_up(vec2);
            auto end2 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> duration2 = end2 - start2;
            total_duration2 += duration2.count();
        }

        double average_duration1 = total_duration1 / num_trials;
        double average_duration2 = total_duration2 / num_trials;
        
        double speedup = (average_duration2 / average_duration1);

        std::cout << std::left << std::setw(12) << current_size
              << std::scientific << std::setprecision(6)
              << std::setw(25) << average_duration1
              << std::setw(25) << average_duration2
              << std::fixed << std::setprecision(2)
              << std::setw(2) << "x" << speedup
              << std::defaultfloat << "\n";
    }
}

int main() {

    std::random_device rd;
    std::mt19937 gen(rd());

    benchmark_heaps(gen);   
}