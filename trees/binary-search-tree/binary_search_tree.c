/*
 * Project: Binary Search Tree
 * Description: Implements insertion, search, deletion, and traversal operations for a binary search tree.
 * Author: Foad Zahedi Labaf
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int key;
    struct Node *left;
    struct Node *right;
} Node;

Node *create_node(int key);
Node *insert_node(Node *root, int key);
Node *delete_node(Node *root, int key, int *deleted);
Node *find_minimum(Node *root);
Node *search_node(Node *root, int key);
void print_preorder(const Node *root);
void print_inorder(const Node *root);
void print_postorder(const Node *root);
void free_tree(Node *root);
int count_nodes(const Node *root);
int calculate_height(const Node *root);
void print_tree_summary(const Node *root);
void print_menu(void);
void clear_input_buffer(void);
void insert_keys_from_line(Node **root);
int read_integer_choice(int *choice);

int main(void) {
    Node *root = NULL;
    int choice;
    int key;

    while (1) {
        print_menu();

        if (!read_integer_choice(&choice)) {
            printf("Invalid input. Exiting program.\n");
            break;
        }

        switch (choice) {
            case 1:
                insert_keys_from_line(&root);
                break;

            case 2:
                printf("Enter key to search: ");
                if (scanf("%d", &key) == 1) {
                    printf(search_node(root, key) != NULL ? "Key found.\n" : "Key not found.\n");
                } else {
                    printf("Invalid key.\n");
                    clear_input_buffer();
                }
                break;

            case 3: {
                int deleted = 0;

                printf("Enter key to delete: ");
                if (scanf("%d", &key) == 1) {
                    root = delete_node(root, key, &deleted);
                    printf(deleted ? "Deleted successfully.\n" : "Key not found.\n");
                } else {
                    printf("Invalid key.\n");
                    clear_input_buffer();
                }
                break;
            }

            case 4:
                printf("Preorder traversal: ");
                print_preorder(root);
                printf("\n");
                break;

            case 5:
                printf("Inorder traversal: ");
                print_inorder(root);
                printf("\n");
                break;

            case 6:
                printf("Postorder traversal: ");
                print_postorder(root);
                printf("\n");
                break;

            case 7:
                print_tree_summary(root);
                break;

            case 0:
                free_tree(root);
                printf("Done. Tree memory released successfully.\n");
                return EXIT_SUCCESS;

            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }

        printf("\n");
    }

    free_tree(root);
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

Node *insert_node(Node *root, int key) {
    if (root == NULL) {
        return create_node(key);
    }

    if (key < root->key) {
        root->left = insert_node(root->left, key);
    } else if (key > root->key) {
        root->right = insert_node(root->right, key);
    } else {
        printf("Key %d already exists. Duplicate ignored.\n", key);
    }

    return root;
}

Node *delete_node(Node *root, int key, int *deleted) {
    if (root == NULL) {
        return NULL;
    }

    if (key < root->key) {
        root->left = delete_node(root->left, key, deleted);
    } else if (key > root->key) {
        root->right = delete_node(root->right, key, deleted);
    } else {
        Node *replacement;
        *deleted = 1;

        if (root->left == NULL) {
            replacement = root->right;
            free(root);
            return replacement;
        }

        if (root->right == NULL) {
            replacement = root->left;
            free(root);
            return replacement;
        }

        replacement = find_minimum(root->right);
        root->key = replacement->key;
        root->right = delete_node(root->right, replacement->key, deleted);
    }

    return root;
}

Node *find_minimum(Node *root) {
    if (root == NULL) {
        return NULL;
    }

    while (root->left != NULL) {
        root = root->left;
    }

    return root;
}

Node *search_node(Node *root, int key) {
    if (root == NULL || root->key == key) {
        return root;
    }

    if (key < root->key) {
        return search_node(root->left, key);
    }

    return search_node(root->right, key);
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

void free_tree(Node *root) {
    if (root == NULL) {
        return;
    }

    free_tree(root->left);
    free_tree(root->right);
    free(root);
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

void print_tree_summary(const Node *root) {
    const Node *minimum = root;
    const Node *maximum = root;

    if (root == NULL) {
        printf("Tree is empty.\n");
        return;
    }

    while (minimum->left != NULL) {
        minimum = minimum->left;
    }

    while (maximum->right != NULL) {
        maximum = maximum->right;
    }

    printf("Number of nodes: %d\n", count_nodes(root));
    printf("Tree height: %d\n", calculate_height(root));
    printf("Minimum key: %d\n", minimum->key);
    printf("Maximum key: %d\n", maximum->key);
}

void print_menu(void) {
    printf("Binary Search Tree Menu\n");
    printf("1. Insert one or more keys\n");
    printf("2. Search key\n");
    printf("3. Delete key\n");
    printf("4. Print preorder traversal\n");
    printf("5. Print inorder traversal\n");
    printf("6. Print postorder traversal\n");
    printf("7. Print tree summary\n");
    printf("0. Exit\n");
    printf("Choice: ");
}

void clear_input_buffer(void) {
    int character;

    while ((character = getchar()) != '\n' && character != EOF) {
        /* Discard invalid input. */
    }
}

void insert_keys_from_line(Node **root) {
    char line[512];
    char *token;
    int inserted_count = 0;

    printf("Enter keys separated by spaces: ");

    if (fgets(line, sizeof(line), stdin) == NULL) {
        printf("Invalid input.\n");
        return;
    }

    if (line[0] == '\n' || line[0] == '\0') {
        printf("No keys entered.\n");
        return;
    }

    token = strtok(line, " \t\n");

    while (token != NULL) {
        char *end_ptr;
        long value = strtol(token, &end_ptr, 10);

        if (*token != '\0' && *end_ptr == '\0') {
            *root = insert_node(*root, (int)value);
            inserted_count++;
        } else {
            printf("Skipped invalid key: %s\n", token);
        }

        token = strtok(NULL, " \t\n");
    }

    printf("Inserted %d key%s.\n", inserted_count, inserted_count == 1 ? "" : "s");
}

int read_integer_choice(int *choice) {
    char line[64];
    char *end_ptr;
    long value;

    if (fgets(line, sizeof(line), stdin) == NULL) {
        return 0;
    }

    value = strtol(line, &end_ptr, 10);

    if (line[0] == '\0' || (*end_ptr != '\n' && *end_ptr != '\0')) {
        return 0;
    }

    *choice = (int)value;
    return 1;
}