#include <random>
#include <chrono>
#include <algorithm>
#include <iostream>
#include <iomanip> // Make sure this is included for std::setw, std::left, etc.

#include <vector>

void sift_down(std::vector<int> &vec, std::vector<int>::iterator it) {
    auto largest = it;
    size_t index = std::distance(vec.begin(), it);
    size_t left_index = 2 * index + 1;
    size_t right_index = 2 * index + 2;
    
    if (left_index < vec.size() && vec[left_index] > *largest)
        largest = vec.begin() + left_index;
    
    if (right_index < vec.size() && vec[right_index] > *largest)
        largest = vec.begin() + right_index;

    if (largest != it) {
        std::iter_swap(largest, it);
        sift_down(vec, largest);
    }
}

// Build a max-heap in linear-time with sift-down.
void heapify(std::vector<int> &vec) {
    auto start = vec.begin(); auto end = vec.end();
    auto non_leaves = start + (end - start) / 2 - 1;
    for (auto it = non_leaves; it >= vec.begin(); --it) {
        sift_down(vec, it);
    }
}

void sift_up(std::vector<int> &vec, std::vector<int>::iterator it) {
    // If 'it' is the root, it cannot be sifted up further.
    if (it == vec.begin())
        return;
        
    size_t index = std::distance(vec.begin(), it);
    auto parent_it = vec.begin() + (index - 1) / 2;

    if (*it > *parent_it) {
        std::iter_swap(it, parent_it);
        sift_up(vec, parent_it); 
    }
}

// Build a max-heap by repeatedly applying sift-up.
void heapify_sift_up(std::vector<int> &vec) {
    // A vector with 0 or 1 element is already a heap.
    if (vec.size() <= 1) 
        return; 
    
    for (auto it = vec.begin() + 1; it != vec.end(); ++it) {
        sift_up(vec, it);
    }
}

// Benchmark performance between sift-up and sift-down implementations
int main() {
    std::vector<size_t> sizes = {10000, 100000, 500000, 1000000, 2000000}; // Example sizes
    int num_trials = 20; // Reduced for quicker testing across multiple sizes, adjust as needed

    std::random_device rd;
    std::mt19937 gen(rd());

    std::cout << std::left << std::setw(12) << "Size"
              << std::setw(25) << "Avg Heapify (s)"
              << std::setw(25) << "Avg Heapify_sift_up (s)" << "\n";
    std::cout << std::string(62, '-') << "\n"; // Separator line

    for (size_t current_size : sizes) {
        std::uniform_int_distribution<> distrib(1, current_size);
        double total_duration1 = 0.0;
        double total_duration2 = 0.0;

        // std::cout << "Running " << num_trials << " trials for size " << current_size << "\n"; // Optional: per-size progress

        for (int i = 0; i < num_trials; ++i) {
            std::vector<int> vec1(current_size);
            std::vector<int> vec2(current_size);

            for (size_t j = 0; j < current_size; ++j) {
                int num = distrib(gen);
                vec1[j] = num;
                vec2[j] = num;
            }

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

        std::cout << std::left << std::setw(12) << current_size
                  << std::scientific << std::setprecision(6)
                  << std::setw(25) << average_duration1
                  << std::setw(25) << average_duration2
                  << std::defaultfloat << "\n";
    }
    return 0;
}