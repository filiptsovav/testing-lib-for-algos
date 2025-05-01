#include "myTestingLib.h"
#include <vector>
#include <iostream>

struct MyNode {
    int v;
    MyNode* l;
    MyNode* r;

    int& getValue() {
        return v;
    }

    MyNode*& getLeft() {
        return l;
    }

    MyNode*& getRight() {
        return r;
    }

};

void preorderTraversal(MyNode* root) {
    if (!root) return;
    std::cout << root->getValue() << " ";
    preorderTraversal(root->getLeft());
    preorderTraversal(root->getRight());
}

int main() {
    std::vector<int> vect = Testing::Generators::generateVectorWithDuplicates(20, 1, 100);
    std::cout<<"Vector: \n";
    for(int i : vect) {
        std::cout<<i<<" ";
    }
    std::cout<<"\nSorted vector: \n";
    vect = Testing::Generators::generateSortedVectorWithDuplicates(15, -10, 10);
    for(int i : vect) {
        std::cout<<i<<" ";
    }
    std::cout<<"\nVector without duplicates: \n";
    vect = Testing::Generators::generateVectorWithoutDuplicates(10, 0, 1000);
    for(int i : vect) {
        std::cout<<i<<" ";
    }
    std::cout<<"\nSorted vector without duplicates: \n";
    vect = Testing::Generators::generateSortedVectorWithoutDuplicates(20, -100, 100);
    for(int i : vect) {
        std::cout<<i<<" ";
    }

    MyNode* root = Testing::Generators::generateBST<MyNode>(10, 0, 100);
    std::cout<<"\nLeft traversal of generated BST: \n";
    preorderTraversal(root);
    root = Testing::Generators::generateBalancedBST<MyNode>(20, 5, 100);
    std::cout<<"\nLeft traversal of generated balanced BST: \n";
    preorderTraversal(root);
    std::vector<int> for_test = {2, 8, 5, 3, 1, 11, 12, 7, 4};
    root = Testing::Generators::buildBST<MyNode>(for_test);
    std::cout<<"\nLeft traversal of generated BST: \n";
    preorderTraversal(root);
}