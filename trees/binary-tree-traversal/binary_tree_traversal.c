/*
 * Project: Binary Tree Traversal
 * Description: Builds a binary tree from user input and prints preorder, inorder, and postorder traversals.
 * Author: Foad Zahedi Labaf
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_SIZE 100
#define NULL_INPUT "NULL"

typedef struct Node {
    int key;
    struct Node *left;
    struct Node *right;
} Node;

Node *create_node(int key);
Node *build_tree_from_input(void);
Node *build_tree_recursive(int key);
void print_preorder(const Node *root);
void print_inorder(const Node *root);
void print_postorder(const Node *root);
int count_nodes(const Node *root);
int calculate_height(const Node *root);
void free_tree(Node *root);
int read_integer_or_null(const char *prompt, int *value, int *is_null);
int parse_integer(const char *text, int *value);

int main(void) {
    Node *root = build_tree_from_input();

    printf("\nPreorder traversal: ");
    print_preorder(root);
    printf("\n");

    printf("Inorder traversal: ");
    print_inorder(root);
    printf("\n");

    printf("Postorder traversal: ");
    print_postorder(root);
    printf("\n");

    printf("Number of nodes: %d\n", count_nodes(root));
    printf("Tree height: %d\n", calculate_height(root));

    free_tree(root);

    printf("Done. Tree memory released successfully.\n");

    return EXIT_SUCCESS;
}

Node *create_node(int key) {
    Node *node = malloc(sizeof(Node));

    if (node == NULL) {
        fprintf(stderr, "Error: memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    node->key = key;
    node->left = NULL;
    node->right = NULL;

    return node;
}

Node *build_tree_from_input(void) {
    int root_key;
    int is_null;

    read_integer_or_null("Enter root value: ", &root_key, &is_null);

    if (is_null) {
        return NULL;
    }

    return build_tree_recursive(root_key);
}

Node *build_tree_recursive(int key) {
    Node *node = create_node(key);
    int child_key;
    int is_null;
    char prompt[INPUT_SIZE];

    snprintf(prompt, sizeof(prompt), "Enter left child of %d, or NULL: ", key);
    read_integer_or_null(prompt, &child_key, &is_null);

    if (!is_null) {
        node->left = build_tree_recursive(child_key);
    }

    snprintf(prompt, sizeof(prompt), "Enter right child of %d, or NULL: ", key);
    read_integer_or_null(prompt, &child_key, &is_null);

    if (!is_null) {
        node->right = build_tree_recursive(child_key);
    }

    return node;
}

void print_preorder(const Node *root) {
    if (root == NULL) {
        return;
    }

    printf("%d ", root->key);
    print_preorder(root->left);
    print_preorder(root->right);
}

void print_inorder(const Node *root) {
    if (root == NULL) {
        return;
    }

    print_inorder(root->left);
    printf("%d ", root->key);
    print_inorder(root->right);
}

void print_postorder(const Node *root) {
    if (root == NULL) {
        return;
    }

    print_postorder(root->left);
    print_postorder(root->right);
    printf("%d ", root->key);
}

int count_nodes(const Node *root) {
    if (root == NULL) {
        return 0;
    }

    return 1 + count_nodes(root->left) + count_nodes(root->right);
}

int calculate_height(const Node *root) {
    if (root == NULL) {
        return -1;
    }

    int left_height = calculate_height(root->left);
    int right_height = calculate_height(root->right);

    return 1 + (left_height > right_height ? left_height : right_height);
}

void free_tree(Node *root) {
    if (root == NULL) {
        return;
    }

    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

int read_integer_or_null(const char *prompt, int *value, int *is_null) {
    char input[INPUT_SIZE];

    while (1) {
        printf("%s", prompt);

        if (scanf("%99s", input) != 1) {
            fprintf(stderr, "Error: failed to read input.\n");
            exit(EXIT_FAILURE);
        }

        if (strcmp(input, NULL_INPUT) == 0) {
            *is_null = 1;
            return 1;
        }

        if (parse_integer(input, value)) {
            *is_null = 0;
            return 1;
        }

        printf("Invalid input. Please enter an integer or NULL.\n");
    }
}

int parse_integer(const char *text, int *value) {
    char *end_ptr;
    long number = strtol(text, &end_ptr, 10);

    if (*text == '\0' || *end_ptr != '\0') {
        return 0;
    }

    *value = (int)number;
    return 1;
}