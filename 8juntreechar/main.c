#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct node {
  char data;
  struct node* right_child;
  struct node* left_child;
};

struct node* new_node(char x) {
  struct node* temp = malloc(sizeof(struct node));
  temp->data = x;
  temp->left_child = NULL;
  temp->right_child = NULL;
  return temp;
}

struct node* search(struct node* root, char x) {
  if (root == NULL || root->data == x)
    return root;
  else if (x > root->data)
    return search(root->right_child, x);
  else
    return search(root->left_child, x);
}

struct node* insert(struct node* root, char x) {
  if (root == NULL)
    return new_node(x);
  else if (x > root->data)
    root->right_child = insert(root->right_child, x);
  else
    root->left_child = insert(root->left_child, x);
  return root;
}

struct node* find_minimum(struct node* root) {
  if (root == NULL)
    return NULL;
  else if (root->left_child != NULL)
    return find_minimum(root->left_child);
  return root;
}

struct node* delete(struct node* root, char x) {
  if (root == NULL)
    return NULL;
  if (x > root->data)
    root->right_child = delete(root->right_child, x);
  else if (x < root->data)
    root->left_child = delete(root->left_child, x);
  else {
    if (root->left_child == NULL && root->right_child == NULL) {
      free(root);
      return NULL;
    } else if (root->left_child == NULL || root->right_child == NULL) {
      struct node* temp;
      if (root->left_child == NULL)
        temp = root->right_child;
      else
        temp = root->left_child;
      free(root);
      return temp;
    } else {
      struct node* temp = find_minimum(root->right_child);
      root->data = temp->data;
      root->right_child = delete(root->right_child, temp->data);
    }
  }
  return root;
}

void inorder(struct node* root, FILE* file) {
  if (root != NULL) {
    inorder(root->left_child, file);
    fprintf(file, "%c ", root->data);
    inorder(root->right_child, file);
  }
}

void preorder(struct node* root, FILE* file) {
  if (root != NULL) {
    fprintf(file, "%c ", root->data);
    preorder(root->left_child, file);
    preorder(root->right_child, file);
  }
}

void postorder(struct node* root, FILE* file) {
  if (root != NULL) {
    postorder(root->left_child, file);
    postorder(root->right_child, file);
    fprintf(file, "%c ", root->data);
  }
}

int main() {
  struct node* root = NULL;
  int choice;
  char value;
  srand(time(NULL));

  printf("Binary Search Tree Operations\n");
  printf("1. Insert Random Character\n");
  printf("2. Delete Random Character\n");
  printf("3. Inorder Traversal\n");
  printf("4. Preorder Traversal\n");
  printf("5. Postorder Traversal\n");
  printf("6. Exit\n");

  while (1) {
    printf("\nEnter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
      case 1:
        value = 'A' + rand() % 26;  // Generate a random uppercase character
        root = insert(root, value);
        printf("Random character '%c' inserted.\n", value);
        break;
      case 2:
        if (root == NULL) {
          printf("Tree is empty. Cannot delete.\n");
          break;
        }
        value = root->data;
        root = delete(root, value);
        printf("Random character '%c' deleted.\n", value);
        break;
      case 3: {
        FILE* file = fopen("inorder.txt", "w");
        if (file == NULL) {
          printf("Error opening file.\n");
          exit(1);
        }
        inorder(root, file);
        fclose(file);
        printf("Inorder traversal stored in 'inorder.txt'.\n");
        break;
      }
      case 4: {
        FILE* file = fopen("preorder.txt", "w");
        if (file == NULL) {
          printf("Error opening file.\n");
          exit(1);
        }
        preorder(root, file);
        fclose(file);
        printf("Preorder traversal stored in 'preorder.txt'.\n");
        break;
      }
      case 5: {
        FILE* file = fopen("postorder.txt", "w");
        if (file == NULL) {
          printf("Error opening file.\n");
          exit(1);
        }
        postorder(root, file);
        fclose(file);
        printf("Postorder traversal stored in 'postorder.txt'.\n");
        break;
      }
      case 6:
        exit(0);
      default:
        printf("Invalid choice. Please try again.\n");
    }
  }

  return 0;
}
