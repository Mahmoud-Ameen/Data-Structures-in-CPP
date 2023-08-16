/**
 * @brief Binary Max Heap Implementation
 *
 * Description:
 * This is a templated C++ implementation of a binary max heap data structure. A binary max heap
 * is a complete binary tree where the value of each node is larger than or equal to
 * the values of its children. This structure is useful for maintaining a collection of
 * items with quick access to the largest item.
 *
 * Usage:
 * - Instantiate a BinaryMaxHeap object using the constructor.
 * - Use the insert() method to add elements to the heap.
 * - Use the getMax() method to get the maximum element without removing it.
 * - Use the extractMax() method to get and remove the maximum element.
 * - Use the size() method to get the current size of the heap.
 * - Use the isEmpty() method to check if the heap is empty.
 *
 * @note:
 * This implementation assumes that the items are comparable and provides a basic
 * demonstration of a binary max heap. Depending on your needs, you may want to
 * extend it to include additional functionality or error handling.
 *
 * @author: Mahmoud Ashraf
 * @date 16/8/2023
 */

#ifndef DSA_BINARYMAXHEAP_H
#define DSA_BINARYMAXHEAP_H



#include <vector>
#include <iostream>

template<typename Comparable>
class BinaryMaxHeap {
public:
    /**region Constructors **/
    /*endregion*/

    /**region Constant Public Methods **/

    /**
     * @return maximum element in heap
     * **/
    Comparable getMax() const;

    /**
     * @return the current size of the heap
     */
    [[nodiscard]] int size() const;

    /**
     * @brief checks if heap is empty
     * @return true if heap is empty, false otherwise.
     * */
    [[nodiscard]] bool isEmpty() const;

    /*endregion*/

    /**region Non-Constant Methods*/

    /**
     * @brief inserts item to heap
     * */
    void insert(const Comparable& item);
    /**
     * @brief inserts item to heap
     * */
    void insert(Comparable&& item);

    /**
     * @brief Get the maximum element in heap and remove it
     * @return Comparable copy of maximum element in heap (before removed).
     * **/
    Comparable extractMax();

    /**
     * @brief Remove the maximum element in heap without returning it
     * **/
    void removeMax();

    /*endregion*/

private:
    std::vector<Comparable> heap;

    /**region Private Constant (and Static) Methods */
    static int getParentIndex(int itemIndex);
    static int getRightChildIndex(int parentIndex);
    static int getLeftChildIndex(int parentIndex);

    Comparable parentValue(int itemIndex) const;
    /**
     * @brief Checks whether a node at the given index needs to be moved down in the heap.
     *
     * This function determines whether the node at the specified index should be moved down
     * in the binary max-heap to maintain the max-heap property.
     *
     * @tparam Comparable The type of elements stored in the heap. It should be a comparable type.
     * @param itemIndex The index of the node to be checked.
     * @return `true` if the node needs to be moved down, `false` otherwise.
     */
    [[nodiscard]] bool needsBubbleDown(int itemIndex) const;
    /**
     * @brief Checks whether a node at the given index needs to be moved up in the heap.
     *
     * This function determines whether the node at the specified index should be moved up
     * in the binary max-heap to maintain the max-heap property.
     *
     * @param itemIndex The index of the item to be checked.
     * @return `true` if the item needs to be moved up, `false` otherwise.
     */
    [[nodiscard]] bool needsBubbleUp(int itemIndex) const;

    /*endregion*/

    /**region Private Non-Constant methods **/

    /**
     * @brief Performs the "bubble up" operation in the binary max-heap.
     *
     * This function moves an element up in the heap to maintain the max-heap property.
     * It compares the element at the given index with its parent and swaps them if necessary,
     * repeatedly moving up the heap until the heap property is satisfied.
     *
     * @tparam Comparable The type of elements stored in the heap. It should be a comparable type.
     * @param itemIndex The index of the element to be bubbled up.
     */
    void bubbleUp(int index);

    /**
     * @brief Performs the "bubble down" operation in the binary max-heap.
     *
     * This function moves an element down in the heap to maintain the max-heap property.
     * It compares the element at the given index with its children and swaps it with the smaller child,
     * repeatedly moving down the heap until the heap property is satisfied.
     *
     * @tparam Comparable The type of elements stored in the heap. It should be a comparable type.
     * @param index The index of the element to be bubbled down.
     */
    void bubbleDown(int index);
    /*endregion*/

};

/**region Public Constant Methods */

