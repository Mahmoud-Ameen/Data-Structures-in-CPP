/**
 * @brief Definition of the HashTable class.
 *
 * This file contains the declaration of the HashTable class, which implements a basic
 * hash table data structure. A hash table is used to store key-value pairs, allowing
 * efficient retrieval, insertion, and deletion of elements based on their unique keys.
 *
 * The implementation uses a vector of linked lists to handle collisions. When multiple
 * elements are hashed to the same index, they are stored in a linked List at that index.
 * The implementation uses a rehashing technique to keep most operations as close
 * as possible to time complexity of O(1).
 *
 * This HashTable class supports key-value pairs with generic types.
 * The hashing function used for the keys is the default std::hash function.
 *
 * @note This implementation does not support duplicate keys. If the same key is inserted
 * multiple times, only the last inserted value will be stored in the hash table
 *
 * @author Mahmoud Ashraf
 * @date 27/07/2023
 */

#ifndef DSA_HASHTABLE_H
#define DSA_HASHTABLE_H

#include <vector>

template<typename Key,typename Value>
class HashTable {
public:

    /**region Big Five & Other Constructors*/

    // Default Constructor
    HashTable();

    // Destructor
    ~HashTable();

    // Copy Constructor
    HashTable(const HashTable& other);

    // Copy Assignment Operator
    HashTable& operator=(const HashTable& other);

    // Move Constructor
    HashTable(HashTable&& other) noexcept ;

    // Move Assignment Operator
    HashTable& operator=(HashTable&& other) noexcept ;

    explicit HashTable(int size);

    /*endregion*/

    /*region Constant Methods */
    /**
     * @brief Checks if a key exists in the hash table->
     *
     * @param key The key to check for existence.
     * @return True if the key exists in the hash table, false otherwise.
     */

    bool contains(const Key& key) const;
    bool contains(Key&& key) const;


    /**
     * @return elements count
     * */
    [[nodiscard]] int size() const;

    /**
     * @brief Retrieves the value associated with the given key.
     *
     * If the key is not found in the hash table, it throws a runtime error.
     *
     * @param key The key to search for.
     * @return copy of the value associated with the key.
     */
    Value get(Key key) const;

    // endregion

    /** region Non-Constant Methods */

    /**
     * @brief Inserts a key-value pair into the hash table->
     *
     * If the key already exists in the hash table, the value will be updated to the new one.
     *
     * @param key The key of the element to be inserted.
     * @param value The value associated with the key.
     */
    void insert(Key key,Value value);

    /**
     * @brief Retrieves a reference to value associated with the given key.
     *
     * If the key is not found in the hash table,
     * the function throws a runtime error,
     *
     * @param key The key to search for.
     * @return Reference to the value associated with the key.
     */
    Value& operator[](const Key& key);

    /**
     * @brief Removes the key-value pair with the specified key from the hash table->
     *
     * If the key is not found in the hash table, the function does nothing.
     *
     * @param key The key of the element to be removed.
     */
    void remove(const Key& key);
    void remove(Key && key);

     // endregion

private:
    /* forward declaration of data structures used as bucket */
    struct List;
    struct Node;

    /* Private members */
    int capacity = 257;                                 // Default tableSize of the hash table
    int tableSize = 0;                                  // Current tableSize of the hash table
    std::vector<List>* table = new std::vector<List>;   // Vector of linked lists (buckets) for hashing
    const int LOAD_FACTOR = 1;

    /*** Private Constant Methods */

    /**
     * @brief Calculates the next prime number after the given number.
     *
     * @param n The number to start from.
     * @return The next prime number after n.
     */
    static int nextPrime(int n);
    /**
     * @brief Checks if a number is prime.
     *
     * @param n The number to check.
     * @return True if the number is prime, false otherwise.
     */
    static int isPrime(int n);

    /**
     * @brief Computes the hash value for a given key.
     *
     * @param key The key to hash.
     * @return The hash value.
     */
     [[nodiscard]] std::size_t hashFunction(const Key& key) const;

