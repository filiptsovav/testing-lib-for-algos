#include "myTestingLib.h"

#include <random>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <type_traits>

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
        static_assert(std::is_arithmetic_v<T>,  "Only arithmetic types (int/int64_t/double) are supported");
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
    std::unordered_set<T> unique_values;
    while (unique_values.size() < static_cast<size_t>(size)) {
        unique_values.insert(generateRandomValue(min, max));
    }
    std::vector<T> result;
    result.reserve(size);
    for (T  elem : unique_values) {
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
} 
}  
