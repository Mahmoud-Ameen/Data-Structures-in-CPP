//
// Created by MAHMOUD on 7/19/2023.
//

#ifndef DATA_STRUCTURES_AND_ALGORITHM_ANALYSIS_IN_C_BINARYSEARCHTREE_H
#define DATA_STRUCTURES_AND_ALGORITHM_ANALYSIS_IN_C_BINARYSEARCHTREE_H

#include <algorithm>

template<typename Comparable>
class BinarySearchTree {
public:
    BinarySearchTree();                            // default constructor
    BinarySearchTree(const BinarySearchTree& rhs); // copy constructor
    BinarySearchTree(BinarySearchTree&& rhs);      // move constructor
    ~BinarySearchTree();                           // destructor

    /*** Public Constant Methods  ***/
    const Comparable& findMin() const;
    const Comparable& findMax() const;
    bool contains(const Comparable& element) const;
    bool isEmpty() const;
    void printTree() const;

    /*** Public Non-Constant Methods  ***/
    void makeEmpty();
    void insert(const Comparable& element);
    void insert(Comparable&& element);
    void remove(const Comparable& element);
    void remove(Comparable&& element);

    BinarySearchTree& operator= (const BinarySearchTree& rhs);
    BinarySearchTree& operator= (BinarySearchTree&& rhs);

private:
    struct BinaryNode{
        Comparable element;
        BinaryNode* right;
        BinaryNode* left;

        explicit BinaryNode(const Comparable& element):element{element}{};
        explicit BinaryNode(Comparable&& element):element{std::move(element)} {};

        void setLeft (Comparable* node) {left = node;};
        void setRight (Comparable* node) {right  = node;};
    };

    BinaryNode* root;

    /*** Constant Private Methods ***/
    BinaryNode* findMin(BinaryNode* tree) const;
    BinaryNode* findMax(BinaryNode* tree) const;
    BinaryNode* clone(BinaryNode* tree) const;
    bool contains(BinaryNode* tree) const;
    bool isEmtpy(BinaryNode* tree) const;
    void printTree(BinaryNode* tree) const;

    /*** Non-Constant Private Methods ***/
    void insert(const Comparable& value, BinaryNode*& tree);
    void insert(Comparable&& value, BinaryNode*& tree);
    void remove(const Comparable& value,BinaryNode*& tree);
    void makeEmpty(BinaryNode* tree);
};

#endif //DATA_STRUCTURES_AND_ALGORITHM_ANALYSIS_IN_C_BINARYSEARCHTREE_H
