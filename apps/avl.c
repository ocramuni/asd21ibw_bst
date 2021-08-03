//
// AVL tree (height balanced binary search tree)
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_SIZE 1000   // maximum size of a line of input
#define MAX_CMD_LENGTH 15   // maximum length of a command name

/**
 * Extract command, key and data from command line.
 * @param cmd command to execute
 * @param key key to use
 * @param data data to insert in key
 */
void scanLine(char *cmd, int *key, char *data) {
    // scan line of text
    char line[MAX_LINE_SIZE];
    /*
     * You can instruct the scanf to ignore the special characters
     * by prefixing % by a space character.
     */
    scanf(" %[^\n]s", line);

    char *tmp_cmd=strtok(line, " ");

    /*
     * strcpy doesn't allocate memory for you.
     * you need to have the destination of strcpy be already
     * allocated memory locations
    */
    strcpy(cmd, tmp_cmd);

    char *param = strtok(NULL, "\n");

    char tmp_data[MAX_LINE_SIZE];
    strcpy(tmp_data, "");
    // A null pointer is returned if there are no tokens left to retrieve.
    if  (param != NULL) {
        sscanf(param, "%d%s", key, tmp_data);
        if ((strcmp(tmp_data, "") == 0)) {
            strcpy(data, "");
        } else {
            strcpy(data, tmp_data);
        }
    } else {
        strcpy(data, "");
        *key = 0;
    }
}

/**
 * Structure to represent each
 * node in an AVL binary search tree
 */
typedef struct avl_node
{
    int key;
    char *data;
    int height;
    struct avl_node *left;
    struct avl_node *right;
} avl_node;

/**
 * Get the height of the node
 * @param avl_node AVL node
 * @return height of the node
 */
int height(struct avl_node* node)
{
    if (node == NULL)
        return 0;
    return node->height;
}

/**
 * Get maximum of two integers
 * @param a int first integer
 * @param b int second integer
 * @return max of two values
 */
int max(int a, int b)
{
    return (a > b)? a : b;
}

/**
 * Right rotate AVL subtree rooted with y
 * @param root avl_node AVL root
 * @return rotated AVL
 */
struct avl_node* avl_right_rotate(struct avl_node* root)
{
    struct avl_node* x = root->left;
    struct avl_node* T2 = x->right;

    // Perform rotation
    x->right = root;
    root->left = T2;

    // Update heights
    root->height = max(height(root->left), height(root->right))+1;
    x->height = max(height(x->left), height(x->right))+1;

    // Return new root
    return x;
}

/**
 * Left rotate AVL subtree rooted with y
 * @param root avl_node AVL root
 * @return rotated AVL
 */
struct avl_node *avl_left_rotate(struct avl_node* root)
{
    struct avl_node *y = root->right;
    struct avl_node *T2 = y->left;

    // Perform rotation
    y->left = root;
    root->right = T2;

    //  Update heights
    root->height = max(height(root->left), height(root->right))+1;
    y->height = max(height(y->left), height(y->right))+1;

    // Return new root
    return y;
}

/**
 * Get balance factor of node N
 * @param node avl_node
 * @return balance factor
 */
