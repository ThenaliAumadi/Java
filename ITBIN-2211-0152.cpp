#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h> // for toupper

#define ALPHABET_SIZE 26

typedef struct TrieNode {
    struct TrieNode* children[ALPHABET_SIZE];
    bool isEndOfWord;
} TrieNode;

TrieNode* createNode() {
    TrieNode* node = (TrieNode*)malloc(sizeof(TrieNode));
    node->isEndOfWord = false;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        node->children[i] = NULL;
    }
    return node;
}

void insert(TrieNode* root, const char* word) {
    while (*word) {
        int index = tolower(*word) - 'a'; // Convert to lowercase before indexing
        if (!root->children[index]) {
            root->children[index] = createNode();
        }
        root = root->children[index];
        word++;
    }
    root->isEndOfWord = true;
}

bool search(TrieNode* root, const char* word) {
    while (*word) {
        int index = tolower(*word) - 'a'; // Convert to lowercase before indexing
        if (!root->children[index]) {
            return false;
        }
        root = root->children[index];
        word++;
    }
    return root && root->isEndOfWord;
}

void freeTrie(TrieNode* root) {
    if (root == NULL) return;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        freeTrie(root->children[i]);
    }
    free(root);
}

int main() {
    TrieNode* root = createNode();

    insert(root, "Apple");
    insert(root, "Banana");
    insert(root, "Orange");
    insert(root, "Grapes");
    insert(root, "Kiwi");

    char word[100];
    while (true) {
        printf("Enter a word to spell check (or type 'exit' to quit): ");
        fgets(word, sizeof(word), stdin);
        word[strcspn(word, "\n")] = '\0'; // Remove newline character
        if (strcmp(word, "exit") == 0) {
            break;
        }
        if (search(root, word)) {
            printf("The word '%s' is spelled correctly.\n", word);
        } else {
            printf("The word '%s' is spelled incorrectly.\n", word);
        }
    }

    freeTrie(root); // Free allocated memory

return 0;

}
