// BinarySearchTree - A binary search tree implementation (BST).
// A binary search tree is a data structure that allows efficient insertion,
// removal, and search operations on a sorted collection of elements. In a BST,
// each node has at most two children - a left child and a right child. The nodes
// are arranged in a way that satisfies the binary search tree property: for every
// node in the tree, all nodes in its left subtree have values less than the node's
// value, and all nodes in its right subtree have values greater than the node's value.
//
// This header file defines the BinarySearchTree class, which provides a templated implementation
// of a binary search tree. The class supports insertion, removal, search, finding minimum and
// maximum elements, checking if the tree is empty, printing the tree, and more.
//
// The BinarySearchTree class uses a struct named BinaryNode to represent each node in the tree.
// Each BinaryNode contains a comparable value and pointers to its left and right child nodes.
// This class does not enforce any balancing mechanism, so its performance can degrade to O(n)
// in the worst-case scenario, where n is the number of elements. However, it's suitable for
// smaller collections and serves as a foundation for more advanced self-balancing trees like AVL or Red-Black trees.
//
// Usage example:
//
// --------------
// BinarySearchTree<int> bst;
// bst.insert(5);
// bst.insert(10);
// bst.insert(3);
// bst.remove(5);
// if (bst.contains(10)) {
//     std::cout << "10 is in the BST!" << std::endl;
// }
// bst.printTree();
//
// The BinarySearchTree class allows insertion and removal of elements, providing
// moderate search and retrieval performance with average time complexity of O(log n),
// where n is the number of elements in the tree.
//
// Note: The Comparable type must support comparison operators (>, <, >=, <=) for proper functionality.
//
// This code is designed for educational purposes and can be freely used and modified.
// Refer to the GitHub repository for the full code and documentation:
// https://github.com/Mahmoud-Ameen/Data-Structures-and-Algorithm-Analysis-in-CPP
//
// Created by Mahmoud Ashraf on 7/19/2023.

#ifndef DATA_STRUCTURES_AND_ALGORITHM_ANALYSIS_IN_C_BINARYSEARCHTREE_H
#define DATA_STRUCTURES_AND_ALGORITHM_ANALYSIS_IN_C_BINARYSEARCHTREE_H

#include <iostream>
#include <algorithm>

template<typename Comparable>
class BinarySearchTree {
public:
    BinarySearchTree();                                    // default constructor
    BinarySearchTree(const BinarySearchTree& rhs);         // copy constructor
    BinarySearchTree(BinarySearchTree&& rhs) noexcept;     // move constructor
    ~BinarySearchTree();                                   // destructor

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
     * @brief searches the tree for an value.
     * @param value Comparable to be searched for.
     * @return true if found, otherwise false.
     * */
    bool contains(const Comparable& value) const;
    bool contains(Comparable &&value) const;
    /**
     * @brief Checks if the tree is empty.
     * @return true if empty, otherwise false.
     * */
    [[nodiscard]] bool isEmpty() const;
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
     * @brief inserts an value to the tree.
     * if value already exists, nothing happens.
     * */
    void insert(const Comparable& value);
    void insert(Comparable&& value);
    /**
     * @brief removes an value from the tree
     * if the value doesn't exist, nothing happens.
     * */
    void remove(const Comparable& value);
    void remove(Comparable&& value);

    // copy assignment operator
    BinarySearchTree& operator= (const BinarySearchTree& rhs);
    // move assignment operator
    BinarySearchTree& operator= (BinarySearchTree&& rhs) noexcept;

private:
    struct BinaryNode{
        Comparable value;
        BinaryNode* right = nullptr;
        BinaryNode* left = nullptr;

        explicit BinaryNode(const Comparable& value): value{value}{};
        explicit BinaryNode(Comparable&& value): value{std::move(value)} {};
    };

    /*** Private Members ***/
    BinaryNode* root;

    /*** Constant Private Methods ***/
    BinaryNode* findMin(BinaryNode* node) const;
    BinaryNode* findMax(BinaryNode* node) const;
    BinaryNode* clone(BinaryNode* treeRoot) const;
    bool contains(BinarySearchTree::BinaryNode *node, Comparable value) const;
    void printTree(BinaryNode *treeRoot, int depth) const;