template<typename Comparable>
Comparable BinaryMaxHeap<Comparable>::getMax() const {
    if(size() == 0) throw std::runtime_error("Heap is empty");

    return heap[0];
}

template<typename Comparable>
int BinaryMaxHeap<Comparable>::size() const{
    return heap.size();
}

template<typename Comparable>
bool BinaryMaxHeap<Comparable>::isEmpty() const {
    return size() == 0;
}

/*endregion*/

/**region Public Non-Const Methods */
template<typename Comparable>
void BinaryMaxHeap<Comparable>::insert(const Comparable &item) {
    heap.push_back(item);

    // If needed, bubble up the recently added item until it doesn't
    // violate the heap property
    int itemIndex = heap.size() - 1;
    bubbleUp(itemIndex);
}

template<typename Comparable>
void BinaryMaxHeap<Comparable>::insert(Comparable&& item) {
    insert(item);
}

template<typename Comparable>
void BinaryMaxHeap<Comparable>::removeMax() {
    int lastItem = heap[size() - 1];
    heap.pop_back();
    if(!heap.empty()){
        heap[0] = lastItem;

        bubbleDown(0);
    }
}

template<typename Comparable>
Comparable BinaryMaxHeap<Comparable>::extractMax() {
    if(heap.empty()) throw std::out_of_range("Heap is empty.");

    Comparable max = heap[0];
    removeMax();
    return max;
}

/*endregion*/

/**region Private Constant (and Static) Methods */
template<typename Comparable>
int BinaryMaxHeap<Comparable>::getRightChildIndex(int parentIndex){
    return parentIndex * 2 + 2;
}

template<typename Comparable>
int BinaryMaxHeap<Comparable>::getLeftChildIndex(int parentIndex){
    return parentIndex * 2 + 1;
}
template<typename Comparable>
int BinaryMaxHeap<Comparable>::getParentIndex(int itemIndex){
    return (itemIndex - 1) / 2;
}

template<typename Comparable>
Comparable BinaryMaxHeap<Comparable>::parentValue(int itemIndex) const{
    return heap[getParentIndex(itemIndex)];
}

template<typename Comparable>
bool BinaryMaxHeap<Comparable>::needsBubbleDown(int itemIndex) const{
    int rightChildIndex = getRightChildIndex(itemIndex);
    // if right child exists and is larger, bubble down is needed
    if( rightChildIndex < size() &&
        heap[rightChildIndex] > heap[itemIndex] ){
        return true;
    };

    // if left child exists and is larger, bubble down is needed
    int leftChildIndex = getLeftChildIndex(itemIndex);
    if( leftChildIndex < size() &&
        heap[leftChildIndex] > heap[itemIndex] ){
        return true;
    };

    // else no bubble down needed
    return false;
}

template<typename Comparable>
bool BinaryMaxHeap<Comparable>::needsBubbleUp(int itemIndex) const {
    return itemIndex > 0 && heap[itemIndex] > parentValue(itemIndex);
}

/*endregion*/

/**region Private Non-Constant methods **/

template<typename Comparable>
void BinaryMaxHeap<Comparable>::bubbleUp(int itemIndex) {
    while(needsBubbleUp(itemIndex)){
        int parentIndex = getParentIndex(itemIndex);
        if(parentIndex >= 0)
            std::swap(heap[parentIndex],heap[itemIndex]);

        itemIndex = parentIndex;
    }
}


template<typename Comparable>
void BinaryMaxHeap<Comparable>::bubbleDown(int index) {

    while(needsBubbleDown(index)) {

        // get indexes of node's left and right children
        int rightChildIndex = getRightChildIndex(index);
        int leftChildIndex = getLeftChildIndex(index);

        int indexToSwapWith;

        // if node has two children,
        // swap it with the larger
        if (rightChildIndex < size() && leftChildIndex < size()) {
            if (heap[rightChildIndex] >= heap[leftChildIndex])
                indexToSwapWith = rightChildIndex;
            else
                indexToSwapWith = leftChildIndex;
        }
            // if only has a rightChild
        else if (rightChildIndex < size())
            indexToSwapWith = rightChildIndex;
            // if only has left Child
        else if (leftChildIndex < size())
            indexToSwapWith = leftChildIndex;
            // node has no children
        else return;

        std::swap(heap[indexToSwapWith], heap[index]);
        index = indexToSwapWith;
    }
}

/*endregion*/


#endif //DSA_BINARYMAXHEAP_H
