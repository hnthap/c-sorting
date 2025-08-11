/**
 * @file tree_sort.c
 * @author HN Thap
 * @brief An implementation of a recursive Tree sort algorithm.
 * @version 0.1
 * @date 2025-08-08
 * @copyright See LICENSE
 * 
 * @todo Use a balanced BST.
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Return code for tree sort that indicates success.
 */
#define CDSA_TREE_SORT_OK (0)

/**
 * @brief Return code for tree sort that indicates failure.
 */
#define CDSA_TREE_SORT_FAILED (1)

/**
 * @brief Return code for tree sort that indicates errors involving NULL.
 */
#define CDSA_TREE_SORT_NULL (2)

/**
 * @brief Return code for tree sort that indicates errors involving empty
 * containers.
 */
#define CDSA_TREE_SORT_EMPTY (3)

/**
 * @brief Return code for tree sort that indicates allocation failure.
 */
#define CDSA_TREE_SORT_ALLOC_FAILED (4)

/**
 * @brief Basic structure for a BST node.
 * 
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
 * @return BSTNode* Pointer to new allocated block
 */
BSTNode *new_bst_node(int data, BSTNode *left, BSTNode *right);

/**
 * @brief Allocate and initialize an empty BST.
 * 
 * @return BST* Pointer to new allocated block
 */
BST *new_bst();

/**
 * @brief Push new node to a BST.
 * 
 * @param tree Pointer to BST
 * @param data Data to be stored
 * @return int CDSA_TREE_SORT_OK if success,
 * otherwise, CDSA_TREE_SORT_ALLOC_FAILED when failed to allocate node.
 */
int push_bst(BST *tree, int data);

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
 * @brief Recursively traverse a BST tree to modify array (particularly used
 * inside tree_sort()).
 * 
 * @param arr Array
 * @param index_ref Reference to current index
 * @param node BST node
 */
void tree_sort_recursive(int arr[], int *index_ref, BSTNode *node);

/**
 * @brief Perform Tree sort on an array in-place.
 * 
 * @param arr_count Size of the array
 * @param arr The array
 * @return int CDSA_TREE_SORT_OK if success,
 * or CDSA_TREE_SORT_ALLOC_FAILED if failed to allocate memory,
 * otherwise, CDSA_TREE_SORT_FAILED, which indicates failure from
 * push_bst() or push_bst_stack().
 */
int tree_sort(int arr_count, int arr[]);

int main(int argc, char *argv[])
{
    int i, n;
    int *a;
    if (argc == 1)
    {
        fprintf(stderr, "Invalid arguments: Array size must be specified.\n");
        return 1;
    }
    n = atoi(argv[1]);
    if (n <= 0)
    {
        /* An empty array is sorted by nature. */
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
    a = malloc(n * sizeof(int));
    if (a == NULL)
    {
        fprintf(stderr, "Failed to allocate array. Exiting.\n");
        return 1;
    }
    for (i = 0; i < n; i += 1)
    {
        a[i] = atoi(argv[i + 2]);
    }
    tree_sort(n, a);
    for (i = 0; i < n; i += 1)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
    free(a);
    return 0;
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
    BSTNode *parent;
    if (tree->root == NULL)
    {
        tree->root = new_bst_node(data, NULL, NULL);
        if (tree->root == NULL)
        {
            fprintf(
                stderr,
                "Failed to push to BST: failed to allocate memory.\n"
            );
            return CDSA_TREE_SORT_ALLOC_FAILED;
        }
        return CDSA_TREE_SORT_OK;
    }
    parent = tree->root;
    while (1) /* Loop termination is warranteed. */
    {
        if (data <= parent->data)
        {
            if (parent->left == NULL)
            {
                parent->left = new_bst_node(data, NULL, NULL);
                if (parent->left == NULL)
                {
                    fprintf(
                        stderr,
                        "Failed to push to BST: failed to allocate memory.\n"
                    );
                    return CDSA_TREE_SORT_ALLOC_FAILED;
                }
                return CDSA_TREE_SORT_OK;
            }
            parent = parent->left;
        }
        else
        {
            if (parent->right == NULL)
            {
                parent->right = new_bst_node(data, NULL, NULL);
                if (parent->right == NULL)
                {
                    fprintf(
                        stderr,
                        "Failed to push to BST: failed to allocate memory.\n"
                    );
                    return CDSA_TREE_SORT_ALLOC_FAILED;
                }
                return CDSA_TREE_SORT_OK;
            }
            parent = parent->right;
        }
    }
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
        fprintf(stderr, "Failed to clear BST: tree is NULL.\n");
        return CDSA_TREE_SORT_NULL;
    }
    clear_bst_recursive(tree->root);
    tree->root = NULL;
    return CDSA_TREE_SORT_OK;
}

int destroy_bst(BST **tree_ref)
{
    if (tree_ref == NULL)
    {
        fprintf(stderr, "Failed to destroy BST: tree reference is NULL.\n");
        return CDSA_TREE_SORT_NULL;
    }
    if (*tree_ref == NULL)
    {
        return CDSA_TREE_SORT_OK;
    }
    /*
     * As per current implementation of clear_bst(),
     * since *tree_ref could not be NULL, clear_bst() would not fail.
     */
    (void)clear_bst(*tree_ref);
    free(*tree_ref);
    *tree_ref = NULL;
    return CDSA_TREE_SORT_OK;
}

void tree_sort_recursive(int arr[], int *index_ref, BSTNode *node)
{
    if (node == NULL) return;
    tree_sort_recursive(arr, index_ref, node->left);
    arr[(*index_ref)++] = node->data;
    tree_sort_recursive(arr, index_ref, node->right);
}

int tree_sort(int arr_count, int arr[])
{
    BST *tree;
    int i;
    int rc = CDSA_TREE_SORT_OK;
    if (arr == NULL)
    {
        fprintf(
            stderr,
            "Tree sort failed: invalid parameter: arr cannot be NULL.\n"
        );
        return CDSA_TREE_SORT_NULL;
    }
    if (arr_count < 2) return CDSA_TREE_SORT_OK;
    tree = new_bst();
    if (tree == NULL)
    {
        fprintf(stderr, "Tree sort failed: failed to allocate tree.\n");
        return CDSA_TREE_SORT_ALLOC_FAILED;
    }
    for (i = 0; i < arr_count; i++)
    {
        if (push_bst(tree, arr[i]) != CDSA_TREE_SORT_OK)
        {
            fprintf(stderr, "Tree sort failed: failed to push to tree.\n");
            rc = CDSA_TREE_SORT_FAILED;
            goto cleanup_tree_sort;
        }
    }
    i = 0;
    tree_sort_recursive(arr, &i, tree->root);
cleanup_tree_sort:
    if (destroy_bst(&tree) != CDSA_TREE_SORT_OK)
    {
        fprintf(
            stderr,
            "Tree sort failed: failed to destroy tree after using.\n"
        );
        return CDSA_TREE_SORT_FAILED;
    }
    return rc;
}
