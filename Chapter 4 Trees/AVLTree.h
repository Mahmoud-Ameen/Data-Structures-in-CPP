// AVLTree.h
//
// AVLTree - A self-balancing binary search tree implementation (AVL tree).
// An AVL tree is a balanced binary search tree that maintains its height
// to be logarithmic, ensuring efficient insertion, removal, and search operations.
//
// This header file defines the AVLTree class, which provides a templated implementation
// of an AVL tree. The class supports insertion, removal, search, finding minimum and
// maximum elements, checking if the tree is empty, printing the tree, and more.
//
// The AVLTree class uses a struct named AVLNode to represent each node in the tree.
// Each AVLNode contains a comparable value and pointers to its left and right child nodes.
// The AVL tree automatically balances itself to ensure that the difference in heights
// between the left and right subtrees of any node is at most 1, maintaining the AVL
// tree property and guaranteeing efficient operations.
//
// Usage example:
// --------------
// AVLTree<int> avlTree;
// avlTree.insert(5);
// avlTree.insert(10);
// avlTree.insert(3);
// avlTree.remove(5);
// if (avlTree.contains(10)) {
//     std::cout << "10 is in the AVL tree!" << std::endl;
// }
// avlTree.printTree();
//
// The AVLTree class allows insertion and removal of elements while keeping the tree balanced,
// providing fast search and retrieval of elements with logarithmic time complexity.
//
// Note: The Comparable type must support comparison operators (>, <, >=, <=) for proper functionality.
//
// This code is designed for educational purposes and can be freely used and modified.
// Refer to the GitHub repository for the full code and documentation:
// https://github.com/Mahmoud-Ameen/Data-Structures-and-Algorithm-Analysis-in-CPP
//
// Created by Mahmoud Ashraf on 7/22/2023.

#ifndef DSA_AVLTREE_H
#define DSA_AVLTREE_H

#include <iostream>

template <typename Comparable>
class AVLTree {
private:

    /**
     * @struct AVLNode
     * @brief A struct representing a node in an AVL tree.
     *
     * This struct represents a single node in an AVL tree, a self-balancing binary search tree.
     * Each node holds a value of a comparable type, and pointers to its left and right child nodes.
     * Additionally, it keeps track of the height of the node, which is used for balancing the tree.
     *
     * @tparam Comparable The type of the value held by the node, which must be comparable using comparison operators.
     */
    struct AVLNode {
        /**
         * @brief Constructs an AVLNode with the given value.
         * @param value The value to be stored in the node.
         */
        explicit AVLNode(Comparable value): value{value}{}

        Comparable value;
        int height = 0;
        AVLNode* right = nullptr;
        AVLNode* left = nullptr ;
    };

public:
    /** Constructors */

    // default constructor
    AVLTree() = default;
    // Copy constructor. Performs a deep copy.
    AVLTree(const AVLTree& rhs);
    // Move Constructor
    AVLTree(AVLTree&& rhs) noexcept;
    // Destructor
    ~AVLTree();

    /** Const Methods */
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
    /**
     * @brief clears the tree.
     * */
    void makeEmpty();

    /** Non-Const Methods */
    /**
     * @brief Inserts a value into the AVL tree.
     * @param value The value to be inserted.
     */
    void insert(const Comparable& value);
    /**
     * @brief Overload of insert() for rvalue references.
     * @param value The rvalue reference to the value to be inserted.
     */
    void insert(Comparable&& value);
    /**
     * @brief Removes a value from the AVL tree.
     * @param value The value to be removed.
     */
    void remove(const Comparable& value);
    /**
      * @brief Overload of remove() for rvalue references.
      * @param value The rvalue reference to the value to be removed.
      */
    void remove(Comparable&& value);

private:
    /*** Private Members ***/
    AVLNode* root = nullptr;

    /*** Static Members ***/
    static const int ALLOWED_IMBALANCE = 1;

    /*** Static Helper Methods ***/

