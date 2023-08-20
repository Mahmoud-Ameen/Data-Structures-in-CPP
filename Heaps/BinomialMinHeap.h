/**
 * @file BinomialMinHeap.h
 * @brief Binomial Min Heap Implementation
 *
 * Description:
 * This is a templated C++ implementation of a binomial min heap data structure. A binomial min heap
 * is a collection of binomial trees, where each tree follows the binomial heap property: the value
 * of each node is less than or equal to the values of its children. This structure provides
 * efficient access to the minimum element.
 *
 * Usage:
 * - Instantiate a BinomialMinHeap object using the constructor.
 * - Use the insert() method to add elements to the heap.
 * - Use the getMin() method to get the minimum element without removing it.
 * - Use the deleteMin() method to remove the minimum element without returning it.
 * - Use the extractMin() method to get and remove the minimum element.
 * - Use the size() method to get the current size of the heap.
 * - Use the isEmpty() method to check if the heap is empty.
 *
 * @note:
 * This implementation assumes that the items are comparable and provides a basic
 * demonstration of a binomial min heap. Depending on your needs, you may want to
 * extend it to include additional functionality or error handling.
 *
 * @author: Mahmoud Ashraf
 * @date 18/8/2023
 */

#ifndef DSA_BINOMIALMINHEAP_H
#define DSA_BINOMIALMINHEAP_H

#include <utility>
#include <vector>
#include <cmath>

template<typename Comparable>
class BinomialMinHeap {
public:
    /*region Big Five */

    // Default constructor
    BinomialMinHeap() = default;

    // Copy constructor
    BinomialMinHeap(const BinomialMinHeap& other);

    // Move constructor
    BinomialMinHeap(BinomialMinHeap&& other) noexcept;

    // Copy assignment operator
    BinomialMinHeap& operator=(const BinomialMinHeap& other);

    // Move assignment operator
    BinomialMinHeap& operator=(BinomialMinHeap&& other) noexcept;

    // Destructor
    ~BinomialMinHeap();

    /*endregion*/

    /*region Public constant methods*/

    /**
     * @brief Returns the minimum value in the binomial heap.
     *
     * This function returns the minimum value present in the binomial heap without
     * modifying the heap's structure.
     *
     * @return The minimum value in the binomial heap.
     * @throws std::underflow_error If the heap is empty.
     */
    Comparable getMin() const;

    /**
     * @brief Checks if the binomial heap is empty.
     *
     * This function checks whether the binomial heap is empty, i.e., it contains no elements.
     *
     * @return True if the binomial heap is empty, false otherwise.
     */
    [[nodiscard]] bool isEmpty() const;

    /**
     * @brief gets the number of elements in the heap
     * @return number of elements in the heap
     * */
    [[nodiscard]] int size() const;

    /*endregion*/

    /* region Public non-constant methods*/

    /**
     * @brief Inserts a new element into the binomial heap.
     *
     * This function inserts a new element with the given value into the binomial heap.
     * It creates a new binomial tree with a single node and merges it into the heap's
     * forest vector while maintaining the heap's properties.
     *
     * @param element The element to be inserted.
     */
    void insert(const Comparable& element);
    /**
     * @brief Inserts a new element into the binomial heap.
     *
     * This function inserts a new element with the given value into the binomial heap.
     * It creates a new binomial tree with a single node and merges it into the heap's
     * forest vector while maintaining the heap's properties.
     *
     * @param element The element to be inserted.
     */
    void insert(Comparable&& element);

    /**
     * @brief Merges another binomial heap into the current heap.
     *
     * This function merges the content of another binomial heap into the current heap.
     * It combines the root lists of both heaps, maintaining the proper order of binomial trees
     * and preserving the binomial heap properties.
     *
     * @param heap The binomial heap to be merged into the current heap. After merging,
     *             the merged heap will be empty.
     */
    void merge(BinomialMinHeap& heap);

    /**
     * @brief Deletes the minimum element from the binomial heap.
     *
     * This function removes the minimum element from the binomial heap, restructures
     * the heap as necessary to maintain the heap properties, and releases the memory
     * associated with the deleted node. It handles merging trees and updating the root list.
     *
     * @throws std::underflow_error If the heap is empty.
     */
    void deleteMin();

