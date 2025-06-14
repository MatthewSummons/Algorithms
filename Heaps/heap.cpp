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

// Build a max-heap in linear-time with sift-down.
void heapify(std::vector<int> &vec) {
    auto start = vec.begin(); auto end = vec.end();
    auto non_leaves = start + (end - start) / 2 - 1;
    for (auto it = non_leaves; it >= vec.begin(); --it) {
        sift_down(vec, it);
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

std::vector<int> meld_heap(const std::vector<int> &h1, const std::vector<int> &h2) {
    std::vector<int> res;
    res.reserve(h1.size() + h2.size());
    res.insert(res.end(), h1.begin(), h1.end());
    res.insert(res.end(), h2.begin(), h2.end());

    heapify(res);
    return res;
}