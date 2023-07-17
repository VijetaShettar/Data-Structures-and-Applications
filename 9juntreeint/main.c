#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Node
{
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* createNode(int data)
{
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL)
    {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

struct Node* insert(struct Node* root, int data)
{
    if (root == NULL)
    {
        return createNode(data);
    }
    if (data < root->data)
    {
        root->left = insert(root->left, data);
    }
    else if (data > root->data)
    {
        root->right = insert(root->right, data);
    }
    return root;
}
void preorderTraversal(struct Node* root, FILE* outFile)
{
    if (root != NULL)
    {
        fprintf(outFile, "%d ", root->data);
        preorderTraversal(root->left, outFile);
        preorderTraversal(root->right, outFile);
    }
}

void inorderTraversal(struct Node* root, FILE* outFile)
{
    if (root != NULL)
    {
        inorderTraversal(root->left, outFile);
        fprintf(outFile, "%d ", root->data);
        inorderTraversal(root->right, outFile);
    }
}
void postorderTraversal(struct Node* root, FILE* outFile)
{
    if (root != NULL)
    {
        postorderTraversal(root->left, outFile);
        postorderTraversal(root->right, outFile);
        fprintf(outFile, "%d ", root->data);
    }
}
void freeTree(struct Node* root)
{
    if (root != NULL)
    {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int main()
{
    int num_numbers;
    printf("Enter the number of random numbers to generate: ");
    scanf("%d", &num_numbers);
    int lower_limit, upper_limit;
    printf("Enter the lower limit: ");
    scanf("%d", &lower_limit);
    printf("Enter the upper limit: ");
    scanf("%d", &upper_limit);
    FILE* file = fopen("tree1.txt", "w");
    if (file == NULL)
    {
        printf("Failed to open the file.\n");
        return 1;
    }
    srand(time(NULL));
    int i;
    struct Node* root = NULL;
    for (i = 0; i < num_numbers; i++)
    {
        int random_number = (rand() % (upper_limit - lower_limit + 1)) + lower_limit;
        fprintf(file, "%d\n", random_number);
        root = insert(root, random_number);
    }
    FILE* fp = fopen("preorder.txt", "w");
    fprintf(fp, "\nPreorder traversal: ");
    preorderTraversal(root, fp);
    FILE* fp1 = fopen("inorder.txt", "w");
    fprintf(fp1, "\nInorder traversal: ");
    inorderTraversal(root, fp1);
    FILE* fp2 = fopen("postorder.txt", "w");
    fprintf(fp2, "\nPostorder traversal: ");
    postorderTraversal(root, fp2);
    fclose(fp);
    fclose(fp1);
    fclose(fp2);
    return 0;
}