    /**
     * @brief Extracts and returns the minimum element from the binomial heap.
     *
     * This function removes the minimum element from the binomial heap, restructures
     * the heap as necessary to maintain the heap properties, and returns the extracted
     * minimum value. It handles merging trees and updating the root list.
     *
     * @return The minimum value that was extracted from the heap.
     * @throws std::underflow_error If the heap is empty.
     */
    Comparable extractMin();

    /*endregion*/

private:
    struct BinomialTreeNode;
    int mSize = 0; // number of elements in heap
    /*
     * vector of binomial tree pointers. where position with index i
     * represents a pointer to a binomial tree of order i.
     * a nullptr indicates there is no binomial tree of this order in this heap.
     * */
    std::vector<BinomialTreeNode*> forest;


    /* region Private constant methods*/

    /**
     * @brief Finds the index of the minimum node in the binomial heap's forest vector.
     *
     * This private function iterates through the binomial heap's forest vector and
     * finds the index of the minimum node based on the node's data value. If the heap
     * is empty, it returns -1.
     *
     * @return The index of the minimum node, or -1 if the heap is empty.
     */
    [[nodiscard]] int minNodeIndex() const;

    /**
     * @brief Creates a deep copy of a binomial tree.
     *
     * This private method recursively creates a deep copy of a binomial tree by cloning
     * each node, its left child, and its siblings. The cloned tree is independent from
     * the original tree and can be modified without affecting it.
     *
     * @param tree The root node of the binomial tree to be cloned.
     * @return A pointer to the root node of the cloned tree, or nullptr if the input tree is nullptr.
     */
    BinomialTreeNode * cloneTree(const BinomialMinHeap::BinomialTreeNode *tree) const;

    /*endregion*/

    /* region Private non-constant methods*/

    /**
     * @brief Merges a vector of binomial trees into the current heap's forest.
     *
     * This function takes a vector of binomial trees and merges each tree into the
     * current heap's forest vector while maintaining the proper order and structure
     * of the heap. After merging, the trees in the otherForest vector are set to nullptr
     * to prevent double memory de-allocation.
     *
     * @pre This function assumes this->forest and otherForest are vectors of binomial tree pointers
     * where each index in the vector represents a binomial tree of order index.
     * Nullptr in the ith place indicates that the forest has no binomial tree of order i.
     *
     * @param otherForest The vector of binomial trees to be merged. After merging, the trees
     *                    in this vector will be set to nullptr.
     */
    void mergeForest(std::vector<BinomialTreeNode *> &otherForest);

    /**
     * @brief Clears the content of a vector of binomial trees and resets forest mSize to zero.
     *
     * This method iterates through the vector of binomial trees, invoking the private
     * makeEmpty function on each tree to clear its content and deallocate memory. After
     * clearing the trees, the vector of trees is emptied, and the forest mSize is reset to zero.
     *
     * @param trees The vector of binomial trees to be cleared.
     */
    void clearForest(std::vector<BinomialTreeNode*>& trees);

    /**
     * @brief Inserts a binomial tree into the heap's forest vector.
     *
     * This function inserts a binomial tree into the current heap's forest vector,
     * ensuring that the order of trees is maintained and binomial heap properties
     * are preserved.
     *
     * @param treeNode The binomial tree to be inserted.
     */
    void insertTree(BinomialTreeNode* treeNode);

    /**
     * @brief Combines two binomial trees of the same order.
     *
     * This function combines two binomial trees by making one tree the child of the other,
     * while maintaining the binomial heap properties. The tree with the smaller root value
     * becomes the parent.
     *
     * @param first The first binomial tree.
     * @param second The second binomial tree.
     * @return The merged binomial tree.
     */
    BinomialTreeNode * combineTrees(BinomialTreeNode* first,BinomialTreeNode* second);

    /**
     * @brief Recursively clears the content of a binomial tree and deallocates memory.
     *
     * This function traverses a binomial tree in a recursive manner, clearing the
     * content of each node and deallocating the memory associated with it. It starts
     * by clearing the left child and sibling nodes before deallocating memory for the
     * current node itself.
     *
     * @param tree The root node of the binomial tree to be emptied.
     */
    void makeEmpty(BinomialTreeNode* tree);

    /*endregion*/

};

/* region Internal struct BinomialTreeNode  */

//
template<typename Comparable>
struct BinomialMinHeap<Comparable>::BinomialTreeNode{
public:
    Comparable data;
    BinomialTreeNode* leftChild;
    BinomialTreeNode* nextSibling;
    int order = 0;

