#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define COUNT 10

// Austin Bangle
// Chpt7 PA

// Definition of the BST Node
typedef struct BSTNode {
    int key;                    // The key stored in the node
    struct BSTNode* left;       // Pointer to the left child
    struct BSTNode* right;      // Pointer to the right child
} BSTNode;

// Function to create a new BST node with a given key
BSTNode* createNode(int key) {
    BSTNode* newNode = (BSTNode*)malloc(sizeof(BSTNode));
    newNode->key = key;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Definition of the Binary Search Tree (BST)
typedef struct BST {
    BSTNode* root;              // Pointer to the root node of the BST
} BST;

// Function to create an empty BST
BST* createBST() {
    BST* tree = (BST*)malloc(sizeof(BST));
    tree->root = NULL;
    return tree;
}

// Returns the root node of the BST
BSTNode* getRoot(BST* tree) {
    return tree->root;
}

// -------------------------------------------------------------------------
// BSTSearchRecursive: Recursively searches for a node with the given key.
// If found, returns the pointer to the node; otherwise, returns NULL.
BSTNode* searchRecursive(BSTNode* node, int key) {
    // Base case: if the node is NULL or the key is found, return the node.
    if (node == NULL || node->key == key) {
        return node;
    }
    // If the key is less than the current node's key, search left.
    if (key < node->key) {
        return searchRecursive(node->left, key);
    } else {
        // Otherwise, search right.
        return searchRecursive(node->right, key);
    }
}

// -------------------------------------------------------------------------
// BSTSearch: Searches for a key in the BST using the recursive search helper.
BSTNode* search(BST* tree, int key) {
    return searchRecursive(tree->root, key);
}

// -------------------------------------------------------------------------
// BSTInsertRecursive: Recursively inserts nodeToInsert into the BST starting
// from the given parent node. Assumes that duplicate keys are not allowed.
void insertRecursive(BSTNode* parent, BSTNode* nodeToInsert) {
    // If the key of the node to insert is less than the parent's key,
    // then it should go in the left subtree.
    if (nodeToInsert->key < parent->key) {
        if (parent->left == NULL) {
            parent->left = nodeToInsert;
        } else {
            insertRecursive(parent->left, nodeToInsert);
        }
    } else {
        // Otherwise, the node should go in the right subtree.
        if (parent->right == NULL) {
            parent->right = nodeToInsert;
        } else {
            insertRecursive(parent->right, nodeToInsert);
        }
    }
}

// -------------------------------------------------------------------------
// BSTInsertNode: Inserts a node into the BST. If the BST is empty, the node
// becomes the root; otherwise, it is inserted recursively.
void insertNode(BST* tree, BSTNode* node) {
    if (tree->root == NULL) {
        tree->root = node;
    } else {
        insertRecursive(tree->root, node);
    }
}

// -------------------------------------------------------------------------
// Function to insert a key into the BST. Returns false if the key already exists
// (since duplicate keys are not allowed); otherwise, inserts the key and returns true.
bool insertKey(BST* tree, int key) {
    if (search(tree, key) != NULL) {
        return false; // Duplicate keys not allowed
    }
    BSTNode* newNode = createNode(key);
    insertNode(tree, newNode);
    return true;
}

// -------------------------------------------------------------------------
// printInReverseOrder: Performs a reverse in-order traversal (right, node, left)
// to print the BST keys in descending order.
void printInReverseOrder(BSTNode* node) {
    if (node == NULL) {
        return;
    }
    // First, traverse the right subtree.
    printInReverseOrder(node->right);
    // Then, print the current node's key.
    printf("%d ", node->key);
    // Finally, traverse the left subtree.
    printInReverseOrder(node->left);
}

// -------------------------------------------------------------------------
// print2DUtil: Utility function to print the BST in 2D using reverse inorder traversal.
// It prints nodes with increased spacing to represent tree levels.
void print2DUtil(BSTNode* root, int space) {
    if (root == NULL) {
        return;
    }
    space += COUNT; // Increase space for the next level
    print2DUtil(root->right, space);
    printf("\n");
    for (int i = COUNT; i < space; i++) {
        printf(" ");
    }
    printf("%d\n", root->key);
    print2DUtil(root->left, space);
}

// Wrapper function to print the BST in 2D.
void print2D(BSTNode* root) {
    print2DUtil(root, 0);
}

// -------------------------------------------------------------------------
// freeTree: Recursively frees all nodes in the BST to prevent memory leaks.
void freeTree(BSTNode* root) {
    if (root == NULL) {
        return;
    }
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

// -------------------------------------------------------------------------
// main: Demonstrates the BST functions by performing the following operations:
// 1. Inserts keys into the BST.
// 2. Prints the BST in reverse order (descending).
// 3. Prints the BST structure in 2D.
// 4. Searches for an existing key (27) and a non-existing key (89),
//    printing messages based on the search results.
int main() {
    // Create an empty BST.
    BST* tree = createBST();
    
    // Insert the specified keys in the given order.
    int keys[] = {35, 41, 13, 57, 3, 83, 88, 51, 38, 20, 11, 22, 27, 21, 48, 8};
    int n = sizeof(keys) / sizeof(keys[0]);
    for (int i = 0; i < n; i++) {
        insertKey(tree, keys[i]);
    }
    
    // Print the BST keys in descending order.
    printf("BST in reverse order (descending):\n");
    printInReverseOrder(tree->root);
    printf("\n");
    
    // Print the BST in 2D.
    printf("\nBST printed in 2D:\n");
    print2D(tree->root);
    
    // Search for an existing key: 27.
    BSTNode* foundNode = search(tree, 27);
    if (foundNode != NULL) {
        printf("\nKey 27 found in BST.\n");
    } else {
        printf("\nKey 27 not found in BST.\n");
    }
    
    // Search for a non-existing key: 89.
    foundNode = search(tree, 89);
    if (foundNode != NULL) {
        printf("Key 89 found in BST.\n");
    } else {
        printf("Key 89 not found in BST.\n");
    }
    
    // Free all allocated memory.
    freeTree(tree->root);
    free(tree);
    
    return 0;
}

