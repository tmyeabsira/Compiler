#ifndef ARITHMETIC_H
#define ARITHMETIC_H

// Define the structure for a parse tree node
typedef struct Node {
    int value;  // Used for storing the value of numbers or the result of an operation
    char op;    // Operator for non-leaf nodes
    struct Node* left;  // Left child
    struct Node* right; // Right child
} Node;

// Function prototypes
Node* createNode(int value, char op, Node* left, Node* right);
int evaluate(Node* node);
void printTree(Node* node, int level);
void freeTree(Node* node);

#endif

