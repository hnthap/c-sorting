/**
 * @file tree_sort_no_recursion.c
 * @author HN Thap
 * @brief An implementation of a recursion-free Tree sort algorithm.
 * @version 0.1
 * @date 2025-08-08
 * @copyright See LICENSE
 * 
 * @todo Use a balanced BST.
 * @todo (Since balanced BST is implemented) Use recursion in some parts.
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Return code for tree sort that indicates success.
 */
#define C_SORTING_TREE_SORT_OK (0)

/**
 * @brief Return code for tree sort that indicates failure.
 */
#define C_SORTING_TREE_SORT_FAILED (1)

/**
 * @brief Return code for tree sort that indicates errors involving NULL.
 */
#define C_SORTING_TREE_SORT_NULL (2)

/**
 * @brief Return code for tree sort that indicates errors involving empty
 * containers.
 */
#define C_SORTING_TREE_SORT_EMPTY (3)

/**
 * @brief Return code for tree sort that indicates allocation failure.
 */
#define C_SORTING_TREE_SORT_ALLOC_FAILED (4)

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
 * @brief Basic structure for a BST-specific stack node.
 */
typedef struct BSTStackNode
{
    BSTNode *tree_node;
    struct BSTStackNode *down;
} BSTStackNode;

/**
 * @brief Basic structure for a BST-specific stack.
 */
typedef struct BSTStack
{
    BSTStackNode *top;
} BSTStack;

/**
 * @brief Allocate and initialize new BST-specific stack node.
 * 
 * @param tree_node The BST node pointer to be stored
 * @param down Pointer to the downward stack node
 * @return BSTStackNode* Pointer to new allocated block
 */
BSTStackNode *new_bst_stack_node(BSTNode *tree_node, BSTStackNode *down);

/**
 * @brief Allocate and initialize new empty BST-specific stack.
 * 
 * @return BSTStack* Pointer to new allocated block
 */
BSTStack *new_bst_stack();

/**
 * @brief Push new node into a BST-specific stack.
 * 
 * @param stack Pointer to stack
 * @param tree_node Pointer to the BST node to be stored
 * @return int C_SORTING_TREE_SORT_OK if success,
 * or C_SORTING_TREE_SORT_NULL if the stack pointer is NULL,
 * otherwise, C_SORTING_TREE_SORT_ALLOC_FAILED when failed to allocate new
 * node.
 */
int push_bst_stack(BSTStack *stack, BSTNode *tree_node);

/**
 * @brief Pop node from a BST-specific stack.
 * 
 * @param stack Pointer to stack
 * @param node_ref Reference of the pointer to stack
 * @return int C_SORTING_TREE_SORT_OK if success,
 * or C_SORTING_TREE_SORT_NULL if the stack pointer is NULL,
 * otherwise, C_SORTING_TREE_SORT_EMPTY when the stack is empty.
 */
int pop_bst_stack(BSTStack *stack, BSTNode **node_ref);

/**
 * @brief Destroy (including clearing and freeing) a BST-specific stack.
 * 
 * @param stack_ref Reference of the pointer to stack
 * @return int C_SORTING_TREE_SORT_OK if success,
 * otherwise, C_SORTING_TREE_SORT_NULL when the stack reference is NULL.
 */
int destroy_bst_stack(BSTStack **stack_ref);

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
 * @return int C_SORTING_TREE_SORT_OK if success,
 * otherwise, C_SORTING_TREE_SORT_ALLOC_FAILED when failed to allocate node.
 */
int push_bst(BST *tree, int data);

/**
 * @brief Clear a BST (without destroying it).
 * 
 * @param tree Pointer to BST
 * @return int C_SORTING_TREE_SORT_OK if success,
 * or C_SORTING_TREE_SORT_NULL if the tree pointer is NULL,
 * or C_SORTING_TREE_SORT_ALLOC_FAILED if failed to allocate memory,
 * otherwise, C_SORTING_TREE_SORT_FAILED, which indicates failure from
 * push_bst_stack().
 */
int clear_bst(BST *tree);

/**
 * @brief Destroy a BST.
 * 
 * @param tree_ref Reference of the pointer to BST
 * @return int C_SORTING_TREE_SORT_OK if success,
 * or C_SORTING_TREE_SORT_NULL if the BST reference is NULL,
 * otherwise, C_SORTING_TREE_SORT_FAILED, which indicates failure from
 * clear_bst().
 */
int destroy_bst(BST **tree_ref);

