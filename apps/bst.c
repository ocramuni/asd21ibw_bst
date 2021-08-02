//
// Created by Marco Giunta on 27/07/2021.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_SIZE 1000   // maximum size of a line of input
#define MAX_CMD_LENGTH 15   // maximum length of a command name

/**
 * Extract command and parameter from command line.
 * @param a parameters array.
 * @param command command to execute.
 * @return size of a.
 */
int scanLine(char *cmd, int* key, char *data) {
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

    int size = 0, offset = 0, numFilled, n;

    char tmp_data[MAX_LINE_SIZE];
    strcpy(tmp_data, "");
    // A null pointer is returned if there are no tokens left to retrieve.
    if  (param != NULL) {
        size = sscanf(param, "%d%s", key, tmp_data);
        //printf("%d", *key);
        if ((strcmp(tmp_data, "") == 0)) {
            strcpy(data, "");
        } else {
            //printf("'%s'", tmp_data);
            strcpy(data, tmp_data);
        }
    } else {
        strcpy(data, "");
        *key = 0;
    }

    return size;
}


/**
 * Node structure
 */
typedef struct node
{
    int key;
    char *data;
    struct node *left;
    struct node *right;
} node;

/**
 * Create a new node
 * @param key node key
 * @param data node value
 * @return new node
 */
struct node* create(int key, char *data)
{
    struct node *new_node;
    new_node = (struct node *) malloc(sizeof(node));
    if (new_node == NULL)
    {
        fprintf (stderr, "create node fail\n");
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
struct node* insert(struct node *node, int key, char *data) {
    // Return a new node if the tree is empty
    if (node == NULL)
    {
        return create(key, data);
    }

    // Traverse to the right place and insert the node
    if (key < node->key) {
        node->left = insert(node->left, key, data);
    } else {
        node->right = insert(node->right, key, data);
    }
    return node;
}

/**
 * Search a node with key and, if found, print its value
 * @param node BST to search for the key
 * @param key key to search
 */
void find(struct node* node, int key) {
    if (node->key == key)
        printf("%s", node->data);
    if (node->key < key) {
        if (node->right != NULL)
            return find(node->right, key);
        else
            printf("\n");
    } else {
        if (node->left != NULL)
            return find(node->left, key);
        else
            printf("\n");
    }
}

/**
 * Return the node with minimum key value found in that tree.
 * @param node node to traverse to find the minimum key
 * @return node with minimum key
 */
struct node* minKey(struct node* node)
{
    struct node* current = node;

    // loop down to find the leftmost leaf
    while (current && current->left != NULL)
        current = current->left;

    return current;
}

/**
 * Delete key from BST and return the new root
 * @param root bst
 * @param key key to delete
 * @return new bst without key
 */
struct node* delete(struct node* root, int key)
{
    // base case
    if (root == NULL)
        return root;

    // If the key to be deleted
    // is smaller than the root's
    // key, then it lies in left subtree
    if (key < root->key)
        root->left = delete(root->left, key);

    // If the key to be deleted
    // is greater than the root's
    // key, then it lies in right subtree
    else if (key > root->key)
        root->right = delete(root->right, key);

    // if key is same as root's key,
    // then This is the node
    // to be deleted
    else {
        // node with only one child or no child
        if (root->left == NULL) {
            struct node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            struct node* temp = root->left;
            free(root);
            return temp;
        }

        // node with two children:
        // Get the inorder successor
        // (smallest in the right subtree)
        struct node* temp = minKey(root->right);
        // Copy the inorder
        // successor's content to this node
        root->key = temp->key;
        root->data = temp->data;

        // Delete the inorder successor
        root->right = delete(root->right, temp->key);
    }
    return root;
}

/**
 * Remove all nodes from BST
 * @param node
 */
void clear(struct node* node) {
    memset(&node, 0, sizeof(node));
    //free(node);
}

// Inorder Traversal
void inorder(struct node *root) {
    if (root != NULL) {
        // Traverse left
        inorder(root->left);

        // Traverse root
        printf("%s -> ", root->data);

        // Traverse right
        inorder(root->right);
    }
}

/**
 * Show current bst with prefix expression (Polish notation)
 * Given a binary tree, print its nodes in preorder
 * @param node bst to traverse
 */
void show(struct node* node)
{
    if (node == NULL) {
        printf("NULL ");
        return;
    }

    /* first print data of node */
    printf("%d:%s ", node->key, node->data);

    /* then recur on left sutree */
    show(node->left);

    /* now recur on right subtree */
    show(node->right);
}

/**
 * Execute command with parameters
 * build: inizializzazione della heap tramite sequenza di elementi interi (non necessariamente ordinati)
 * length: restituzione del numero di elementi nella heap
 * getmin: restituzione del valore del nodo radice
 * extract: rimozione del nodo radice
 * insert: inserimento di un nuovo nodo con valore intero x
 * change: assegnazione di un nuovo valore x al nodo con indice i
 * @param command command to execute
 * @param a init array values
 * @param n init array length
 * @param heap heap
 */
struct node* doCommand(struct node* root, char *command, int key, char *data)  {
    if (strcmp(command, "insert") == 0)
    {
        root = insert(root, key, data);
    }
    else if (strcmp(command, "remove") == 0)
    {
        root = delete(root, key);
    }
    else if (strcmp(command, "find") == 0)
    {
        find(root, key);
    }
    else if (strcmp(command, "clear") == 0)
    {
        //memset(root, NULL, sizeof(node));
        //clear(root);
        free(root);
    }
    else if (strcmp(command, "show") == 0)
    {
        show(root);
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
    struct node* root = NULL;
    int key = 0;
    char command[MAX_CMD_LENGTH];
    char data[MAX_CMD_LENGTH];
    int n;
    // minHeap array
    int heap[MAX_LINE_SIZE];

    while ((strcmp(command, "exit") != 0))
    {
        printf("%p", root);
        n = scanLine(command, &key, data); // carica in key  la chiave e in data il valore
        // execute command
        root = doCommand(root, (char *) &command, key, (char *) &data);
    }

    return 0;
}