    explicit BinomialTreeNode(const Comparable& data,BinomialTreeNode* leftChild = nullptr,BinomialTreeNode* nextSibling = nullptr)
            : data(data),leftChild(leftChild),nextSibling(nextSibling){};

    explicit BinomialTreeNode(Comparable && data,BinomialTreeNode* leftChild = nullptr, BinomialTreeNode* nextSibling = nullptr)
            : data(std::move(data)),leftChild(leftChild),nextSibling(nextSibling) {};

    BinomialTreeNode() = default;
};
/*endregion*/

/*region PUBLIC*/

/*region Big Five*/

// Copy constructor
template<typename Comparable>
BinomialMinHeap<Comparable>::BinomialMinHeap(const BinomialMinHeap& other) {

    // Perform deep copy of the other heap's state

    // Clone each tree in the other heap's forest and add to this heap
    for (const BinomialTreeNode* tree : other.forest) {
        auto clonedTree = cloneTree(tree);
        forest.push_back(clonedTree);
    }

    // Copy other heap's mSize
    mSize = other.mSize;
}

// Move constructor
template<typename Comparable>
BinomialMinHeap<Comparable>::BinomialMinHeap(BinomialMinHeap&& other) noexcept
        : forest(std::move(other.forest)), mSize(other.mSize) {
    // Reset other's state to leave it in a valid but unspecified state

    other.forest.clear();
    other.mSize = 0;
}

// Copy assignment operator
template<typename Comparable>
BinomialMinHeap<Comparable>& BinomialMinHeap<Comparable>::operator=(const BinomialMinHeap& other) {
    if (this != &other) {
        // Perform deep copy of the other heap's state

        // Clear the current heap's content
        clearForest(forest);

        // Clone each tree in the other heap's forest and add to this heap
        for (int order = 0; order < other.forest.size(); ++order) {
            forest.push_back(cloneTree(other.forest[order]));
        }

        // Copy other heap's mSize
        mSize = other.mSize;    }
    return *this;
}

// Move assignment operator
template<typename Comparable>
BinomialMinHeap<Comparable>& BinomialMinHeap<Comparable>::operator=(BinomialMinHeap&& other) noexcept {
    if (this != &other) {
        // Release current resources
        clearForest(forest);

        // Transfer ownership of resources from other to this
        forest = std::move(other.forest);
        mSize = other.mSize;

        // Reset other's state
        other.mSize = 0;

    }
    return *this;
}

// Destructor
template<typename Comparable>
BinomialMinHeap<Comparable>::~BinomialMinHeap() {
    clearForest(forest);
}
/*endregion*/

/*region Public Const Methods*/

template<typename Comparable>
Comparable BinomialMinHeap<Comparable>::getMin() const {
    if (isEmpty()) throw std::underflow_error("Cannot find minimum element; Heap is empty!\n");

    auto index = minNodeIndex();
    return forest[index]->data;
}

template<typename Comparable>
bool BinomialMinHeap<Comparable>::isEmpty() const {
    return mSize == 0;
}

template<typename Comparable>
int BinomialMinHeap<Comparable>::size() const{
    return mSize;
};

/*endregion*/

/* region Public Non-Const Methods */

template<typename Comparable>
void BinomialMinHeap<Comparable>::insert(Comparable&& element){
    insert(element);
}

template<typename Comparable>
void BinomialMinHeap<Comparable>::insert(const Comparable &element) {
    auto newTree = new BinomialTreeNode(element);
    insertTree(newTree);
}

template<typename Comparable>
void BinomialMinHeap<Comparable>::merge(BinomialMinHeap &heap) {
    mergeForest(heap.forest);
}

template<typename Comparable>
void BinomialMinHeap<Comparable>::deleteMin() {
    // If heap is empty, throw underflow error
    if(mSize == 0) throw std::underflow_error("Cannot delete an element from an empty Heap.\n");


    // find the tree with minimum root node, delete it while keeping track of its children
    BinomialTreeNode* minRoot = forest[minNodeIndex()];

    std::vector<BinomialTreeNode*> deletedRootChildren;
    deletedRootChildren.resize(minRoot->order + 2, nullptr);
    mSize-=pow(2, minRoot->order);

    auto child = minRoot->leftChild;

    forest[minRoot->order] = nullptr;
    delete minRoot;

    // Create a forest from deleted Node's children and merge it with current forest
    while(child){
        deletedRootChildren[child->order] = (child);
        auto nextChild = child->nextSibling;
        child->nextSibling = nullptr;
        child = nextChild;
    }
    mergeForest(deletedRootChildren);

}

