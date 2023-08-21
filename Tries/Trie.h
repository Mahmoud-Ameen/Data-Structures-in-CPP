/**
 * @file Trie.h
 * @brief Declaration of the Trie class for efficient string storage and retrieval.
 *
 * This header file defines the Trie class, a data structure used for efficient storage and retrieval
 * of strings with common prefixes. The Trie class provides methods for insertion, searching, deletion,
 * and other operations on the stored strings. It is suitable for tasks like autocomplete, spell checking,
 * and substring matching.
 *
 * The Trie class is designed to efficiently manage a dynamic set of strings by using a tree-like structure,
 * where each node represents a character of a string. This allows for fast prefix matching and other string-based
 * operations. The class also includes methods for copying, moving, and managing the trie's contents.
 *
 * @author Mahmoud Ashraf
 * @date 20/8/2023
 */
#ifndef DSA_TRIE_H
#define DSA_TRIE_H

#include <unordered_map>
#include <string>
#include <vector>


class Trie {

struct Node;
public:
    /* region Big Five */

    Trie();

    Trie(const Trie& other); // copy constructor
    Trie(Trie&& other) noexcept; // Move constructor

    ~Trie(); // Destructor

    Trie& operator=(const Trie& other); // Copy Assignment Operator
    Trie& operator=(Trie&& other) noexcept ; // Move Assignment Operator

    /*endregion*/

    /* region Public Constant Methods */

    /**
     * @brief Retrieves a vector of words that have the given prefix.
     *
     * Returns a vector of words stored in the trie that have the specified prefix.
     *
     * @param prefix The prefix for which to retrieve words.
     * @return A vector of words with the given prefix.
     */
    [[nodiscard]] std::vector<std::string> getWords(const std::string& prefix) const;

    /**
     * @brief Checks if a word exists in the trie.
     *
     * Returns true if the word exist, false otherwise.
     *
     * @param word word to check if exists
     * @return true if the word exist, false otherwise.
     * */
    [[nodiscard]] bool contains(const std::string& word) const;

    /*endregion*/

    /* region Public Non-Constant Methods */

    /**
     * @brief Inserts a word to the trie.
     *
     * @param word The word to be inserts.
     */
    void insert(const std::string& word);

    /**
     * @brief Removes a word from the trie if it exists.
     *
     * Removes the specified word from the trie if it exists.
     *
     * @param word The word to be removed.
     */
    void remove(const std::string& word);

    /*endregion*/

private:
    Node* root;

    /* region Private Constant Methods */

    /**
     * @brief Recursively retrieves words from the trie rooted at the given node.
     *
     * Recursively traverses the trie rooted at the given node to retrieve words and adds them to the vector.
     *
     * @param node The current node being traversed.
     * @param word The current word formed during traversal.
     * @param words The vector to store retrieved words.
     */
    void getWords(Node* node, std::string& word, std::vector<std::string>& words) const;

    /**
     * @brief Retrieves the last node of a given word in the trie.
     *
     * Traverses the trie from the root to the last node representing the characters of the given word.
     *
     * @param word The word for which to retrieve the last node.
     * @return A pointer to the last node representing the characters of the word, or nullptr if the word is not in the trie.
     */
    [[nodiscard]] Node* getLastNode(const std::string& word) const;

    Node* copyNodes(Node* source) const;

    /*endregion*/

    /* region Private Non-Constant Methods */

    /**
     * @brief Recursively removes a word from the trie rooted at the given node.
     *
     * Recursively traverses the trie rooted at the given node to remove the specified word.
     *
     * @param node The current node being traversed.
     * @param word The word to be removed.
     * @param nextIndex The index of the next character to be processed in the word.
     */
    void remove(Node *node, const std::string &word, int nextIndex);

    /*endregion*/

};

struct Trie::Node{
    char value;
    bool isWordEnd = false;

    explicit Node(char value) : value(value){};
    ~Node();

    /*region PUBLIC non-Constant Methods*/

    /**
     * @brief Inserts a new child node with the specified character.
     *
     * Inserts a new child node with the given character into the current node's children.
     *
     * @param ch The character for the new child node.
     */
    void insertChild(char ch);

    /**
     * @brief Inserts a node pointer as a child.
     *
     * Inserts a node into the current node's children.
     * If already exists a child with same value, it is overwritten.
     *
     * @param child The pointer to Node to be inserted.
     */
    void insertChild(Node* child);

    /**
     * @brief Checks if the node has a child with the given character.
     *
     * Checks whether the current node has a child node associated with the specified character.
     *
     * @param ch The character to check for.
     * @return True if a child with the specified character exists, otherwise false.
     */
    bool hasChild(const char& ch);

    /**
     * @brief Gets the child node associated with the specified character.
     *
     * Searches for the child node associated with the specified character in the current node's children.
     *
     * @param ch The character to search for.
     * @return A pointer to the child node if found, or nullptr if not found.
     */
    Node* getChild(char ch);

    /**
     * @brief Removes the child node associated with the specified character.
     *
     * Removes the child node associated with the given character from the current node's children.
     * If the removed child node has no more children, it is deleted.
     *
     * @param ch The character of the child node to be removed.
     */
    void removeChild(char ch);
    /*endregion*/
    /* region PUBLIC CONST Methods*/

    /**
     * @brief Checks if the node has any children.
     *
     * Checks whether the current node has any valid child nodes.
     *
     * @return True if the node has children, otherwise false.
     */
    bool hasChildren() const;

    /**
     * @brief Retrieves a vector of child nodes.
     *
     * Retrieves a vector containing pointers to all valid child nodes of the current node.
     *
     * @return A vector of child node pointers.
     */
    std::vector<Node*> getChildren() const;
    /*endregion*/

private:
    std::unordered_map<char,Node*> children;

};

#endif //DSA_TRIE_H
