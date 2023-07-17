#include <stdio.h>
#include <stdlib.h>

// Structure for a binary tree node
struct Node {
    char data;
    struct Node* left;
    struct Node* right;
};

// Function to create a new node
struct Node* createNode(char data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to perform inorder traversal and write to file
void inorder(struct Node* root, FILE* file) {
    if (root == NULL)
        return;

    inorder(root->left, file);
    fprintf(file, "%c ", root->data);
    inorder(root->right, file);
}

// Function to perform preorder traversal and write to file
void preorder(struct Node* root, FILE* file) {
    if (root == NULL)
        return;

    fprintf(file, "%c ", root->data);
    preorder(root->left, file);
    preorder(root->right, file);
}

// Function to perform postorder traversal and write to file
void postorder(struct Node* root, FILE* file) {
    if (root == NULL)
        return;

    postorder(root->left, file);
    postorder(root->right, file);
    fprintf(file, "%c ", root->data);
}

// Function to generate a random character
char generateRandomChar() {
    return 'A' + rand() % 26; // Generates a random uppercase letter
}

// Function to generate a binary tree with random characters
struct Node* generateRandomBinaryTree(int size) {
    if (size <= 0)
        return NULL;

    struct Node* root = createNode(generateRandomChar());

    int leftSize = rand() % size;
    int rightSize = size - leftSize - 1;

    root->left = generateRandomBinaryTree(leftSize);
    root->right = generateRandomBinaryTree(rightSize);

    return root;
}

int main() {
    int treeSize;
    printf("Enter the size of the binary tree: ");
    scanf("%d", &treeSize);

    // Generate a random binary tree
    struct Node* root = generateRandomBinaryTree(treeSize);

    // Open output files
    FILE* inorderFile = fopen("inorder.txt", "w");
    FILE* preorderFile = fopen("preorder.txt", "w");
    FILE* postorderFile = fopen("postorder.txt", "w");

    if (inorderFile == NULL || preorderFile == NULL || postorderFile == NULL) {
        printf("Error opening output files!\n");
        exit(1);
    }

    // Perform traversals and write to files
    inorder(root, inorderFile);
    preorder(root, preorderFile);
    postorder(root, postorderFile);

    // Close output files
    fclose(inorderFile);
    fclose(preorderFile);
    fclose(postorderFile);

    printf("Traversals completed and written to files.\n");

    return 0;
}
