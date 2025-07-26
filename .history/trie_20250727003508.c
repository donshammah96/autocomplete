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
    strcpy(newPrefix, prefix);
    printf("Autocomplete suggestions for '%s':\n", prefix);
    printWordsWithPrefix(current, newPrefix, strlen(prefix));
    free(newPrefix);
}

// Spell checker: suggests corrections for a misspelled word
void spellCheck(TrieNode* root, const char* word) {
    if(search(root, word)) {
        printf("'%s' is spelled correctly \n", word);
        return;
    }
    printf("'%s' is misspelled. Possible corrections: \n", word);
    // Try single-character edits (insertions, deletions, substitutions)
    char* suggestion = (char*)malloc(strlen(word) + 2);
    // Try insertions
    for (int i = 0; i <= strlen(word); i++) {
        strcpy(suggestion, word);
        for (char c = 'a'; c <= 'z'; c++) {
            // Insert character c at position i
            memmove(suggestion + i + 1, suggestion + i, strlen(suggestion) - i + 1);
            suggestion[i] = c;
            if(search(root, suggestion)) {
                printf("%s\n", suggestion);
            }
        }
    }
    // Try deletions
    for (int i = 0; i <= strlen(word); i++) {
        strcpy(suggestion, word);
        memmove(suggestion + i, suggestion + i + 1, strlen(suggestion) - i);
        if (search(root, suggestion)) {
            printf("%s\n", suggestion);
        }
    }
    // Try substitutions
    for (int i = 0; i <= strlen(word); i++) {
        strcpy(suggestion, word);
        for (char c = 'a'; c <= 'z'; c++) {
            suggestion[i] = c;
            if(search(root, suggestion)) {
                printf("%s\n", suggestion);
            }
        }
    }
    free(suggestion);
}

// Word prediction: predicts next word based on prefix
void predictNextWord(TrieNode* root, const char* prefix) {
    printf("Word predictions for '%s':\n", prefix);
    autocomplete(root, prefix); // Uses same logic as autocomplete
}

// Function to free the trie memory
void freeTrie(TrieNode* root) {
    if (!root) return;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        freeTrie(root->children[i]); // Recursively free child nodes
    }
    free(root); // Free current node
}

int main() {
    TrieNode* root = createNode();

    // Insert sample words
    const char* words[] = {"cat", "car", "cart", "cake", "cell", "dog", "don", "dot"};
    for (int i = 0; i < 8; i++) {
        insert(root, words[i]);
    }

    // Autocomplete demo
    printf("==== Autocomplete Demo =====\n");
    autocomplete(root, "ca");

    // Spell checker demo
    printf("==== Spell Checker Demo =====\n");
    spellCheck(root, "kat");

    // Word prediction demo
    printf("==== Word Prediction Demo =====\n");
    predictNextWord(root, "ca");

    // Free trie
    freeTrie(root);
    return 0;
}