/**
 * @file simple_bst.c
 * @author HN Thap
 * @brief Simple implementation of simple, unbalanced binary search tree.
 * 
 * Just run to see the visualized tree:
 * 
 * simple_bst 10 3 10 2 1 -100 4 95 3 489 78
 * 
 * in which
 *      simple_bst is the executable,
 *      10 is the array size,
 *      and 3, 10, ..., 78 is the 10-element array that need to be stored.
 * 
 * Expected output:
 * 
 *             489
 *         95
 *             78
 *     10
 *         4
 * 3
 *         3
 *     2
 *         1
 *             -100
 * 
 * @version 0.1
 * @date 2025-08-11
 * @copyright See LICENSE
 */

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Return code for BST that indicates success.
 */
#define CDSA_SIMPLE_BST_OK (0)
/**
 * @brief Return code for BST that indicates failure.
 */
#define CDSA_SIMPLE_BST_FAILED (1)
/**
 * @brief Return code for BST that indicates errors involving NULL.
 */
#define CDSA_SIMPLE_BST_NULL (2)
/**
 * @brief Return code for BST that indicates errors involving empty
 * containers.
 */
#define CDSA_SIMPLE_BST_EMPTY (3)
/**
 * @brief Return code for BST that indicates allocation failure.
 */
#define CDSA_SIMPLE_BST_ALLOC_FAILED (4)
/**
 * @brief Return code for BST that indicates a failed search operation,
 * i.e. item is not found.
 */
#define CDSA_SIMPLE_BST_NOT_FOUND (5)

/**
 * @brief Basic structure for a BST node.
 */
typedef struct BSTNode
{
    int data;
    struct BSTNode *left;
    struct BSTNode *right;
} BSTNode;

/**
 * @brief Basic structure for a BST.
 */
typedef struct BST
{
    BSTNode *root;
} BST;

/**
 * @brief Allocate and initialize new BST node.
 * 
 * @param data Data
 * @param left Pointer to left child (NULL if not presenting)
 * @param right Pointer to right child (NULL if not presenting)
 * @return BSTNode* Pointer to new allocated block,
 * otherwise, NULL when allocation fails
 */
BSTNode *new_bst_node(int data, BSTNode *left, BSTNode *right);

/**
 * @brief Allocate and initialize an empty BST.
 * 
 * @return BST* Pointer to new allocated block,
 * otherwise, NULL when allocation fails
 */
BST *new_bst();

/**
 * @brief Push new node to a BST. If the inserted value has already existed
 * in the tree, a new node with that value would be pushed to the left subtree
 * of the existing node with the same value.
 * 
 * @param tree Pointer to BST
 * @param data Data to be stored
 * @return int CDSA_SIMPLE_BST_OK if success,
 * or, CDSA_SIMPLE_BST_NULL if tree pointer is NULL,
 * otherwise, CDSA_SIMPLE_BST_ALLOC_FAILED when failed to allocate node.
 */
int push_bst(BST *tree, int data);

/**
 * @brief Search for node to delete. Particularly used inside pop_bst(), never
 * use it anywhere else except you have a ridiculously good reason.
 * 
 * @param tree Pointer to BST (This has to be not NULL, otherwise, undefined
 * behavior is warranted.)
 * @param data Data to delete
 * @param parent_ref Reference of pointer to parent
 * @param node_ref Reference of pointer to node
 * @param is_right_child_ref Reference to value indicating whether the node to
 * delete is a right child of another (ignored when node to delete is root)
 * @return CDSA_SIMPLE_BST_OK if found,
 * otherwise, CDSA_SIMPLE_BST_NOT_FOUND when not found.
 */
int pop_bst_search(
    BST *tree,
    int data,
    BSTNode **parent_ref,
    BSTNode **node_ref,
    unsigned char *is_right_child_ref
);

/**
 * @brief Pop (delete) node from a BST.
 * 
 * @param tree Pointer to tree
 * @param data Data to delete
 * @return int CDSA_SIMPLE_BST_OK if success,
 * or, CDSA_SIMPLE_BST_NOT_FOUND if the value to data is not found,
 * otherwise, CDSA_SIMPLE_BST_NULL if tree pointer is NULL.
 */
int pop_bst(BST *tree, int data);

/**
 * @brief Search data inside a BST.
 * 
 * @param tree Pointer to BST
 * @param data Data to search
 * @return int CDSA_SIMPLE_BST_OK if found,
 * or CDSA_SIMPLE_BST_NOT_FOUND if not found,
 * otherwise, CDSA_SIMPLE_BST_NULL when the tree pointer is NULL.
 */
int search_bst(const BST *tree, int data);

/**
 * @brief Recursively clear a BST node and all of its children (particularly
 * used inside clear_bst()).
 * 
 * @param node Pointer to BST node.
 */
void clear_bst_recursive(BSTNode *node);

