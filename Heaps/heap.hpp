#pragma once
#include <vector>

void heapify(std::vector<int> &vec);
void heapify_sift_up(std::vector<int> &vec);
std::vector<int> meld_heap(const std::vector<int> &h1, const std::vector<int> &h2);