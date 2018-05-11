#include <iostream>
#include <vector>

/* MergeSort */

template <typename T>
void PartialMergeSort(
        std::vector<T>& data__,
        const size_t lh,
        const size_t rh,
        std::vector<T>& scratch__
) {
    if (rh - lh == 1) {
        return;
    }
    size_t ave = (lh + rh) / 2;
    PartialMergeSort(data__, lh, ave, scratch__);
    PartialMergeSort(data__, ave, rh, scratch__);
    size_t left_p = lh;
    size_t mid_p = ave;
    size_t idx = 0;
    while ((left_p < ave) && (mid_p < rh)) {
        if (data__[mid_p] < data__[left_p]) {
            scratch__[idx] = data__[mid_p];
            ++mid_p;
        } else {
            scratch__[idx] = data__[left_p];
            ++left_p;
        }
        ++idx;
    }
    while (left_p < ave) {
        scratch__[idx] = data__[left_p];
        ++left_p;
        ++idx;
    }
    while (mid_p < rh) {
        scratch__[idx] = data__[mid_p];
        ++mid_p;
        ++idx;
    }
    for (size_t i = 0; i < idx; ++i) {
        data__[lh + i] = scratch__[i];
    }
}


template <typename T>
void MergeSort(std::vector<T>& data_) {
    std::vector<T> scratch(data_.size());
    PartialMergeSort(data_, 0, data_.size(), scratch);
}


int main() {
    std::ios_base::sync_with_stdio(false);
    size_t len;
    std::cin >> len;
    std::vector<int> data(len);
    for (size_t i = 0; i < len; ++i) {
        std::cin >> data[i];
    }

    MergeSort(data);

    for (int i : data) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    return 0;
}
