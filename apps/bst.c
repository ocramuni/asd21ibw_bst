//
// Binary Search Tree
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
 * node in a binary search tree
 */
typedef struct bst_node
{
    int key;
    char *data;
    struct bst_node *left;
    struct bst_node *right;
} bst_node;

/**
 * Create a new BST node
 * @param key node key
 * @param data node value
 * @return new BST node
 */
struct bst_node* bst_create(int key, char *data)
{
    struct bst_node *new_node;
    new_node = (struct bst_node *) malloc(sizeof(bst_node));
    if (new_node == NULL)
    {
        fprintf (stderr, "create bst node fail\n");
        exit(1);
    }
    new_node->key = key;
    new_node->data = strdup(data);
    new_node->left = NULL;
    new_node->right = NULL;

    return new_node;
}

/**
 * Insert new node in a BST
 * @param node root BST
 * @param key key to insert
 * @param data value to insert
 * @return BST with new node
 */
struct bst_node* bst_insert(struct bst_node *node, int key, char *data) {
    // Return a new node if the tree is empty
    if (node == NULL)
    {
        return bst_create(key, data);
    }

    // Traverse to the right place and insert the node
    if (key < node->key) {
        node->left = bst_insert(node->left, key, data);
    } else {
        node->right = bst_insert(node->right, key, data);
    }
    return node;
}

/**
 * Search a node with key and, if found, print its value
 * @param node BST to search for the key
 * @param key key to search
 */
void bst_find(struct bst_node* node, int key) {
    if (node->key == key)
        printf("%s", node->data);
    if (node->key < key) {
        if (node->right != NULL)
            return bst_find(node->right, key);
        else
            printf("\n");
    } else {
        if (node->left != NULL)
            return bst_find(node->left, key);
        else
            printf("\n");
    }
}

/**
 * Remove all nodes from BST
 * @param node
 */
void bst_clear(struct bst_node* node) {
    if (node == NULL)
        return;

    // first recur on left subtree
    bst_clear(node->left);

    // then recur on right subtree
    bst_clear(node->right);

    // now deal with the node
    free(node);
    node = NULL;
}

/**
 * Show current bst with prefix expression (Polish notation)
 * Given a BST, print its nodes in preorder
 * @param node bst to traverse
 */
void bst_show(struct bst_node* node)
{
    if (node == NULL) {
        printf("NULL ");
        return;
    }

    /* first print data of node */
    printf("%d:%s ", node->key, node->data);

    /* then recur on left subtree */
    bst_show(node->left);

    /* now recur on right subtree */
    bst_show(node->right);
}

/**
 * Execute command with parameters.
 * Available commands:
 *   insert: insert a new node with key and data
 *   find: bst_find a node with key and, if found, return data
 *   bst_clear: remove every node from tree
 *   bst_show: print tree nodes in preorder
 * @param command command to execute
 * @param key key to insert or search
 * @param data data to insert in key
 * @return BST root after operation
 */
struct bst_node* doCommand(struct bst_node* root, char *command, int key, char *data)  {
    if (strcmp(command, "insert") == 0)
    {
        root = bst_insert(root, key, data);
    }
    else if (strcmp(command, "find") == 0)
    {
        bst_find(root, key);
    }
    else if (strcmp(command, "clear") == 0)
    {
        bst_clear(root);
        root = NULL;
    }
    else if (strcmp(command, "show") == 0)
    {
        bst_show(root);
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
    struct bst_node* root = NULL;
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