    /**
     * @brief Finds a node with the given key in the hash table.
     *
     * @param key The key to search for.
     * @return Pointer to the node if found, nullptr if not found.
     */
    Node * findNode(const Key &key) const;

    /**
     * @brief Creates a deep copy of the table vector.
     *
     * @return Pointer to a new table vector with a deep copy of the linked lists.
     */
    std::vector<HashTable<Key, Value>::List> * cloneTable() const;

    /**
    * @brief Checks if a resize is needed based on the load factor.
    *
    * @return True if resizing is needed, false otherwise.
    */
    [[nodiscard]] bool needResize() const;

    /*** Private Non-Constant Methods */

    /**
     * @brief Performs rehashing to resize the hash table.
     */
    void rehash();

};

/**region HashTable Bucket (custom linked List) */

/**
 * @brief Definition of the Node struct used within the HashTable List.
 *
 * This struct represents a node in a linked list within the HashTable's bucket.
 * Each node contains a key-value pair and a pointer to the next node.
 *
 * @tparam Key The type of the key.
 * @tparam Value The type of the value.
 */
template <typename Key,typename Value>
struct HashTable<Key,Value>::Node {
    Key key;
    Value value;
    Node* next = nullptr;

    /**
     * @brief Constructor to initialize a new node.
     *
     * @param key The key of the node.
     * @param val The value associated with the key.
     */
    Node(const Key& key, Value val) : key(key), value(val), next(nullptr) {}

    Node(const Node& other){
        key = other.key;
        value = other.value;
        if(other.next != nullptr)
            next = new Node(*other.next);
        else next = nullptr;
    }
};

/**
 * @brief Definition of the List struct used as a bucket in the HashTable.
 *
 * This struct represents a linked list that serves as a bucket in the HashTable.
 * It contains methods for inserting, finding, and removing nodes from the list.
 *
 * @tparam Key The type of the key.
 * @tparam Value The type of the value.
 */
template <typename Key,typename Value>
struct HashTable<Key,Value>:: List{
    Node* head = nullptr;

    /**
     * @brief Default constructor for the List struct.
     */
    List() = default;

    /**
     * @brief Copy constructor for the List struct.
     *
     * Initializes a new list by copying nodes from another list.
     *
     * @param other The list to be copied.
     */
    List(const List& other){

        if( other.head){
            // Call copy constructor of Node class which
            // performs a deep copy of the other's head node
            Node* node = new Node(*other.head);
            head = node;
        }
        else head = nullptr;

    }

    /**
     * @brief Destructor for the List struct.
     *
     * Clears the linked list by deleting all nodes.
     */
    ~List(){
        clear();
    }

    /**
     * @brief Finds a node with the given key in the linked List.
     *
     * This method searches the linked List for a node with the specified key and returns
     * a pointer to the node if found, or nullptr if the key is not present in the List.
     *
     * @param key The key to search for in the linked List.
     * @return A pointer to the node with the given key, or nullptr if the key is not found.
     */
    Node * findNode(const Key& key){
        Node* node = head;
        while(node && node->key != key){
            node = node->next;
        }
        return node;
    };

    /**
     * @brief Finds the previous node before a given key in the linked List.
     *
     * This method searches the linked List for the node that comes immediately before
     * the specified key and returns a pointer to that node. If the key is not present
     * in the linked List, the function returns nullptr.
     *
     * @param key The key to search for in the linked List.
     * @return A pointer to the node that comes before the given key,
     *         or nullptr if the key is not found.
     */
    Node* findPrev(const Key& key){
        Node* prev = nullptr;   /**< Pointer to the previous node before the key. */
        Node* current = head;   /**< Pointer to the current node being inspected. */

        while (current && current->key != key) {
            prev = current;
            current = current->next;
        }

        // Key not found
        if (!current) {
            return nullptr;
        }

        return prev;
    }