/**
 * @brief Perform Tree sort on an array in-place.
 * 
 * @param arr_count Size of the array
 * @param arr The array
 * @return int C_SORTING_TREE_SORT_OK if success,
 * or C_SORTING_TREE_SORT_ALLOC_FAILED if failed to allocate memory,
 * otherwise, C_SORTING_TREE_SORT_FAILED, which indicates failure from
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

BSTStackNode *new_bst_stack_node(BSTNode *tree_node, BSTStackNode *down)
{
    BSTStackNode *node = malloc(sizeof(BSTStackNode));
    if (node == NULL)
    {
        fprintf(
            stderr,
            "Failed to create new BST stack node: failed to allocate.\n"
        );
        return NULL;
    }
    node->tree_node = tree_node;
    node->down = down;
    return node;
}

BSTStack *new_bst_stack()
{
    BSTStack *stack = malloc(sizeof(BSTStack));
    if (stack == NULL)
    {
        fprintf(
            stderr,
            "Failed to create new BST stack: failed to allocate.\n"
        );
        return NULL;
    }
    stack->top = NULL;
    return stack;
}

int push_bst_stack(BSTStack *stack, BSTNode *tree_node)
{
    BSTStackNode *node;
    if (stack == NULL)
    {
        fprintf(stderr, "Failed to push to BST stack: stack is NULL.\n");
        return C_SORTING_TREE_SORT_NULL;
    }
    node = new_bst_stack_node(tree_node, stack->top);
    if (node == NULL)
    {
        fprintf(
            stderr,
            "Failed to push to BST stack: failed to allocate new node.\n"
        );
        return C_SORTING_TREE_SORT_ALLOC_FAILED;
    }
    stack->top = node;
    return C_SORTING_TREE_SORT_OK;
}

int pop_bst_stack(BSTStack *stack, BSTNode **node_ref)
{
    BSTStackNode *node;
    if (stack == NULL)
    {
        fprintf(stderr, "Failed to pop from BST stack: stack is NULL.\n");
        return C_SORTING_TREE_SORT_NULL;
    }
    if (stack->top == NULL)
    {
        fprintf(stderr, "Failed to pop from BST stack: stack is empty.\n");
        return C_SORTING_TREE_SORT_EMPTY;
    }
    if (node_ref) *node_ref = stack->top->tree_node;
    node = stack->top->down;
    free(stack->top);
    stack->top = node;
    return C_SORTING_TREE_SORT_OK;
}

int destroy_bst_stack(BSTStack **stack_ref)
{
    BSTStackNode *node;
    if (stack_ref == NULL)
    {
        fprintf(
            stderr,
            "Failed to destroy BST stack: stack reference is NULL.\n"
        );
        return C_SORTING_TREE_SORT_NULL;
    }
    if (*stack_ref == NULL)
    {
        return C_SORTING_TREE_SORT_OK;
    }
    while ((*stack_ref)->top)
    {
        node = (*stack_ref)->top;
        (*stack_ref)->top = (*stack_ref)->top->down;
        free(node);
    }
    free(*stack_ref);
    *stack_ref = NULL;
    return C_SORTING_TREE_SORT_OK;
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
        if (tree->root == NULL) goto cleanup_push_bst_alloc_failed;
        return C_SORTING_TREE_SORT_OK;
    }
    parent = tree->root;
    while (1) /* Loop termination is warranteed. */
    {
        if (data <= parent->data)
        {
            if (parent->left == NULL)
            {
                parent->left = new_bst_node(data, NULL, NULL);
                if (parent->left == NULL) goto cleanup_push_bst_alloc_failed;
                return C_SORTING_TREE_SORT_OK;
            }
            parent = parent->left;
        }
        else
        {
            if (parent->right == NULL)
            {
                parent->right = new_bst_node(data, NULL, NULL);
                if (parent->right == NULL) goto cleanup_push_bst_alloc_failed;
                return C_SORTING_TREE_SORT_OK;
            }
            parent = parent->right;
        }
    }
cleanup_push_bst_alloc_failed:
    fprintf(stderr, "Failed to push to BST: failed to allocate memory.\n");
    return C_SORTING_TREE_SORT_ALLOC_FAILED;
}

