#include <iostream>
#include <unordered_map>

// Trie Node
struct TrieNode {
    std::unordered_map<char, TrieNode*> children;
    bool isEndOfWord;

    TrieNode() : isEndOfWord(false) {}
};

// Trie Class
class Trie {
public:
    Trie() {
        root = new TrieNode();
    }

    // Insert a word into the trie
    void insert(const std::string& word) {
        TrieNode* current = root;

        for (char ch : word) {
            if (current->children.find(ch) == current->children.end()) {
                current->children[ch] = new TrieNode();
            }
            current = current->children[ch];
        }

        current->isEndOfWord = true;
    }

    // Search for a word in the trie
    bool search(const std::string& word) {
        TrieNode* node = searchNode(word);
        return (node != nullptr && node->isEndOfWord);
    }

    // Check if any word in the trie starts with the given prefix
    bool startsWith(const std::string& prefix) {
        return (searchNode(prefix) != nullptr);
    }

private:
    TrieNode* root;

    // Helper function to search for a node in the trie
    TrieNode* searchNode(const std::string& word) {
        TrieNode* current = root;

        for (char ch : word) {
            if (current->children.find(ch) == current->children.end()) {
                return nullptr; // Prefix not found
            }
            current = current->children[ch];
        }

        return current;
    }
};

int test_trie() {
    Trie trie;

    // Insert words into the trie
    trie.insert("apple");
    trie.insert("app");
    trie.insert("banana");

    // Search for words in the trie
    std::cout << std::boolalpha; // Output 'true' or 'false' instead of '1' or '0'
    std::cout << "Search for 'apple': " << trie.search("apple") << std::endl;
    std::cout << "Search for 'app': " << trie.search("app") << std::endl;
    std::cout << "Search for 'banan': " << trie.search("banan") << std::endl;
    std::cout << "Search for 'orange': " << trie.search("orange") << std::endl;
    std::cout << "Search for 'ban' presence: " << trie.startsWith("ban") << std::endl;
    return 0;
}