    /**
     * @brief Get the height of a given node in the AVL tree.
     *
     * @param node Pointer to the node for which height needs to be calculated.
     * @return The height of the node if it exists, otherwise -1.
     */
    static int getHeight(const AVLNode *node);
    /**
     * @brief Get the balance factor of a given node in the AVL tree.
     *
     * The balance factor is the difference between the height of the left subtree
     * and the height of the right subtree of the given node.
     *
     * @param node Pointer to the node for which the balance factor needs to be calculated.
     * @return The balance factor of the node.
     */
    static int getBalanceFactor(const AVLNode *node);
    /**
     * @brief Check if a given node is right-heavy in the AVL tree.
     *
     * A node is considered right-heavy if its balance factor is less than ALLOWED_IMBALANCE * -1.
     *
     * @param node Pointer to the node to be checked.
     * @return True if the node is right-heavy, otherwise false.
     */
    static bool isRightHeavy(const AVLNode *node);
    /**
     * @brief Check if a given node is left-heavy in the AVL tree.
     *
     * A node is considered left-heavy if its balance factor is greater than ALLOWED_IMBALANCE.
     *
     * @param node Pointer to the node to be checked.
     * @return True if the node is left-heavy, otherwise false.
     */
    static bool isLeftHeavy(const AVLNode *node);
    /**
     * @brief Calculate and set the height of a given node in the AVL tree.
     *
     * The height of a node is the maximum height of its left and right subtrees plus 1.
     *
     * @param node Pointer to the node for which the height needs to be updated.
     */
    static void setHeight(AVLNode *node);

    /**
     * @brief Set the height of a given node in the AVL tree.
     *
     * The height of a node is the maximum height of its left and right subtrees plus 1.
     *
     * @param node Pointer to the node for which the height needs to be updated.
     */
    static void makeEmpty(AVLNode*& node);

    /**
     * @brief Find the node with the minimum value starting from the given node in the AVL tree.
     *
     * @param node Pointer to the node from which the search for the minimum node begins.
     * @return Pointer to the node with the minimum value.
     */
    static const AVLNode * findMin(const AVLNode *node);

    /**
     * @brief Find the node with the maximum value starting from the given node in the AVL tree.
     *
     * @param node Pointer to the node from which the search for the maximum node begins.
     * @return Pointer to the node with the maximum value.
     */
    static AVLNode* findMax(const AVLNode *node);

    /**
     * @brief Recursively clone the AVL tree with the given tree root.
     *
     * This function creates a deep copy of the AVL tree starting from the given tree root.
     *
     * @param treeRoot Pointer to the root node of the tree to be cloned.
     * @return Pointer to the root node of the cloned tree.
     */
    static AVLNode* clone(const AVLNode *treeRoot);

    /**
     * @brief Check if the AVL tree starting from the given node contains the specified value.
     *
     * This function is used to check whether the AVL tree contains the specified value
     * by recursively searching through the tree.
     *
     * @param node Pointer to the node from which the search for the value begins.
     * @param value The value to be searched for in the AVL tree.
     * @return True if the value is found, otherwise false.
     */
    static bool contains(const AVLNode*& node, Comparable value);

    /**
     * @brief Print the AVL tree starting from the given node.
     *
     * This function is used to print the AVL tree in a hierarchical format
     * by recursively traversing the tree.
     *
     * @param treeRoot Pointer to the root node of the tree to be printed.
     * @param depth The depth of the current node in the tree (used for indentation).
     */
    static void printTree(const AVLNode *treeRoot, int depth);

    /*** Private Member Methods ***/

    /**
    * @brief Inserts a value into the AVL tree starting from the given node.
    * @param value The value to be inserted.
    * @param node The current node being considered for insertion.
    */
    void insert(const Comparable& value, AVLTree::AVLNode *&node);

    /**
     * @brief Balances the AVL tree starting from the given node.
     * @param node The current node being considered for balancing.
     */
    void balance(AVLNode *&node);

    /**
     * @brief Performs a right rotation on the AVL tree rooted at the given node.
     * @param node The current node being considered for the right rotation.
     */
    void rightRotate(AVLNode*& node);