    /*** Non-Constant Private Methods ***/
    void insert(const Comparable& value, BinaryNode*& treeRoot);
    void insert(Comparable&& value, BinaryNode*& tree);
    void remove(const Comparable& value,BinaryNode*& node);
    void removeNode(BinaryNode*& node);
    void makeEmpty(BinarySearchTree::BinaryNode *&node);
};

/*** Constructors & Destructor ***/
/* region */

/* Default constructor */
template<typename Comparable>
BinarySearchTree<Comparable>::BinarySearchTree() {
    root = nullptr;
}

/* Copy Constructor */
template<typename Comparable>
BinarySearchTree<Comparable>::BinarySearchTree(const BinarySearchTree& rhs) {
    root = clone(rhs.root);
}

/* Move Constructor */
template<typename Comparable>
BinarySearchTree<Comparable>::BinarySearchTree(BinarySearchTree&& rhs)  noexcept {
    root = rhs.root;
    rhs.root = nullptr;
}

/* Destructor */
template<typename Comparable>
BinarySearchTree<Comparable>::~BinarySearchTree() {
    makeEmpty();
}

/* endregion */

/*** Public Constant Methods  ***/
/* region */
template <typename Comparable>
const Comparable& BinarySearchTree<Comparable>::findMin() const{
    return findMin(root);
};

template <typename Comparable>
const Comparable& BinarySearchTree<Comparable>::findMax() const{
    return findMax(root);
};

template<typename Comparable>
bool BinarySearchTree<Comparable>::contains(const Comparable &value) const {
    return contains(root, value);
}
template<typename Comparable>
bool BinarySearchTree<Comparable>::contains(Comparable &&value) const {
    return contains(root,std::move(value));
}

template<typename Comparable>
bool BinarySearchTree<Comparable>::isEmpty() const {
    return root == nullptr;
}

template<typename Comparable>
void BinarySearchTree<Comparable>::printTree() const {
    printTree(root, 0);
}
/* endregion */

/*** Public Non-Constant Methods ***/
/* region */
template<typename Comparable>
void BinarySearchTree<Comparable>::makeEmpty() {
    makeEmpty(root);
}

template<typename Comparable>
void BinarySearchTree<Comparable>::insert(const Comparable &value) {
    insert(value, root);
}

template<typename Comparable>
void BinarySearchTree<Comparable>::insert(Comparable &&value) {
    insert(value, root);
}

template<typename Comparable>
void BinarySearchTree<Comparable>::remove(const Comparable &value) {
    remove(value, root);
}

template<typename Comparable>
void BinarySearchTree<Comparable>::remove(Comparable &&value) {
    remove(value, root);
}

template<typename Comparable>
BinarySearchTree<Comparable> &BinarySearchTree<Comparable>::operator=(const BinarySearchTree &rhs) {
    if (this != &rhs) {
        // Clear the current tree
        makeEmpty(root);
        // Perform deep copy
        root = clone(rhs.root);
    }
    return *this;
}

template<typename Comparable>
BinarySearchTree<Comparable> &BinarySearchTree<Comparable>::operator=(BinarySearchTree &&rhs)  noexcept {
    if (this != &rhs) {
        // Clear the current tree
        makeEmpty();
        // Move ownership of resources
        root = std::exchange(rhs.root, nullptr);
    }
    return *this;
}

/* endregion */

/*** Private Constant Members ***/
/* region */
template<typename Comparable>
typename BinarySearchTree<Comparable>::BinaryNode *BinarySearchTree<Comparable>::findMin(BinarySearchTree::BinaryNode *node) const {
    if(!node->left) return node;

    return findMin(node->left);
}

template<typename Comparable>
typename BinarySearchTree<Comparable>::BinaryNode *BinarySearchTree<Comparable>::findMax(BinarySearchTree::BinaryNode *node) const {
    if(!node->right) return node;

    return findMax(node->right);
}

