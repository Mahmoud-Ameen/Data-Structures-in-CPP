#include <stack>
#include <utility>

#include "Trie.h"


/* region Internal Trie NODE struct */

Trie::Node::~Node(){
    for (auto pair: children) {
        delete pair.second;
    }
}

void Trie::Node::insertChild(char ch){
    children.insert({ch,new Node(ch)});
};

void Trie::Node::insertChild(Node* child) {
    if(!child) return;

    if(children[child->value]) delete children[child->value];

    children[child->value] = child;
}

Trie::Node* Trie::Node::getChild(char ch){
    if(children.find(ch) == children.end())
        return nullptr;

    return children[ch];
}

bool Trie::Node::hasChild(const char &ch) {
    return getChild(ch) != nullptr;
}

std::vector<Trie::Node *> Trie::Node::getChildren() const {
    std::vector<Node *> childrenVector;
    childrenVector.reserve(children.size() + 1);
    for (auto pair:children) {
        if(!pair.second) continue;

        childrenVector.push_back(pair.second);
    }
    return childrenVector;
}

void Trie::Node::removeChild(char ch) {
    auto child = children[ch];
    if(!child->hasChildren()) {
        delete child;
        children[ch] = nullptr;
    }
}

bool Trie::Node::hasChildren() const {
    return !getChildren().empty();
};
/*endregion */

/*region PUBLIC */

/* region Big Five */

Trie::Trie() {
    root = new Node(' ');
}

Trie::Trie(const Trie& other) {
    root = copyNodes(other.root);
}

Trie::~Trie(){
    delete root;
}

Trie& Trie::operator=(const Trie& other) {
    if (this != &other) {
        // Clear the existing trie
        delete root;

        // Perform a deep copy of the other trie
        root = copyNodes(other.root);
    }
    return *this;
}

Trie::Trie(Trie&& other) noexcept : root(std::exchange(other.root, nullptr)) {
}

Trie& Trie::operator=(Trie&& other) noexcept {
    if (this != &other) {
        // Clear the existing trie
        delete root;

        // Move the root pointer from the other object
        root = std::exchange(other.root, nullptr);
    }
    return *this;
}

/*endregion*/

/* region PUBLIC Constant Methods */

std::vector<std::string> Trie::getWords(const std::string &prefix) const {
    std::vector<std::string> words;

    auto current = getLastNode(prefix);

    if(current){
        std::string s = prefix;
        getWords(current, s, words);
    }

    return words;
}

bool Trie::contains(const std::string& word) const {

    auto current = root;

    for (char ch:word) {
        if(!current->hasChild(ch))
            return false;

        current = current->getChild(ch);
    }

    return current->isWordEnd;
}

/*endregion*/

/* region Public Non-Constant Methods */

void Trie::insert(const std::string& word) {
    auto current = root;

    for (char ch:word) {
        if(!current->hasChild(ch))
            current->insertChild(ch);

        current = current->getChild(ch);
    }

    // Mark last char as a word ending
    current->isWordEnd = true;
}

void Trie::remove(const std::string &word) {
    if(!contains(word)) return;

    remove(root,word,0);
}

/*endregion*/

/*endregion PUBLIC*/

/* region PRIVATE */

void Trie::getWords(Node* node , std::string& word, std::vector<std::string>& words) const {
    if(!node) return;

    // If last added character is a word ending,
    // add word to vector
    if(node->isWordEnd)
        words.push_back(word);

    // Use a backtracking approach to find all words starting with this prefix
    for (Node* child: node->getChildren()) {
        word += child->value;
        getWords(child, word, words);
        word.pop_back();
    }
}

Trie::Node *Trie::getLastNode(const std::string &word) const {
    auto current = root;

    for (const char& ch: word) {
        if(!current) return nullptr;
        current = current->getChild(ch);
    }

    return current;
}

Trie::Node* Trie::copyNodes(Node* source)  const{
    if (!source) return nullptr;

    auto node = new Node(source->value);
    node->isWordEnd = source->isWordEnd;

    for (const auto& child : source->getChildren()) {
        node->insertChild(copyNodes(child));
    }
    return node;
}

void Trie::remove(Node *node, const std::string &word, int nextIndex) {
    if(!node) return;

    // Mark last node of word as not a word ending,
    // and end the recursive chain
    if(nextIndex == word.size()){
        node->isWordEnd = false;
        return;
    }

    char nextCh = word[nextIndex];
    auto child = node->getChild(nextCh);

    // Recursively delete all word's nodes in post-order
    remove(child,word,nextIndex + 1);

    // Physically delete the child node if it is not a part of another word
    if(!child->hasChildren() && !child->isWordEnd){
        node->removeChild(nextCh);
    }
}

/* endregion */