    /**
     * @brief Performs a left rotation on the AVL tree rooted at the given node.
     * @param node The current node being considered for the left rotation.
     */
    void leftRotate(AVLNode*& node);

    /**
     * @brief Removes a value from the AVL tree starting from the given node.
     * @param value The value to be removed.
     * @param node The current node being considered for removal.
     */
    void remove(const Comparable& value,AVLNode*& node);

    /**
     * @brief Removes a node from the AVL tree rooted at the given node.
     * @param node The current node being considered for removal.
     */
    void removeNode(AVLNode*& node);
};

/*** region Static Helper Methods  ***/
template <typename Comparable>
int AVLTree<Comparable>::getHeight(const AVLNode *node) {
    return node ?  node->height : -1;
}

template <typename Comparable>
void AVLTree<Comparable>::setHeight(AVLNode *node) {
    if(node)
        node->height = 1 + std::max(getHeight(node->right), getHeight(node->left));
}

template <typename Comparable>
int AVLTree<Comparable>::getBalanceFactor(const AVLNode *node){
    if(!node) return 0;
    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);

    return leftHeight - rightHeight;
}

template <typename Comparable>
bool AVLTree<Comparable>::isRightHeavy(const AVLNode *node){
    return getBalanceFactor(node) < ALLOWED_IMBALANCE * -1;
}

template <typename Comparable>
bool AVLTree<Comparable>::isLeftHeavy(const AVLNode *node){
    return getBalanceFactor(node) > ALLOWED_IMBALANCE;
}

template<typename Comparable>
void AVLTree<Comparable>::makeEmpty(AVLTree::AVLNode *&node) {
    if(!node) return;

    // Empty the children
    makeEmpty(node->right);
    makeEmpty(node->left);

    // Delete the node content
    delete(node);
    node = nullptr;
}

template<typename Comparable>
const typename AVLTree<Comparable>::AVLNode * AVLTree<Comparable>::findMin(const AVLNode *node) {
    if(!node->left) return node;

    return findMin(node->left);
}

template<typename Comparable>
typename AVLTree<Comparable>::AVLNode* AVLTree<Comparable>::findMax(const AVLNode *node) {
    if(!node->right) return node;
    return findMax(node->right);

}

template<typename Comparable>
typename  AVLTree<Comparable>::AVLNode* AVLTree<Comparable>::clone(const AVLNode *treeRoot){
    if(!treeRoot) return nullptr;

    auto node = new AVLNode(treeRoot->value); // Copy the value of treeRoot to a new node.
    node->right = clone(treeRoot->right); // Recursively clone the right subtree.
    node->left = clone(treeRoot->left);   // Recursively clone the left subtree.

    return node;
}

template<typename Comparable>
bool AVLTree<Comparable>::contains(const AVLNode *&node, Comparable value) {
    if(!node) return false;
    if(value > node->value) return contains(node->right, value);
    if(value < node->value) return contains(node->left, value);

    // value found
    return true;
}

template<typename Comparable>
void AVLTree<Comparable>::printTree(const AVLNode *treeRoot, int depth) {
    if(!treeRoot) return;

    for (int i = 0; i < depth; ++i) {
        std::cout <<"  ";
    }
    std::cout << treeRoot->value << '\n';

    printTree(treeRoot->left, depth+1);
    printTree(treeRoot->right, depth+1);

}

/* endregion */

/*** region Constructors ***/

/* Copy Constructor */
template<typename Comparable>
AVLTree<Comparable>::AVLTree(const AVLTree& rhs) {
    root = clone(rhs.root);
}

/* Move Constructor */
template<typename Comparable>
AVLTree<Comparable>::AVLTree(AVLTree&& rhs)  noexcept {
    root = rhs.root;
    rhs.root = nullptr;
}

/* Destructor */
template<typename Comparable>
AVLTree<Comparable>::~AVLTree() {
    makeEmpty();
}
/* endregion */

/*** region Private Member Methods ***/

