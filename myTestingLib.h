#ifndef MYTESTINGLIB_H
#define MYTESTINGLIB_H

#include <string>
#include <vector>
#include <concepts>

namespace Testing {
namespace Generators {
    template <typename T>
    std::vector<T> generateVectorWithDuplicates(int size, T min, T max);
    template <typename T>
    std::vector<T> generateSortedVectorWithDuplicates(int size, T min, T max);
    template <typename T>
    std::vector<T> generateVectorWithoutDuplicates(int size, T min, T max);
    template <typename T>
    std::vector<T> generateSortedVectorWithoutDuplicates(int size, T min, T max);


template<typename Node>
concept BSTNodeConcept = requires(Node* node, int val) {
    { node->getValue() } -> std::convertible_to<int&>;
    { node->getLeft() } -> std::same_as<Node*&>;
    { node->getRight() } -> std::same_as<Node*&>;
    { Node(val) } -> std::same_as<Node>;
};

template <BSTNodeConcept Node>
Node* generateBST(int size, int min, int max);
template <BSTNodeConcept Node>
Node* generateBalancedBST(int size, int min, int max);
template <BSTNodeConcept Node>
Node* generateFullBST(int size, int min, int max); //todo реализовать
template <BSTNodeConcept Node>
Node* buildBST(std::vector<int>& values);


std::string generateString(int lenght);
std::string generateStringWithSmallLatinLetters(int length);
std::string generateStringWithLatinLetters(int length);

}
namespace Benchmarks {}
}

#include "myTestingLib.tpp"

#endif