template<typename Comparable>
Comparable BinomialMinHeap<Comparable>::extractMin() {
    if(isEmpty()) throw std::underflow_error("Heap is empty\n");

    // Get minimum element in heap before deleting it
    Comparable minValue = forest[minNodeIndex()]->data;
    deleteMin();

    return minValue;
}


template<typename Comparable>
typename BinomialMinHeap<Comparable>::BinomialTreeNode *
BinomialMinHeap<Comparable>::combineTrees(BinomialMinHeap::BinomialTreeNode *first, BinomialMinHeap::BinomialTreeNode *second) {
    // Make sure no nullptr are passed to avoid runtime errors
    if(!first && !second) return nullptr;
    if(!first) return second;
    if(!second) return first;

    // make [second] be the tree with the larger root
    if(first->data > second->data){
        std::swap(first,second);
    }

    second->nextSibling = first->leftChild;
    first->leftChild = second;
    first->order++;

    return first;
}


/*endregion*/

/*endregion PUBLIC*/

/*region PRIVATE*/

/*region Private Const Methods */

template<typename Comparable>
int BinomialMinHeap<Comparable>::minNodeIndex() const {
    BinomialTreeNode* min = nullptr;
    int minIndex = -1;

    for (int i = 0; i < forest.size(); ++i) {
        auto node = forest[i];
        if (node && (!min || node->data < min->data)) {
            min = node;
            minIndex = i;
        }

    }

    return minIndex;
}


template<typename Comparable>
typename BinomialMinHeap<Comparable>::BinomialTreeNode *
BinomialMinHeap<Comparable>::cloneTree(const BinomialMinHeap::BinomialTreeNode *tree) const {
    if (!tree) {
        return nullptr;
    }

    // Create a new node with the same data.
    auto* newNode = new BinomialTreeNode(tree->data);

    // Recursively clone left child and siblings.
    newNode->leftChild = cloneTree(tree->leftChild);
    newNode->nextSibling = cloneTree(tree->nextSibling);
    newNode->order = tree->order;

    return newNode;
}

/*endregion*/

/*region Private non-const methods*/

template<typename Comparable>
void BinomialMinHeap<Comparable>::insertTree(BinomialMinHeap::BinomialTreeNode *treeNode) {
    if(!treeNode) return;

    int treeOrder = treeNode->order;
    mSize+=pow(2, treeOrder);

    while(treeOrder < forest.size() && forest[treeOrder] != nullptr){
        // Merge trees of same order resulting in a new tree of [initial order + 1]
        treeNode = combineTrees(forest[treeOrder], treeNode);
        // clear the slot after merging
        forest[treeOrder] = nullptr;
        treeOrder++;
    }

    // reached the end of the vector
    if(treeOrder == forest.size()){
        forest.push_back(treeNode);
    }
    // reached an empty slot
    else {
        forest[treeOrder] = treeNode;
    }

}


template<typename Comparable>
void BinomialMinHeap<Comparable>::mergeForest(std::vector<BinomialTreeNode *> &otherForest) {

    // Call insertTree method to insert each valid binomial tree in other to current forest
    int order = 0;
    while(order < otherForest.size()){
        if(otherForest[order]){
            insertTree(otherForest[order]);
            // Clear other forest to avoid two heaps sharing same state,
            // Potentially causing multiple memory de-allocation for same trees
            otherForest[order] = nullptr;
        }
        order++;
    }
}

template<typename Comparable>
void BinomialMinHeap<Comparable>::makeEmpty(BinomialMinHeap::BinomialTreeNode *tree) {
    if (!tree) {
        return;
    }

    // Recursively clear left child and siblings.
    makeEmpty(tree->leftChild);
    makeEmpty(tree->nextSibling);

    // Deallocate memory for the current node.
    delete tree;
}


template<typename Comparable>
void BinomialMinHeap<Comparable>::clearForest(std::vector<BinomialTreeNode *> &trees) {
    for (BinomialTreeNode* tree : trees) {
        makeEmpty(tree);
    }
    trees.clear();
}


/*endregion*/

/*endregion PRIVATE*/


#endif //DSA_BINOMIALMINHEAP_H