/**
 * @brief Clear a BST (without destroying it).
 * 
 * @param tree Pointer to BST
 * @return int CDSA_SIMPLE_BST_OK if success,
 * otherwise, CDSA_SIMPLE_BST_NULL when the tree pointer is NULL.
 */
int clear_bst(BST *tree);

/**
 * @brief Destroy a BST.
 * 
 * @param tree_ref Reference of the pointer to BST
 * @return int CDSA_SIMPLE_BST_OK if success,
 * otherwise, CDSA_SIMPLE_BST_NULL when the BST reference is NULL.
 */
int destroy_bst(BST **tree_ref);

/**
 * @brief Print an BST node and its children recursively sideways to standard
 * output (particularly used inside print_bst_sideways()).
 * 
 * @param node Pointer to node
 * @param level Node level
 */
void print_bst_sideways_recursive(const BSTNode *node, int level);

/**
 * @brief Print an BST tree sideways to standard output.
 * 
 * @param tree Pointer to tree
 * @return CDSA_SIMPLE_BST_OK if success,
 * otherwise, CDSA_SIMPLE_BST_NULL if tree pointer is NULL
 */
int print_bst_sideways(const BST *tree);

static int safe_atoi(char *s, int *result_ref)
{
    long t;
    char *end;
    t = strtol(s, &end, 10);
    if (*end != '\0' || t < INT_MIN || t > INT_MAX)
    {
        return CDSA_SIMPLE_BST_FAILED;
    }
    *result_ref = (int)t;
    return CDSA_SIMPLE_BST_OK;
}

static void bst_replace_node(
    BST *tree,
    BSTNode *parent,
    unsigned char is_right_child,
    BSTNode *new_node
)
{
    if (parent == NULL) tree->root = new_node;
    else if (is_right_child) parent->right = new_node;
    else parent->left = new_node;
}

int main(int argc, char *argv[])
{
    int i, n, rc, temp;
    BST *tree;
    rc = 0;
    if (argc == 1)
    {
        fprintf(stderr, "Invalid arguments: Array size must be specified.\n");
        return 1;
    }
    if (safe_atoi(argv[1], &n) != CDSA_SIMPLE_BST_OK)
    {
        fprintf(stderr, "Invalid array size: %s\n", argv[1]);
        return 1;
    }
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
    tree = new_bst();
    if (tree == NULL)
    {
        fprintf(stderr, "Critical error: allocation failed.\n");
        return 1;
    }
    for (i = 0; i < n; i += 1)
    {
        if (safe_atoi(argv[i + 2], &temp) != CDSA_SIMPLE_BST_OK)
        {
            fprintf(
                stderr,
                "Invalid value at index %d: %s\n",
                i + 2,
                argv[i + 2]
            );
            rc = 1;
            goto cleanup_main;
        }
        if (push_bst(tree, temp) != CDSA_SIMPLE_BST_OK)
        {
            fprintf(stderr, "Failed to insert into BST: allocation failure.\n");
            rc = 1;
            goto cleanup_main;
        }
    }
    /* NULL check for tree has already been performed,
     * so print_bst_sideways() cannot fail. */
    (void)print_bst_sideways(tree);
    printf("\n");
cleanup_main:
    /* NULL check for tree has already been performed,
     * so destroy_bst() cannot fail. */
    (void)destroy_bst(&tree);
    tree = NULL; /* Defensive programming */
    return rc;
}

BSTNode *new_bst_node(int data, BSTNode *left, BSTNode *right)
{
    BSTNode *node = malloc(sizeof(BSTNode));
    if (node == NULL)
    {
        fprintf(stderr, "Failed to create new BST node: failed to allocate.\n");
        return NULL;
    }
    node->data = data;
    node->left = left;
    node->right = right;
    return node;
}

BST *new_bst()
{
    BST *tree = malloc(sizeof(BST));
    if (tree == NULL)
    {
        fprintf(stderr, "Failed to create new BST: failed to allocate.\n");
        return NULL;
    }
    tree->root = NULL;
    return tree;
}

int push_bst(BST *tree, int data)
{
    BSTNode **current;
    if (tree == NULL)
    {
        fprintf(stderr, "Failed to push to BST: tree pointer is NULL.\n");
        return CDSA_SIMPLE_BST_NULL;
    }
    current = &(tree->root);
    while (*current)
    {
        if (data <= (*current)->data)
        {
            current = &((*current)->left);
        }
        else
        {
            current = &((*current)->right);
        }
    }
    *current = new_bst_node(data, NULL, NULL);
    if (*current == NULL)
    {
        fprintf(
            stderr,
            "Failed to push to BST: failed to allocate memory.\n"
        );
        return CDSA_SIMPLE_BST_ALLOC_FAILED;
    }
    return CDSA_SIMPLE_BST_OK;
}

