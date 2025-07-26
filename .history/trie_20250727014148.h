#ifndef TRIE_H
#define TRIE_H

#include <stdbool.h>

// Defining trie node structure 
#define ALPHABET_SIZE 26

typedef struct TrieNode
{
    struct TrieNode* children [ALPHABET_SIZE]; // Array to store child nodes (one for each letter)
    bool isEndOfWord; // Flag to mark end of a valid word
} TrieNode;

// Function declarations
TrieNode* createNode();
void insert(TrieNode* root, const char* word);
bool search(TrieNode* root, const char* word);
void printWordsWithPrefix(TrieNode* root, char* prefix, int level);
void autocomplete(TrieNode* root, const char* prefix);
void spellCheck(TrieNode* root, const char* word);
void predictNextWord(TrieNode* root, const char* prefix);
void freeTrie(TrieNode* root);

#endif // TRIE_H