template<typename Comparable>
void AVLTree<Comparable>::balance(AVLNode *& node) {
    /*
     * If the tree is left heavy, there are two cases:
     * 1) If left subtree is left heavy (insertion done to the outside),
     *  a single rotation is performed (right rotation)
     * 2) If left subtree is right heavy (insertion done to the inside),
     *  a double rotation is performed (left-right rotation)
     *
     * If the tree is right heavy, there are two similar cases:
     * 1) If right subtree is right heavy (insertion done to the outside),
     *  a single rotation is performed (left rotation)
     * 2) If right subtree is left heavy (insertion done to the inside),
     *  a double rotation is performed (right-left rotation)
     * */

    if(isLeftHeavy(node)){
        if(getBalanceFactor(node->left) < 0 )
            leftRotate(node->left);

        rightRotate(node);

    }else if(isRightHeavy(node)){
        if(getBalanceFactor(node->right) > 0) {
            rightRotate(node->right);
        }
        leftRotate(node);
    }
};

template<typename Comparable>
void AVLTree<Comparable>::insert(const Comparable &value, AVLTree::AVLNode *&node) {
    // Base condition
    if(!node) {
        node = new AVLNode(value);
        return;
    }

    // If value greater than current node,
    // Call the function recursively to the right child
    if(value > node->value){
        insert(value,node->right);
     }

    // If value less than current node,
    // Call the function recursively to the left child
    else if(value < node->value){
        insert(value,node->left);
    }

    // After inserting the node to either side,
    // Reset the height of each parent tree
    setHeight(node);

    // Make sure each subTree is balanced
    balance(node);

}

template <typename Comparable>
void AVLTree<Comparable>::rightRotate(AVLNode*& node) {
    auto newRoot = node->left;
    node->left = newRoot->right;
    newRoot->right = node;

    // reset the height of the root and new root
    setHeight(node);
    setHeight(newRoot);

    // sets the root to be the new root
    node = newRoot;
}

template<typename Comparable>
void AVLTree<Comparable>::leftRotate(AVLNode*& node) {

    auto newRoot = node->right;
    node->right = newRoot->left;
    newRoot->left = node;

    setHeight(node);
    setHeight(newRoot);

    node = newRoot;

}

template<typename Comparable>
void AVLTree<Comparable>::removeNode(AVLNode*& node) {
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
void AVLTree<Comparable>::remove(const Comparable &value, AVLNode*& node) {
    // Node with the given value not found in the tree.
    if (!node ) {
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

    // After removing the node, update the height of the current node
    setHeight(node);

    // Perform balancing operations to restore the AVL property
    balance(node);
}


/*endregion*/

/*** region Non-Constant Public Methods  ***/
template<typename Comparable>
void AVLTree<Comparable>::insert(const Comparable& value){
    insert(value,root);
};

template<typename Comparable>
void AVLTree<Comparable>::insert(Comparable&& value){
    insert(std::move(value),root);
};

template<typename Comparable>
void AVLTree<Comparable>::remove(const Comparable &value) {
    remove(value,root);
}

template<typename Comparable>
void AVLTree<Comparable>::remove(Comparable && value) {
    remove(std::move(value),root);
}

/* endregion */

/*** region Constant Public Methods ***/
template <typename Comparable>
const Comparable& AVLTree<Comparable>::findMin() const{
    return findMin(root);
};

template <typename Comparable>
const Comparable& AVLTree<Comparable>::findMax() const{
    return findMax(root);
};

template<typename Comparable>
bool AVLTree<Comparable>::contains(const Comparable &value) const {
    return contains(root, value);
}
template<typename Comparable>
bool AVLTree<Comparable>::contains(Comparable &&value) const {
    return contains(root,std::move(value));
}

template<typename Comparable>
bool AVLTree<Comparable>::isEmpty() const {
    return root == nullptr;
}

template<typename Comparable>
void AVLTree<Comparable>::printTree() const {
    printTree(root, 0);
}

template<typename Comparable>
void AVLTree<Comparable>::makeEmpty() {
    makeEmpty(root);
}
/* endregion */

#endif //DSA_AVLTREE_H