int clear_bst(BST *tree)
{
    BSTStack *s1, *s2;
    BSTNode *node;
    int rc = C_SORTING_TREE_SORT_OK;
    if (tree == NULL)
    {
        fprintf(stderr, "Failed to clear BST: tree is NULL.\n");
        return C_SORTING_TREE_SORT_NULL;
    }
    if (tree->root == NULL) return C_SORTING_TREE_SORT_OK;
    s1 = new_bst_stack();
    if (s1 == NULL)
    {
        fprintf(stderr, "Failed to clear BST: failed to allocate stack s1.\n");
        return C_SORTING_TREE_SORT_ALLOC_FAILED;
    }
    s2 = new_bst_stack();
    if (s2 == NULL)
    {
        fprintf(stderr, "Failed to clear BST: failed to allocate stack s2.\n");
        (void)destroy_bst_stack(&s1);
        return C_SORTING_TREE_SORT_ALLOC_FAILED;
    }
    if (push_bst_stack(s1, tree->root) != C_SORTING_TREE_SORT_OK)
    {
        fprintf(stderr, "Failed to clear BST: failed to push to stack s1.\n");
        rc = C_SORTING_TREE_SORT_FAILED;
        goto cleanup_clear_bst;
    }
    while (s1->top)
    {
        (void)pop_bst_stack(s1, &node);
        if (push_bst_stack(s2, node) != C_SORTING_TREE_SORT_OK)
        {
            fprintf(
                stderr,
                "Failed to clear BST: failed to push node to stack s2. "
                "Tree might be partially cleared.\n"
            );
            rc = C_SORTING_TREE_SORT_FAILED;
            goto cleanup_clear_bst;
        }
        if (node->left)
        {
            if (push_bst_stack(s1, node->left) != C_SORTING_TREE_SORT_OK)
            {
                fprintf(
                    stderr,
                    "Failed to clear BST: failed push left child to stack. "
                    "Memory leak possible.\n"
                );
                rc = C_SORTING_TREE_SORT_FAILED;
                goto cleanup_clear_bst;
            }
        }
        if (node->right)
        {
            if (push_bst_stack(s1, node->right) != C_SORTING_TREE_SORT_OK)
            {
                fprintf(
                    stderr,
                    "Failed to clear BST: failed push right child to stack.\n"
                );
                rc = C_SORTING_TREE_SORT_FAILED;
                goto cleanup_clear_bst;
            }
        }
    }
    while (s2->top)
    {
        (void)pop_bst_stack(s2, &node);
        free(node);
        node = NULL; /* Defensive programming */
    }
    tree->root = NULL;
cleanup_clear_bst:
    (void)destroy_bst_stack(&s1);
    (void)destroy_bst_stack(&s2);
    return rc;
}

int destroy_bst(BST **tree_ref)
{
    if (tree_ref == NULL)
    {
        fprintf(stderr, "Failed to destroy BST: tree reference is NULL.\n");
        return C_SORTING_TREE_SORT_NULL;
    }
    if (*tree_ref == NULL)
    {
        return C_SORTING_TREE_SORT_OK;
    }
    if (clear_bst(*tree_ref) != C_SORTING_TREE_SORT_OK)
    {
        fprintf(stderr, "Failed to destroy BST: failed to clear tree.\n");
        return C_SORTING_TREE_SORT_FAILED;
    }
    free(*tree_ref);
    *tree_ref = NULL;
    return C_SORTING_TREE_SORT_OK;
}

int tree_sort(int arr_count, int arr[])
{
    BST *tree;
    BSTNode *current;
    BSTStack *stack;
    int i;
    int rc = C_SORTING_TREE_SORT_OK;
    if (arr == NULL)
    {
        fprintf(
            stderr,
            "Tree sort failed: invalid parameter: arr cannot be NULL.\n"
        );
        return C_SORTING_TREE_SORT_NULL;
    }
    if (arr_count < 2) return C_SORTING_TREE_SORT_OK;
    stack = new_bst_stack();
    if (stack == NULL)
    {
        fprintf(stderr, "Tree sort failed: failed to allocate stack.\n");
        return C_SORTING_TREE_SORT_ALLOC_FAILED;
    }
    tree = new_bst();
    if (tree == NULL)
    {
        fprintf(stderr, "Tree sort failed: failed to allocate tree.\n");
        free(stack);
        return C_SORTING_TREE_SORT_ALLOC_FAILED;
    }
    for (i = 0; i < arr_count; i++)
    {
        if (push_bst(tree, arr[i]) != C_SORTING_TREE_SORT_OK)
        {
            fprintf(stderr, "Tree sort failed: failed to push to tree.\n");
            rc = C_SORTING_TREE_SORT_FAILED;
            goto cleanup_tree_sort;
        }
    }
    current = tree->root;
    i = 0;
    while (current || stack->top)
    {
        while (current)
        {
            if (push_bst_stack(stack, current) != C_SORTING_TREE_SORT_OK)
            {
                fprintf(stderr, "Failed to clear BST: failed push to stack.\n");
                rc = C_SORTING_TREE_SORT_FAILED;
                goto cleanup_tree_sort;
            }
            current = current->left;
        }
        (void)pop_bst_stack(stack, &current);
        arr[i++] = current->data;
        current = current->right;
    }
cleanup_tree_sort:
    (void)destroy_bst_stack(&stack);
    if (destroy_bst(&tree) != C_SORTING_TREE_SORT_OK)
    {
        fprintf(
            stderr,
            "Tree sort failed: failed to destroy tree after using.\n"
        );
        return C_SORTING_TREE_SORT_FAILED;
    }
    return rc;
}
