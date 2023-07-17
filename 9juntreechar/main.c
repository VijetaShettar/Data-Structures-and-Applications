#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Node
{
    char data;
    struct Node* left;
    struct Node* right;
};

struct Node* createNode(char data)
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

struct Node* insert(struct Node* root, char data)
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
        fprintf(outFile, "%c ", root->data);
        preorderTraversal(root->left, outFile);
        preorderTraversal(root->right, outFile);
    }
}

void inorderTraversal(struct Node* root, FILE* outFile)
{
    if (root != NULL)
    {
        inorderTraversal(root->left, outFile);
        fprintf(outFile, "%c ", root->data);
        inorderTraversal(root->right, outFile);
    }
}

void postorderTraversal(struct Node* root, FILE* outFile)
{
    if (root != NULL)
    {
        postorderTraversal(root->left, outFile);
        postorderTraversal(root->right, outFile);
        fprintf(outFile, "%c ", root->data);
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
    int num_chars;
    printf("Enter the number of random characters to generate: ");
    scanf("%d", &num_chars);

    char lower_limit, upper_limit;
    printf("Enter the lower limit character: ");
    scanf(" %c", &lower_limit);
    printf("Enter the upper limit character: ");
    scanf(" %c", &upper_limit);

    FILE* file = fopen("tree2.txt", "w");
    if (file == NULL)
    {
        printf("Failed to open the file.\n");
        return 1;
    }

    srand(time(NULL));
    int i;
    struct Node* root = NULL;

    for (i = 0; i < num_chars; i++)
    {
        char random_char = (rand() % (upper_limit - lower_limit + 1)) + lower_limit;
        fprintf(file, "%c\n", random_char);
        root = insert(root, random_char);
    }

    FILE* fp = fopen("preorder1.txt", "w");
    fprintf(fp, "\nPreorder traversal: ");
    preorderTraversal(root, fp);

    FILE* fp1 = fopen("inorder1.txt", "w");
    fprintf(fp1, "\nInorder traversal: ");
    inorderTraversal(root, fp1);

    FILE* fp2 = fopen("postorder1.txt", "w");
    fprintf(fp2, "\nPostorder traversal: ");
    postorderTraversal(root, fp2);

    fclose(fp);
    fclose(fp1);
    fclose(fp2);

    freeTree(root);
    fclose(file);

    return 0;
}
