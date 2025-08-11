/**
 * @file avl_tree.c
 * @author HN Thap
 * @brief Simple implementation of AVL Tree.
 * 
 * Just run to see the visualized AVL tree:
 * 
 * avl_tree 10 3 10 2 1 -100 4 95 3 489 78
 * 
 * in which
 *      avl_tree is the executable,
 *      10 is the array size,
 *      and 3, 10, ..., 78 is the 10-element array that need to be stored.
 * 
 * Expected output:
 * 
 *              489
 *         95
 *             78
 *     10
 *         4
 *             3
 * 3
 *         2
 *     1
 *         -100
 * 
 * @version 0.1
 * @date 2025-08-08
 * @copyright See LICENSE
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Retrieve the maximum value out of two values.
 * @return The larger value
 */
#define MAXIMUM(a, b) ((a) > (b) ? (a) : (b))

/**
 * @brief Basic structure of an AVL tree node.
 */
typedef struct AVLNode
{
    int data;
    int height;
    struct AVLNode *left;
    struct AVLNode *right;
} AVLNode;

/**
 * @brief Allocate and initialize new AVL tree node.
 * 
 * @param data Data
 * @param height AVL node height
 * @param left Left child
 * @param right Right child
 * @return AVLNode* Pointer to new allocated block if success,
 * otherwise, NULL.
 */
AVLNode *new_avl_node(int data, int height, AVLNode *left, AVLNode *right);

/**
 * @brief Retrieve node height.
 * 
 * @param node Pointer to node
 * @return int 0 if node pointer is NULL, otherwise, node's height.
 */
int get_avl_height(AVLNode *node);

/**
 * @brief Calculate the difference between left and right subtree heights.
 * This is the balance factor for AVL logic.
 * 
 * @param node Pointer to node
 * @return int Balance factor
 */
int get_avl_balance(AVLNode *node);

/**
 * @brief Standard right rotation in AVL tree.
 * 
 * @param y Root node pointer before rotating
 * @return AVLNode* Root node pointer after rotating
 */
AVLNode *right_rotate_avl(AVLNode *y);

/**
 * @brief Standard left rotation in AVL tree.
 * 
 * @param x Root node pointer before rotating.
 * @return AVLNode* Root node pointer after rotating.
 */
AVLNode *left_rotate_avl(AVLNode *x);

/**
 * @brief Insert node into AVL tree.
 * 
 * @param node Pointer to tree's root node
 * @param data Inserted data
 * @return AVLNode* Pointer to new tree's root node
 */
AVLNode *insert_avl(AVLNode *node, int data);

/**
 * @brief Destroy an AVL tree with all of his children, the children's children,
 * and so on.
 * 
 * @param node Pointer to tree's root node
 */
void destroy_avl(AVLNode *node);

/**
 * @brief Print an AVL tree sideways to standard output.
 * 
 * @param node Pointer to node
 * @param depth Node depth
 * @param is_right_child Whether this node is a right child of another
 * (zero means false, non-zero means true)
 */
void print_avl_sideways(const AVLNode *node, int depth);

int main(int argc, char *argv[])
{
    int i, n, rc;
    AVLNode *root = NULL, *temp;
    rc = 0;
    if (argc == 1)
    {
        fprintf(stderr, "Invalid arguments: Array size must be specified.\n");
        return 1;
    }
    n = atoi(argv[1]);
    if (n <= 0)
    {
        return 0;
    }
    if (argc != n + 2)
    {
        fprintf(
            stderr,
            "Invalid arguments: Array was expected to have %d element(s), "
            "but got %d instead.\n",
            n,
            argc - 2
        );
        return 1;
    }
    for (i = 0; i < n; i += 1)
    {
        temp = insert_avl(root, atoi(argv[i + 2]));
        if (temp == NULL)
        {
            fprintf(stderr, "Failed to insert into AVL tree: allocation failure.\n");
            rc = 1;
            goto cleanup_main;
        }
        root = temp;
    }
    print_avl_sideways(root, 0);
    printf("\n");
cleanup_main:
    destroy_avl(root);
    root = NULL; /* Defensive programming */
    return rc;
}

AVLNode *new_avl_node(int data, int height, AVLNode *left, AVLNode *right)
{
    AVLNode *node = malloc(sizeof(AVLNode));
    if (node == NULL)
    {
        fprintf(stderr, "Failed to initialize AVL node: allocation failure.\n");
        return NULL;
    }
    node->data = data;
    node->height = height;
    node->left = left;
    node->right = right;
    return node;
}

int get_avl_height(AVLNode *node)
{
    return node ? node->height : 0;
}

int get_avl_balance(AVLNode *node)
{
    return node ? get_avl_height(node->left) - get_avl_height(node->right) : 0;
}

AVLNode *right_rotate_avl(AVLNode *y)
{
    AVLNode *x = y->left;
    AVLNode *t2 = x->right;
    x->right = y;
    y->left = t2;
    y->height = MAXIMUM(get_avl_height(y->left), get_avl_height(y->right)) + 1;
    x->height = MAXIMUM(get_avl_height(x->left), get_avl_height(x->right)) + 1;
    return x;
}

AVLNode *left_rotate_avl(AVLNode *x)
{
    AVLNode *y = x->right;
    AVLNode *t2 = y->left;
    y->left = x;
    x->right = t2;
    x->height = MAXIMUM(get_avl_height(x->left), get_avl_height(x->right)) + 1;
    y->height = MAXIMUM(get_avl_height(y->left), get_avl_height(y->right)) + 1;
    return y;
}

AVLNode *insert_avl(AVLNode *node, int data)
{
    AVLNode *temp;
    int balance;
    if (node == NULL)
    {
        node = new_avl_node(data, 1, NULL, NULL);
        if (node == NULL)
        {
            fprintf(
                stderr,
                "Failed to insert into AVL tree: allocation failure.\n"
            );
        }
        return node;
    }
    if (data < node->data)
    {
        temp = insert_avl(node->left, data);
        if (temp == NULL)
        {
            fprintf(
                stderr,
                "Failed to insert into AVL tree: allocation failure.\n"
            );
            return NULL;
        }
        node->left = temp;
    }
    else
    {
        temp = insert_avl(node->right, data);
        if (temp == NULL)
        {
            fprintf(
                stderr,
                "Failed to insert into AVL tree: allocation failure.\n"
            );
            return NULL;
        }
        node->right = temp;
    }
    node->height = MAXIMUM(
        get_avl_height(node->left),
        get_avl_height(node->right)
    ) + 1;
    balance = get_avl_balance(node);
    if (balance > 1 && data < node->left->data)
    {
        return right_rotate_avl(node);
    }
    if (balance < -1 && data > node->right->data)
    {
        return left_rotate_avl(node);
    }
    if (balance > 1 && data > node->left->data)
    {
        node->left = left_rotate_avl(node->left);
        return right_rotate_avl(node);
    }
    if (balance < -1 && data < node->right->data)
    {
        node->right = right_rotate_avl(node->right);
        return left_rotate_avl(node);
    }
    return node;
}

void destroy_avl(AVLNode *node)
{
    if (node == NULL) return;
    destroy_avl(node->left);
    destroy_avl(node->right);
    free(node);
}

void print_avl_sideways(const AVLNode *node, int depth)
{
    int i;
    if (node == NULL) return;
    print_avl_sideways(node->right, depth + 1);
    for (i = 0; i < depth; i++) printf("    ");
    printf("%d\n", node->data);
    print_avl_sideways(node->left, depth + 1);
}