template<typename Comparable>
typename BinarySearchTree<Comparable>::BinaryNode *BinarySearchTree<Comparable>::clone(BinarySearchTree::BinaryNode *treeRoot) const {
    if(!treeRoot) return nullptr;

    auto node = new BinaryNode(treeRoot->value); // Copy the value of treeRoot to a new node.
    node->right = clone(treeRoot->right);// Recursively clone the right subtree.
    node->left = clone(treeRoot->left);  // Recursively clone the left subtree.

    return node;
}

template<typename Comparable>
bool BinarySearchTree<Comparable>::contains(BinarySearchTree::BinaryNode *node, Comparable value) const {
    if(!node) return false;
    if(value > node->value) return contains(node->right, value);
    if(value < node->value) return contains(node->left, value);

    // value found
    return true;
}

template<typename Comparable>
void BinarySearchTree<Comparable>::printTree(BinaryNode *treeRoot, int depth) const {
    if(!treeRoot) return;

    for (int i = 0; i < depth; ++i) {
        std::cout <<"  ";
    }
    std::cout << treeRoot->value << '\n';
    printTree(treeRoot->right, depth+1);
    printTree(treeRoot->left, depth+1);
}
/* endregion */

/*** Non-Constant Private Methods ***/
/* region */

template<typename Comparable>
void BinarySearchTree<Comparable>::insert(const Comparable &value, BinarySearchTree::BinaryNode *&treeRoot) {
    // insert the value in place
    if(!treeRoot) {
        treeRoot = new BinaryNode(value);
        return;
    }

    // if value is greater than current node, insert to the right subtree
    if(value > treeRoot->value)
        insert(value,treeRoot->right);

    // if value is less than current node, insert to the left subtree
    else if(value < treeRoot->value)
        insert(value,treeRoot->left);

    else{
        // value is equal to current node
        // nothing happens
    }
}

template<typename Comparable>
void BinarySearchTree<Comparable>::insert(Comparable &&value, BinarySearchTree::BinaryNode *&tree) {
    insert(std::move(value), tree); // Move the value into the original insert function.
}

template<typename Comparable>
void BinarySearchTree<Comparable>::removeNode(BinarySearchTree<Comparable>::BinaryNode *&node) {
    // Node is a leaf Node
    // Just delete it's content and set the pointer to nullptr
    bool isLeaf = node->left == nullptr && node->right == nullptr;
    if (isLeaf) {
        delete node;
        node = nullptr;
        return;
    }

    // Node has two children,
    // replace its content with the min node's in the right subtree and delete that node.
    // (can also be implemented by replacing its content with the max node in the left subtree)

    bool hasTwoChildren = node->left && node->right;
    if (hasTwoChildren) {
        node->value = findMin(node->right)->value;
        remove(node->value, node->right);
    }
    else {
        // Node has one child,
        // Delete the node and replace it with its child
        if (node->left) {
            auto initialLeft = node->left;
            delete node;
            node = initialLeft;
        } else if (node->right) {
            auto initialRight = node->right;
            delete node;
            node = initialRight;
        }

    }
}

template<typename Comparable>
void BinarySearchTree<Comparable>::remove(const Comparable &value, BinarySearchTree::BinaryNode *&node) {
    if (node == nullptr) {
        // Node with the given value not found in the tree.
        return;
    }

    // Node with the given value should be in the left subtree
    if (value < node->value) {
        remove(value, node->left);

    // Node with the given value should be in the right subtree
    } else if (value > node->value) {
        remove(value, node->right);

    // Found the node to be removed
    } else {
        removeNode(node);
    }
}

template<typename Comparable>
void BinarySearchTree<Comparable>::makeEmpty(BinarySearchTree::BinaryNode *&node) {
    if(!node) return;

    // Empty the children
    makeEmpty(node->right);
    makeEmpty(node->left);

    // Delete the node content
    delete(node);
    node = nullptr;
}

/* endregion */

#endif //DATA_STRUCTURES_AND_ALGORITHM_ANALYSIS_IN_C_BINARYSEARCHTREE_H