int getBalance(struct avl_node* node)
{
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

/**
 * Create a new avl_node
 * @param key node key
 * @param data node value
 * @return new avl node
 */
struct avl_node* avl_create(int key, char *data)
{
    struct avl_node *new_node;
    new_node = (struct avl_node *) malloc(sizeof(avl_node));
    if (new_node == NULL)
    {
        fprintf (stderr, "create avl node fail\n");
        exit(1);
    }
    new_node->key = key;
    new_node->data = strdup(data);
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->height = 1;

    return new_node;
}

/**
 * Insert new node in an AVL
 * @param avl_node AVL root
 * @param key key to insert
 * @param data value to insert
 * @return AVL with new node
 */
struct avl_node* avl_insert(struct avl_node *node, int key, char *data) {
    // Return a new avl_node if the tree is empty
    if (node == NULL)
    {
        return avl_create(key, data);
    }

    // Traverse to the right place and insert the node
    if (key < node->key) {
        node->left = avl_insert(node->left, key, data);
    } else if (key > node->key) {
        node->right = avl_insert(node->right, key, data);
    } else { // Equal keys are not allowed in AVL
        return node;
    }

    /* Update height of this node */
    node->height = 1 + max(height(node->left), height(node->right));

    // Get the balance factor of this node
    // to check whether this node became unbalanced
    int balance = getBalance(node);

    // If this node becomes unbalanced, then
    // there are 4 cases

    // Left Left Case
    if (balance > 1 && key < node->left->key)
        return avl_right_rotate(node);

    // Right Right Case
    if (balance < -1 && key > node->right->key)
        return avl_left_rotate(node);

    // Left Right Case
    if (balance > 1 && key > node->left->key)
    {
        node->left =  avl_left_rotate(node->left);
        return avl_right_rotate(node);
    }

    // Right Left Case
    if (balance < -1 && key < node->right->key)
    {
        node->right = avl_right_rotate(node->right);
        return avl_left_rotate(node);
    }

    /* return the (unchanged) avl root */
    return node;
}

/**
 * Search a node with key and, if found, print its value
 * @param avl_node AVL to search for the key
 * @param key key to search
 */
void avl_find(struct avl_node* node, int key) {
    if (node->key == key)
        printf("%s", node->data);
    if (node->key < key) {
        if (node->right != NULL)
            return avl_find(node->right, key);
        else
            printf("\n");
    } else {
        if (node->left != NULL)
            return avl_find(node->left, key);
        else
            printf("\n");
    }
}

/**
 * Remove all nodes from AVL
 * Given an AVL binary tree, remove its nodes in postorder (left, right, root)
 * @param node
 */
void avl_clear(struct avl_node* node) {
    if (node == NULL)
        return;

    // first recur on left subtree
    avl_clear(node->left);

    // then recur on right subtree
    avl_clear(node->right);

    // now deal with the node
    free(node);
    node = NULL;
}

/**
 * Show current AVL with prefix expression (Polish notation)
 * Given an AVL binary tree, print its nodes in preorder (root, left, right)
 * @param avl_node avl to traverse
 */
void avl_show(struct avl_node* node)
{
    if (node == NULL) {
        printf("NULL ");
        return;
    }

    /* first print data of avl_node */
    printf("%d:%s:%d ", node->key, node->data, node->height);

    /* then recur on left sutree */
    avl_show(node->left);

    /* now recur on right subtree */
    avl_show(node->right);
}

/**
 * Execute command with parameters.
 * Available commands:
 *   insert: insert a new node with key and data
 *   find: find a node with key and, if found, return data
 *   clear: remove every node from tree
 *   show: print tree nodes in preorder
 * @param command command to execute
 * @param key key to insert or search
 * @param data data to insert in key
 * @return AVT root after operation
 */
struct avl_node* doCommand(struct avl_node* root, char *command, int key, char *data)  {
    if (strcmp(command, "insert") == 0)
    {
        root = avl_insert(root, key, data);
    }
    else if (strcmp(command, "find") == 0)
    {
        avl_find(root, key);
    }
    else if (strcmp(command, "clear") == 0)
    {
        avl_clear(root);
        root = NULL;
    }
    else if (strcmp(command, "show") == 0)
    {
        avl_show(root);
        printf("\n");
    }
    else if (strcmp(command, "exit") == 0)
    {
        exit(0);
    }
        /* more else if clauses */
    else /* default: */
    {
        printf("Error! operator is not correct");
        exit(0);
    }
    return root;
}

int main ()
{
    struct avl_node* root = NULL;
    int key = 0;
    char command[MAX_CMD_LENGTH];
    char data[MAX_CMD_LENGTH];

    while ((strcmp(command, "exit") != 0))
    {
        scanLine(command, &key, data); // read command, key and data from stdin
        // execute command
        root = doCommand(root, (char *) &command, key, (char *) &data);
    }
    return 0;
}
