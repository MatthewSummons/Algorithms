#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

void print(const std::vector<int> &vec) {
    for (const auto &elem : vec) {
        std::cout << elem << " ";
    } std::cout << std::endl;
}

// Assume non-empty vector input
int max(const std::vector<int> arr) {
    int maxElement = arr[0];
    for (int i = 1; i < arr.size(); i++) {
        if (arr[i] > maxElement)
            maxElement = arr[i];
    } return maxElement;
}

// Construct a min-heap and return the k smallest elements O(k log n)
std::vector<int> k_smallest(std::vector<int> &vec, const int k) {
    std::vector<int> result;
    result.reserve(k);

    std::make_heap(vec.begin(), vec.end(), std::greater<int>());
    for (int i = 0; i < k && !vec.empty(); ++i) {
        result.push_back(vec.front());
        pop_heap(vec.begin(), vec.end(), std::greater<int>());
        vec.pop_back();
    } return result; // Modifies/Removes the k smallest elements from the original vector
    // Note: If you want to keep the original vector unchanged, consider using a copy of it.
}

void subset_3(const std::vector<int> &vec, std::vector<std::array<int, 3>> &subset) {
    size_t n = vec.size();
    if (n < 3) {return;}
    for (auto i = 0; i < n; i++) {
        for (auto j = i + 1; j < n; j++) {
            for (auto k = j + 1; k < n; k++) {
                subset.push_back(std::array<int, 3>{vec[i], vec[j], vec[k]});
            }
        }
    }
}

// Insertion Sort with Binary Search
std::vector<int> insertion_sort(const std::vector<int> &vec) {
    if (vec.empty()) {
        return {};
    }

    std::vector<int> res;
    res.reserve(vec.size());
    
    res.emplace_back(vec[0]);
    for (auto it = vec.begin() + 1; it < vec.end(); it++) {
        if (*it < res.front()) {
            res.insert(res.begin(), *it);
        } else if (*it > res.back()) {
            res.emplace_back(*it);
        } else { // Needs to be inserted (with binary search)
            auto l = res.begin();
            auto r = res.end();
            while (l + 1 < r) {
                auto mid = l + (r - l) / 2;
                if (*it < *mid) {
                    r = mid;
                } else {
                    l = mid;
                }
            } res.insert(r, *it); 
        }
    } return res;
}

// Eculid's GCD Algorithm
int gcd(int a, int b) {
    if (b == 0) {
        return a;
    } else {
        return gcd(b, a % b);
    }
}

int main() {
    std::vector<int> arr = {3, 2, 5, 3, 1};
    std::cout << "1. Largest element is: " << max(arr) << std::endl;
    std::cout << "2. 3-smallest elements: "; print(k_smallest(arr, 3));
    
    const std::vector<int> arr2 = {2, 1, 3, 4};
    std::vector<std::array<int, 3>> huzz;
    subset_3(arr2, huzz);
    std::cout << "3. Subsets of size 3:" << std::endl;
    for (auto &tpl: huzz) {
        std::cout << "\t( ";
        for (const auto &elem : tpl) {
            std::cout << elem << ", ";
        } std::cout << ")" << std::endl;
    }

    const std::vector<int> arr3 = {2, 1, 3, -2, 0, 10, 6, 7, 8};
    auto res = insertion_sort(arr3);
    std::cout << "4. Insertion Sort w/ Binary Search: " << "\n\t"; print(res);

    int a = 120; int b = 108;
    std::cout << "4. GCD of " << a << " " << b << ": " << gcd(a, b) << std::endl;
}