    /**
     * @brief Inserts a new node with the given key and value into the linked List.
     *
     * If a node with the same key already exists in the linked List, the existing node's value
     * will be updated with the new value.
     *
     * @param key The key of the new node to be inserted.
     * @param value The value associated with the new node.
     */
    void insert(Key key, Value value){

        // linked List is empty
        if(!head){
            head = new Node(key,value);
            return;
        }

        // key already exists in the linked lists
        // update its value
        Node* node = findNode(key);
        if(node){
            node->value = value;
            return;
        }

        // key not found
        // insert the node to the linked List start
        node = new Node(key,value);
        node->next = head;
        head = node;

    }


    /**
     * @brief Removes a node with the given key from the linked List.
     *
     * If the key is not found, the function does nothing.
     *
     * @param key The key of the node to be removed.
     *
     * @return true if key found and removed, fasle otherwise.
     */
    bool remove(const Key& key){

        // List is empty. Node doesn't exist
        if(!head) return false;

        // Node to be deleted is the list head
        if( head->key == key){
            auto newHead = head->next;
            delete head;
            head = newHead;
            return true;
        }

        Node* prev = findPrev(key);

        // If key exists, remove it
        if(prev && prev->next)
        {
            auto node = prev->next;
            prev->next = node->next;

            delete node;
            return true;
        }
        // If key doesn't exist, do nothing
        return false;
    }

    /**
     * @brief Clears the linked List by deleting all nodes.
     */
    void clear(){
        auto& node = head;
        while (node) {
            Node* next = node->next;
            delete node;
            node = nullptr;
            node = next;
        }
        head = nullptr;
    }

};

/*endregion */

/***region Big five & other constructors */

template<typename Key, typename Value>
HashTable<Key, Value>::HashTable() {
    for (int i = 0; i < capacity; ++i) {
        List list;
        table->push_back(list);
    }
}

template<typename Key, typename Value>
HashTable<Key, Value>::~HashTable() {
// Release resources owned by 'this'
    delete table;
}

template<typename Key, typename Value>
HashTable<Key, Value>::HashTable(const HashTable &other) {
    tableSize = other.tableSize;
    capacity = other.capacity;
    table = other.cloneTable();
}

template<typename Key, typename Value>
HashTable<Key, Value>::HashTable(HashTable &&other) noexcept : tableSize(other.tableSize), table(std::move(other.table))  {
    other.tableSize = 0;
}

// copy assignment operator
template<typename Key, typename Value>
HashTable<Key,Value> &HashTable<Key, Value>::operator=(const HashTable &other) {
    if(this!= &other) {
        tableSize = other.tableSize;
        table = other.cloneTable();
        return *this;
    }
}

template<typename Key, typename Value>
HashTable<Key,Value> &HashTable<Key, Value>::operator=(HashTable &&other) noexcept {
    if (this != &other) {
        // Release resources owned by 'this'
        for (Node* node : table) {
            while (node) {
                Node* next = node->next;
                delete node;
                node = next;
            }
        }
        table->clear();

        // Transfer ownership of the linked List nodes from 'other' to 'this'
        tableSize = other.tableSize;
        table = std::move(other.table);

    }
    return *this;
}


template<typename Key, typename Value>
HashTable<Key, Value>::HashTable(int size) :capacity(size){
    for (int i = 0; i < capacity; ++i) {
        auto list = new List();
        table->push_back(list);
    }
}
/*endregion*/

/**region Public Non-Constant Methods */

template<typename Key, typename Value>
Value &HashTable<Key, Value>::operator[](const Key &key) {
    auto node = findNode(key);

    if (node)
        return node->value;
    else {
        throw std::runtime_error("key doesn't exist");
    }
}

template<typename Key, typename Value>
void HashTable<Key, Value>::insert( Key key, Value value) {

    // locate the bucket to insert in
    size_t bucketIndex = hashFunction(key) % capacity;
    auto& list = (*table)[bucketIndex];

    list.insert(key,value);
    tableSize++;

    // if
    if(needResize()) {
        rehash();
    }
}

