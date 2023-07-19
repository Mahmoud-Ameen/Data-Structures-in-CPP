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
    /**
     * @return constant reference to the minimum value in the tree
     * @return nullptr if tree is empty
     * */
    const Comparable& findMin() const;
    /**
     * @return constant reference to the maximum value in the tree
     * @return nullptr if tree is empty
     * */
    const Comparable& findMax() const;
    /**
     * @brief searches the tree for an element.
     * @param element Comparable to be searched for.
     * @return true if found, otherwise false.
     * */
    bool contains(const Comparable& element) const;
    /**
     * @brief Checks if the tree is empty.
     * @return true if empty, otherwise false.
     * */
    bool isEmpty() const;
    /**
     * @brief prints the tree.
     * */
    void printTree() const;

    /*** Public Non-Constant Methods  ***/
    /**
     * @brief clears the tree.
     * */
    void makeEmpty();
    /**
     * @brief inserts an element to the tree.
     * if element already exists, nothing happens.
     * */
    void insert(const Comparable& element);
    void insert(Comparable&& element);
    /**
     * @brief removes an element from the tree
     * if the element doesn't exist, nothing happens.
     * */
    void remove(const Comparable& element);
    void remove(Comparable&& element);

    // copy assignment operator
    BinarySearchTree& operator= (const BinarySearchTree& rhs);
    // move constructor
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
