
#include <random>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <type_traits>
#include <limits>
#include <cassert>
#include <cstdint>
#include <stdexcept>
#include "myTestingLib.h"

namespace Testing {
namespace Generators {
inline std::mt19937_64 randomEngine{std::random_device{}()};

template <typename T>
T generateRandomValue(T min, T max) {
    if constexpr (std::is_integral_v<T>) {
        std::uniform_int_distribution<T> dist(min, max);
        return dist(randomEngine);
    } else if constexpr (std::is_floating_point_v<T>) {
        std::uniform_real_distribution<T> dist(min, max);
        return dist(randomEngine);
    } else {
        static_assert(std::is_arithmetic_v<T>,
                      "Only arithmetic types (int/int64_t/double) are supported");
    }
}

template <typename T>
std::vector<T> generateVectorWithDuplicates(int size, T min, T max) {
    std::vector<T> result;
    result.reserve(size);
    for (int i = 0; i < size; ++i) {
        result.push_back(generateRandomValue(min, max));
    }
    return result;
}

template <typename T>
std::vector<T> generateSortedVectorWithDuplicates(int size, T min, T max) {
    auto result = generateVectorWithDuplicates(size, min, max);
    std::sort(result.begin(), result.end());
    return result;
}

template <typename T>
std::vector<T> generateVectorWithoutDuplicates(int size, T min, T max) {
    if constexpr (std::is_floating_point_v<T>) {
        static_assert(false, "Floating-point uniqueness is not quaranteered");
    }
    uint64_t range_size = static_cast<uint64_t>(max) - static_cast<uint64_t>(min) + 1;
    if (static_cast<uint64_t>(size) > range_size) {
        throw std::invalid_argument("Requested size exceeds range of unique values.");
    }
    std::unordered_set<T> unique_values;
    while (unique_values.size() < static_cast<size_t>(size)) {
        unique_values.insert(generateRandomValue(min, max));
    }
    std::vector<T> result;
    result.reserve(size);
    for (T elem : unique_values) {
        result.push_back(elem);
    }
    return result;
}

template <typename T>
std::vector<T> generateSortedVectorWithoutDuplicates(int size, T min, T max) {
    auto result = generateVectorWithoutDuplicates(size, min, max);
    std::sort(result.begin(), result.end());
    return result;
}

template <BSTNodeConcept Node>
Node* insertBST(Node* root, int val) {
    if (!root) {
        return new Node(val);
    }
    if (val < root->getValue()) {
        root->getLeft() = insertBST<Node>(root->getLeft(), val);
    } else {
        root->getRight() = insertBST<Node>(root->getRight(), val);
    }
    return root;
}

template <BSTNodeConcept Node>
Node* generateBST(int size, int min, int max) {
    std::vector<int> values = generateVectorWithoutDuplicates(size, min, max);
    Node* root = nullptr;
    for (int el : values) {
        root = insertBST<Node>(root, el);
    }
    return root;
}

template <BSTNodeConcept Node>
Node* buildBST(std::vector<int>& values) {
    Node* root = nullptr;
    for (int el : values) {
        root = insertBST<Node>(root, el);
    }
    return root;
}

template <BSTNodeConcept Node>
Node* buildBalancedBSTFromSorted(const std::vector<int>& values, int left, int right) {
    if (left > right)
        return nullptr;
    int mid = left + (right - left) / 2;
    Node* root = new Node(values[mid]);
    root->getLeft() = buildBalancedBSTFromSorted<Node>(values, left, mid - 1);
    root->getRight() = buildBalancedBSTFromSorted<Node>(values, mid + 1, right);
    return root;
}

template <BSTNodeConcept Node>
Node* generateBalancedBST(int size, int min, int max) {
    std::vector<int> values = generateSortedVectorWithoutDuplicates(size, min , max);
    return buildBalancedBSTFromSorted<Node>(values, 0, size - 1);
}

}  // namespace Generators
}  // namespace Testing
