#ifndef MYTESTINGLIB_H
#define MYTESTINGLIB_H

#include <string>
#include <vector>

namespace Testing {
namespace Generators {
    //TODO убедиться что не сломается из-за типов
    template <typename T>
    std::vector<T> generateVectorWithDuplicates(int size, T min, T max);
    template <typename T>
    std::vector<T> generateSortedVectorWithDupicates(int size, T min, T max);
    template <typename T>
    std::vector<T> generateVectorWithoutDuplicates(int size, T min, T max);
    template <typename T>
    std::vector<T> generateSortedVectorWithoutDupicates(int size, T min, T max);

// struct BSTNode {
//     int value;
//     BSTNode* left;
//     BSTNode* right;
// };

// BSTNode* generateBST(int size);
// BSTNode* generateBalancedBST(int size);
// BSTNode* generateFullBST(int size);

// BSTNode* buildBST(std::vector<int> values);

std::string generateString(int lenght);
std::string generateStringWithSmallLatinLetters(int length);
std::string generateStringWithLatinLetters(int length);

}
namespace Benchmarks {}
}

#endif MYTESTINGLIB_H