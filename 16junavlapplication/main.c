#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct listNode {
    int key;
    char value[50];
    struct listNode* left;
    struct listNode* right;
    int height;
};

int max(int a, int b) {
    return (a > b) ? a : b;
}

int height(struct listNode* node) {
    if (node == NULL)
        return 0;
    return node->height;
}

struct listNode* newNode(int key, char value[]) {
    struct listNode* node = (struct listNode*)malloc(sizeof(struct listNode));
    node->key = key;
    strcpy(node->value, value);
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

struct listNode* rightRotate(struct listNode* y) {
    struct listNode* x = y->left;
    struct listNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

struct listNode* leftRotate(struct listNode* x) {
    struct listNode* y = x->right;
    struct listNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

int getBalance(struct listNode* node) {
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

struct listNode* insertNode(struct listNode* node, int key, char value[]) {
    if (node == NULL)
        return newNode(key, value);

    if (key < node->key)
        node->left = insertNode(node->left, key, value);
    else if (key > node->key)
        node->right = insertNode(node->right, key, value);
    else {
        printf("Key already exists. Ignoring the insertion.\n");
        return node;
    }

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);

    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

struct listNode* minValueNode(struct listNode* node) {
    struct listNode* current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

struct listNode* deleteNode(struct listNode* root, int key) {
    if (root == NULL)
        return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        if ((root->left == NULL) || (root->right == NULL)) {
            struct listNode* temp = root->left ? root->left : root->right;
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else
                *root = *temp;
            free(temp);
        } else {
            struct listNode* temp = minValueNode(root->right);
            root->key = temp->key;
            strcpy(root->value, temp->value);
            root->right = deleteNode(root->right, temp->key);
        }
    }

    if (root == NULL)
        return root;

    root->height = 1 + max(height(root->left), height(root->right));

    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

char* search(struct listNode* root, int key) {
    if (root == NULL || key == root->key)
        return (root == NULL) ? NULL : root->value;

    if (key < root->key)
        return search(root->left, key);

    return search(root->right, key);
}

void inorder(struct listNode* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("Key: %d, Value: %s\n", root->key, root->value);
        inorder(root->right);
    }
}

void freeAVLTree(struct listNode* root) {
    if (root != NULL) {
        freeAVLTree(root->left);
        freeAVLTree(root->right);
        free(root);
    }
}

int main() {
    struct listNode* root = NULL;
    int choice;
    int key;
    char value[50];

    while (1) {
        printf("\nStudent information using AVL Tree \n");
        printf("1. Insert a key-value pair\n");
        printf("2. Delete a key-value pair\n");
        printf("3. Search for a key\n");
        printf("4. Display the details\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\nEnter the key: ");
                scanf("%d", &key);
                printf("Enter the value: ");
                scanf("%s", value);
                root = insertNode(root, key, value);
                printf("Key-value pair inserted successfully.\n");
                break;

            case 2:
                printf("\nEnter the key to delete: ");
                scanf("%d", &key);
                root = deleteNode(root, key);
                printf("Key-value pair deleted successfully.\n");
                break;

            case 3:
                printf("\nEnter the key to search: ");
                scanf("%d", &key);
                char* result = search(root, key);
                if (result == NULL)
                    printf("Key not found.\n");
                else
                    printf("Value: %s\n", result);
                break;

            case 4:
                printf("\nStudent information:\n");
                inorder(root);
                break;

            case 5:
                freeAVLTree(root);
                printf("\nMemory freed. Exiting...\n");
                exit(0);

            default:
                printf("\nInvalid choice. Please try again.\n");
                break;
        }
    }

    return 0;
}
