//
// Created by Marco Giunta on 01/08/2021.
//
#include<stdio.h>
#include<stdlib.h>
#include <string.h>

#define MAX_LINE_SIZE 1000   // maximum size of a line of input
#define MAX_CMD_LENGTH 15   // maximum length of a command name

enum nodeColor {
    BLACK,
    RED
};

/**
 * // Structure to represent each
// node in a red-black tree
 * Node structure
 */
typedef struct node
{
    int key;
    char *data;
    enum nodeColor color;
    struct node *parent;
    struct node *left;
    struct node *right;
} node;

// Based on CLRS algorithm, use T_Nil as a sentinel to simplify code
struct node  T_Nil_Node;
node* T_Nil = &T_Nil_Node;

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

    int size = 0;

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
 * Creates a new node, initializes and returns a pointer to it.
 * @param key node key
 * @param data node value
 * @return node
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
    new_node->color = RED;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->parent = NULL;

    return new_node;
}

struct node* rotateLeft(node* T, node* x)
{
    node *y  = x->right;    // set y
    x->right = y->left;     // turn y's left subtree into x's right subtree{
    if (y->left != T_Nil)
        y->left->parent = x;
    y->parent = x->parent;  // link x's parent to y
    if (x->parent == T_Nil)
        T = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left   = x;            // put x on y's left
    x->parent = y;
    return T;
}

struct node* rotateRight(node* T, node* y)
{
    node *x  = y->left;     // set x
    y->left  = x->right;    // turn x's right subtree into y's left subtree{
    if (x->right != T_Nil)
        x->right->parent = y;
    x->parent = y->parent;  // link y's parent to x
    if (y->parent == T_Nil)
        T = x;
    else if (y == y->parent->right)
        y->parent->right = x;
    else
        y->parent->left  = x;
    x->right  = y;         // put y on x's right
    y->parent = x;
    return T;
}

struct node* fixup(node* Root, node* New)
{
    node* temp;
    while (New->parent->color == RED)
    {
        if (New->parent == New->parent->parent->left)
        {
            temp = New->parent->parent->right;
            if (temp->color == RED)
            {
                New->parent->color = BLACK;
                temp->color = BLACK;
                New->parent->parent->color = RED;
                New = New->parent->parent;
            }
            else {
                if (New == New->parent->right)
                {
                    New = New->parent;
                    Root = rotateLeft(Root, New);
                }
                New->parent->color = BLACK;
                New->parent->parent->color = RED;
                Root = rotateRight(Root, New->parent->parent);
            }
        }
        else
        {
            temp = New->parent->parent->left;
            if (temp->color == RED)
            {
                New->parent->color = BLACK;
                temp->color = BLACK;
                New->parent->parent->color = RED;
                New = New->parent->parent;
            }
            else {
                if (New == New->parent->left)
                {
                    New = New->parent;
                    Root = rotateRight(Root, New);
                }
                New->parent->color = BLACK;
                New->parent->parent->color = RED;
                Root = rotateLeft(Root, New->parent->parent);
            }
        }
    }
    Root->color = BLACK;
    return Root;
}

/**
 * Insert new node in a BST
 * @param node root BST
 * @param key key to insert
 * @param data value to insert
 */
struct node* insert(node* T, int key, char* data)
{
    node* z =  create(key, data);
    node* y =  T_Nil;
    node* x = T;

    // Find where to Insert new node Z into the binary search tree
    while (x != T_Nil) {
        y = x;
        if (z->key < x->key)
            x = x->left;
        else
            x = x->right;
    }

    z->parent = y;
    if (y == T_Nil)
        T = z;
    else if (z->key < y->key)
        y->left  = z;
    else
        y->right = z;

    // Init z as a red leaf
    z->left  = T_Nil;
    z->right = T_Nil;
    z->color = RED;

    // Ensure the Red-Black property is maintained
    T = fixup(T, z);
    return T;
}

/**
 * Search a node with key and, if found, print its value
 * @param node BST to search for the key
 * @param key key to search
 */
void find(struct node* node, int key) {
    if (node->key == key) {
        printf("%s", node->data);
        printf("\n");

    } else if (node->key < key) {
        if (node->right != NULL)
            return find(node->right, key);
        /*else
            printf("\n");*/
    } else {
        if (node->left != NULL)
            return find(node->left, key);
        /*else
            printf("\n");*/
    }
    //printf("\n");
}

/**
 * Remove all nodes from BST
 * @param node
 */
void clear(struct node* node) {
    if (node == NULL || node == T_Nil)
        return;

    // first recur on left subtree
    clear(node->left);

    // then recur on right subtree
    clear(node->right);

    // now deal with the node
    free(node);
    node = NULL;
}

/**
 * Show current bst with prefix expression (Polish notation)
 * Given a binary tree, print its nodes in preorder
 * @param node bst to traverse
 */
void show(struct node* node)
{
    if (node == T_Nil) {
        printf("NULL ");
        return;
    }

    char color[6];
    if (node->color == BLACK) {
        strcpy(color, "black");
    } else {
        strcpy(color, "red");
    }
    /* first print data of node */
    printf("%d:%s:%s ", node->key, node->data, color);

    /* then recur on left subtree */
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
        //node *new_node = create(key, data);
        root = insert(root, key, data);

        // fix Red Black Tree violations
        //fixup(root, new_node);
    }
    else if (strcmp(command, "find") == 0)
    {
        find(root, key);
    }
    else if (strcmp(command, "clear") == 0)
    {
        clear(root);
        root = T_Nil;
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
    struct node* root = T_Nil;
    int key = 0;
    char command[MAX_CMD_LENGTH];
    char data[MAX_CMD_LENGTH];
    int n;

    while ((strcmp(command, "exit") != 0))
    {
        //printf("%p", root);
        n = scanLine(command, &key, data); // carica in key  la chiave e in data il valore
        // execute command
        root = doCommand(root, (char *) &command, key, (char *) &data);
    }

    return 0;
}