template<typename Key, typename Value>
void HashTable<Key, Value>::remove(const Key &key) {
    auto bucketIndex = hashFunction(key) % capacity;

    bool removed = (*table)[bucketIndex].remove(key);

    if(removed) tableSize--;
}

template<typename Key, typename Value>
void HashTable<Key, Value>::remove(Key && key) {
    remove(key);
}

/* endregion */

/** region Private Constant Methods */

template<typename Key, typename Value>
std::vector<typename HashTable<Key, Value>::List> * HashTable<Key, Value>::cloneTable() const {
    // Create a new vector to hold the cloned lists
    auto tableClone = new std::vector<List>();

    // Iterate over the original table vector
    for (auto& list : *table) {
        // Use the List copy constructor to create a deep copy of the current list
        List listClone(list);
        tableClone->push_back(listClone);
    }

    // Return the cloned vector of lists
    return tableClone;
}

template<typename Key, typename Value>
bool HashTable<Key, Value>::contains(const Key &key) const {
    return findNode(key) != nullptr;
}

template<typename Key, typename Value>
bool HashTable<Key, Value>::contains(Key &&key) const {
    return findNode(std::move(key)) != nullptr;
}

template<typename Key, typename Value>
std::size_t HashTable<Key, Value>::hashFunction(const Key& key) const {
    // Use std::hash to generate the hash code of the key
    std::hash<Key> hashFunc;
    size_t hashCode = hashFunc(key);

    return hashCode;
}

template<typename Key, typename Value>
typename HashTable<Key, Value>::Node * HashTable<Key, Value>::findNode(const Key &key) const {
    int index = hashFunction(key) % capacity;

    return (*table)[index].findNode(key);
}

template<typename Key, typename Value>
int HashTable<Key, Value>::size() const {
    return tableSize;
}

template<typename Key, typename Value>
Value HashTable<Key, Value>::get(Key key) const {
    auto node = findNode(key);

    if (node)
        return node->value;
    else {
        throw std::runtime_error("key doesn't exist");
    }
}

/* endregion */

/*region Private Non-Constant methods */

template<typename Key, typename Value>
void HashTable<Key, Value>::rehash() {
    /*
     * new table tableSize = next prime greater than double initial tableSize
     * create a new HashTable with the new table tableSize
     * for each node in the initial table, insert the key value pair to the new table
     * use copy assignment operator to update the hashtable
     * */

    int newCapacity = nextPrime(capacity *2);
    capacity = newCapacity;


    auto newTable = new std::vector<List> (newCapacity);
    for (int i = 0; i < newCapacity; ++i) {
        (*newTable)[i] = List();
    }

    for (List& list: *table) {
        Node* node = list.head;

        while(node){
            auto newIndex = hashFunction(node->key) % newCapacity;
            List& bucket = (*newTable)[newIndex];

            (*newTable)[newIndex].insert(node->key,node->value);

            auto next = node->next;
            delete node;
            node = next;
        }
    }

    table = newTable;
}

/*endregion*/

/*** region Static Private Methods */

template<typename Key,typename Value>
bool HashTable<Key,Value>::needResize() const {
    return float(tableSize) / capacity >= 1;
}

template<typename Key, typename Value>
int HashTable<Key,Value>::isPrime(int n){
    if (n <= 1) {
        return false;
    }
    if (n <= 3) {
        return true;
    }
    if (n % 2 == 0 || n % 3 == 0) {
        return false;
    }

    int i = 5;
    while (i * i <= n) {
        if (n % i == 0 || n % (i + 2) == 0) {
            return false;
        }
        i += 6;
    }

    return true;
};

template<typename Key, typename Value>
int HashTable<Key,Value>::nextPrime(int n){
    if (n <= 1) {
        return 2;
    }

    if (n % 2 == 0) {
        n++;
    }
    else n += 2;

    while (true) {
        if (isPrime(n)) {
            return n;
        }
        n += 2;
    }
}

/*endregion*/

#endif //DSA_HASHTABLE_H
