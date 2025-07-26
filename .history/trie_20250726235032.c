#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Defining trie node structure 
#define ALPHABET_SIZE 26
typedef struct TrieNode
{
    struct TrieNode* children [ALPHABET_SIZE]; // Array to store child nodes (one for each letter)
    bool isEndOfWord; // Flag to mark end of a valid word
} TrieNode;

//Function to create a new trie node
TrieNode* createNode() {
    TrieNode* node = (TrieNode*)malloc(sizeof(TrieNode));
    if (node) {
        node->isEndOfWord = false;
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            node->children[i] = NULL; // Initialize all children to NULL
        }
    }
    return node;
}

//Function to insert a word into the trie
void insert(TrieNode* root, const char* word) {
    TrieNode* current = root;
    for (int i = 0; word[i] != '\0'; i++) {
        int index = word[i] - 'a'; // Calculate index assuming lowercase letters.
        if (index < 0 || index >= ALPHABET_SIZE) continue; // Skip invalid characters
        if (!current->children[index]) {
            current->children[index] = createNode(); // Create a new node if it doesn't exist
        }
        current = current->children[index];
    }
    current->isEndOfWord = true; // Mark the end of the word
}

// Function to search for a word in the trie
bool search(TrieNode* root, const char* word) {
    TrieNode* current = root;
    for(int i = 0; word[i] != '\0'; i++) {
        int index = word[i] - 'a';
        if (index < 0 || index >= ALPHABET_SIZE || !current->children[index]) {
            return false; // Word not found or invalid character
        }
        current = current->children[index];
    }
    return current && current->isEndOfWord; // Return true if word exists and is complete
}

// Helper function for autocomplete: prints all words with a given prefix
void printWordsWithPrefix(TrieNode* root, char* prefix, int level) {
    if(root->isEndOfWord) {
        prefix[level] = '\0';
        printf("%s\n", prefix); // Print complete word
    }
    for(int i = 0; i < ALPHABET_SIZE; i++) {
        if(root->children[i]) {
            prefix[level] = i + 'a'; // Add current character to prefix
            printWordsWithPrefix(root->children[i], prefix, level + 1); // Recurse for child nodes
        }
    }
}

// Autocomplete function: finds and prints all words with given prefix
void autocomplete(TrieNode* root, const char* prefix) {
    TrieNode* current = root;
    // Traverse to the node representing the prefix
    for (int i = 0; prefix[i] != '\0'; i++) {
        int index = prefix[i] - 'a';
        if (index < 0 || index >= ALPHABET_SIZE || !current->children[index]) {
            printf("No words found with prefix '%s'\n", prefix);
            return;
        }
        current = current->children[index];
    }
    // Print all words starting from this node
    char* newPrefix = (char*)mallock(strlen(prefix) + 100); // Buffer for building words
    

}