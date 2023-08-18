

#ifndef DSA_LEFTISTMINHEAP_H
#define DSA_LEFTISTMINHEAP_H

#include <algorithm>
#include <iostream>

template<typename Comparable>
class LeftistMinHeap {

public:
    /*region Big Five*/

    // Default Constructor
    LeftistMinHeap() = default;

    // Copy Constructor
    LeftistMinHeap(const LeftistMinHeap& other);

    // Copy Assignment Operator
    LeftistMinHeap& operator=(const LeftistMinHeap& other);

    ~LeftistMinHeap();


    /*endregion*/

    /*region Constant Public Methods **/

    /**
     * @return minimum element in heap
     * **/
    Comparable getMin() const;

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

    /*region Non-Constant Methods*/

    /**
     * @brief inserts item to heap
     * */
    void insert(const Comparable& item);
    /**
     * @brief inserts item to heap
     * */
    void insert(Comparable&& item);

    /**
     * @brief merges two heaps together
     * @param rhs heap to be merged with this one
     * */
    void merge(LeftistMinHeap& rhs);

    /**
     * @brief Get the minimum element in heap and remove it
     * @return Comparable copy of minimum element in heap (before removed).
     * **/
    Comparable extractMin();

    /**
     * @brief Remove the minimum element in heap without returning it
     * **/
    void removeMin();

    /*endregion*/


private:
    struct Node;

    Node* root = nullptr;
    int m_size = 0;

    /*region Private Non-Const Methods */
    Node* merge(Node* first,Node* second);

    /**
     * @brief recursively free used memory by tree nodes
     * */
    void clear(Node* node);

    /**
     *  @brief Recursive function to perform deep copy
     *  @param node Node to copy
     */
    Node* deepCopy(Node* node) {
        if (!node) {
            return nullptr;
        }
        Node* new_node = new Node(node->value);
        new_node->rank = node->rank;
        new_node->left = deepCopy(node->left);
        new_node->right = deepCopy(node->right);
        return new_node;
    }

    /*endregion*/

};

/*region Leftist Heap Node */
template<typename Comparable>
struct LeftistMinHeap<Comparable>::Node{
    Comparable value;
    int rank;

    Node* left;
    Node* right;

    explicit Node(const Comparable& val) : value(val), rank(0), left(nullptr), right(nullptr) {};

};
/*endregion*/

/*region Big Five **/

template<typename Comparable>
LeftistMinHeap<Comparable>::~LeftistMinHeap() {
    clear(root);
    root = nullptr;
}

template<typename Comparable>
LeftistMinHeap<Comparable>::LeftistMinHeap(const LeftistMinHeap<Comparable> &other) {
    root = deepCopy(other.root);
    m_size = other.m_size;
}

template<typename Comparable>
LeftistMinHeap<Comparable>& LeftistMinHeap<Comparable>::operator=(const LeftistMinHeap& other){
    if (this != &other) {
        clear(root);
        root = deepCopy(other.root);
        m_size = other.m_size;
    }
    return *this;
};


/*endregion*/

/*region Public Const Methods*/

template<typename Comparable>
bool LeftistMinHeap<Comparable>::isEmpty() const{
    return root == nullptr;
}

template<typename Comparable>
Comparable LeftistMinHeap<Comparable>::getMin() const {
    return root->value;
}

template<typename Comparable>
int LeftistMinHeap<Comparable>::size() const {
    return m_size;
}
/*endregion*/

/*region Public Non-Const Methods */

template<typename Comparable>
void LeftistMinHeap<Comparable>::insert(const Comparable &item) {
    root = merge(root, new Node{item} );
    m_size++;
}

template<typename Comparable>
void LeftistMinHeap<Comparable>::insert(Comparable &&item) {
    insert(item);
}

template<typename Comparable>
void LeftistMinHeap<Comparable>::merge(LeftistMinHeap &rhs) {
    if(&rhs == this) return;

    root = merge(root,rhs.root);
    rhs.root = nullptr;
}

template<typename Comparable>
void LeftistMinHeap<Comparable>::removeMin() {
    if(isEmpty()) throw std::runtime_error("Heap is empty. Cannot delete minimum element.");

    Node* initialRoot = root;
    root = merge(root->left,root->right);
    delete initialRoot;

    m_size--;
}

template<typename Comparable>
Comparable LeftistMinHeap<Comparable>::extractMin() {
    if(isEmpty()) throw std::runtime_error("Heap is empty. Cannot delete minimum element.");

    auto minVal = root->value;
    removeMin();

    return minVal;
}

/*endregion*/

/*region Private Non-Const Methods */

template<typename Comparable>
typename LeftistMinHeap<Comparable>::Node *LeftistMinHeap<Comparable>::merge(LeftistMinHeap::Node *first, LeftistMinHeap::Node *second) {
    if (first == nullptr) return second;
    if (second == nullptr) return first;

    // make first the heap with smaller root
    if (first->value > second->value)
        std::swap(first, second);

    first->right = merge(first->right, second);

    // maintain leftist property
    if (first->left == nullptr || first->left->rank < first->right->rank)
        std::swap(first->left, first->right);

    first->rank = (first->right == nullptr) ? 0 : first->right->rank + 1;
    return first;
}


template<typename Comparable>
void LeftistMinHeap<Comparable>::clear(LeftistMinHeap::Node *node) {

    if (node) {
        clear(node->left);
        clear(node->right);
        delete node;
    }

}


/*endregion*/



#endif //DSA_LEFTISTMINHEAP_H