int pop_bst_search(
    BST *tree,
    int data,
    BSTNode **parent_ref,
    BSTNode **node_ref,
    unsigned char *is_right_child_ref
)
{
    BSTNode *node, *parent;
    unsigned char is_right_child = 0; /* Defensive initialization */
    node = tree->root;
    parent = NULL;
    while (node != NULL && node->data != data)
    {
        parent = node;
        if (data < node->data)
        {
            node = node->left;
            is_right_child = 0;
        }
        else
        {
            node = node->right;
            is_right_child = 1;
        }
    }
    if (node == NULL) return CDSA_SIMPLE_BST_NOT_FOUND;
    *node_ref = node;
    *parent_ref = parent;
    *is_right_child_ref = is_right_child;
    return CDSA_SIMPLE_BST_OK;
}

int pop_bst(BST *tree, int data)
{
    BSTNode *node = NULL;
    BSTNode *parent = NULL;
    unsigned char is_right_child = 0;
    BSTNode *pred_parent = NULL;
    BSTNode *pred = NULL;
    int rc;
    if (tree == NULL)
    {
        fprintf(stderr, "Failed to pop from BST: tree pointer is NULL.\n");
        return CDSA_SIMPLE_BST_NULL;
    }
    rc = pop_bst_search(tree, data, &parent, &node, &is_right_child);
    if (rc == CDSA_SIMPLE_BST_NOT_FOUND) return CDSA_SIMPLE_BST_NOT_FOUND;
    /* Case 1: No children */
    if (node->left == NULL && node->right == NULL)
    {
        bst_replace_node(tree, parent, is_right_child, NULL);
        free(node);
        return CDSA_SIMPLE_BST_OK;
    }
    /* Case 2: One child */
    if (node->left == NULL || node->right == NULL)
    {
        bst_replace_node(
            tree,
            parent,
            is_right_child,
            (node->left ? node->left : node->right)
        );
        free(node);
        return CDSA_SIMPLE_BST_OK;
    }
    /* Case 3: Two children - use inorder predecessor (max in left subtree) */
    pred_parent = node;
    pred = node->left;
    while (pred->right != NULL)
    {
        pred_parent = pred;
        pred = pred->right;
    }
    node->data = pred->data;
    if (pred_parent->right == pred)
    {
        pred_parent->right = pred->left;
    }
    else
    {
        pred_parent->left = pred->left;
    }
    free(pred);
    return CDSA_SIMPLE_BST_OK;
}

int search_bst(const BST *tree, int data)
{
    BSTNode *node;
    if (tree == NULL)
    {
        fprintf(stderr, "Failed to search BST: tree pointer is NULL.\n");
        return CDSA_SIMPLE_BST_NULL;
    }
    node = tree->root;
    while (node != NULL)
    {
        if (node->data == data) return CDSA_SIMPLE_BST_OK;
        node = (node->data > data) ? node->left : node->right;
    }
    return CDSA_SIMPLE_BST_NOT_FOUND;
}

void clear_bst_recursive(BSTNode *node)
{
    if (node != NULL)
    {
        clear_bst_recursive(node->left);
        clear_bst_recursive(node->right);
        free(node);
    }
}

int clear_bst(BST *tree)
{
    if (tree == NULL)
    {
        fprintf(stderr, "Failed to clear BST: tree pointer is NULL.\n");
        return CDSA_SIMPLE_BST_NULL;
    }
    clear_bst_recursive(tree->root);
    tree->root = NULL;
    return CDSA_SIMPLE_BST_OK;
}

int destroy_bst(BST **tree_ref)
{
    if (tree_ref == NULL)
    {
        fprintf(stderr, "Failed to destroy BST: tree reference is NULL.\n");
        return CDSA_SIMPLE_BST_NULL;
    }
    if (*tree_ref == NULL)
    {
        return CDSA_SIMPLE_BST_OK;
    }
    /*
     * As per current implementation of clear_bst(),
     * since *tree_ref could not be NULL, clear_bst() would not fail.
     */
    (void)clear_bst(*tree_ref);
    free(*tree_ref);
    *tree_ref = NULL;
    return CDSA_SIMPLE_BST_OK;
}

void print_bst_sideways_recursive(const BSTNode *node, int level)
{
    int i;
    if (node == NULL) return;
    print_bst_sideways_recursive(node->right, level + 1);
    for (i = 0; i < level; i++) printf("    ");
    printf("%d\n", node->data);
    print_bst_sideways_recursive(node->left, level + 1);
}

int print_bst_sideways(const BST *tree)
{
    if (tree == NULL)
    {
        fprintf(stderr, "Failed to print BST sideways: tree pointer is NULL.\n");
        return CDSA_SIMPLE_BST_NULL;
    }
    print_bst_sideways_recursive(tree->root, 0);
    return CDSA_SIMPLE_BST_OK;
}
