//
// Red-Black Tree
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
 * Enum to represent each
 * node color in a red-black tree
 */
enum nodeColor {
    BLACK,
    RED
};

/**
 * Structure to represent each
 * node in a red-black tree
 */
typedef struct rbt_node
{
    int key;
    char *data;
    enum nodeColor color;
    struct rbt_node *parent;
    struct rbt_node *left;
    struct rbt_node *right;
} rbt_node;


// Use T_Nil as a sentinel to simplify code
struct rbt_node *T_Nil;

/**
 * Creates a new node, initializes and returns a pointer to it.
 * @param key node key
 * @param data node value
 * @return rbt node
 */
struct rbt_node* rbt_create(int key, char *data)
{
    struct rbt_node *new_node;
    new_node = (struct rbt_node *) malloc(sizeof(rbt_node));
    if (new_node == NULL)
    {
        fprintf (stderr, "create rbt node fail\n");
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

/**
 * Left rotate RBT subtree rooted with x
 * @param root rbt_node RBT root
 * @param x rbt_node node to rotate
 * @return rotated RBT
 */
struct rbt_node* rbt_left_rotate(rbt_node* root, rbt_node* x)
{
    // y stored pointer of right child of x
    rbt_node *y = x->right;
    // store y's left subtree's pointer as x's right child
    x->right = y->left;
    // update parent pointer of y's left
    if (y->left != T_Nil)
        y->left->parent = x;
    // link x's parent to y
    y->parent = x->parent;
    // if x's parent is T_Nil make y as root of tree
    if (x->parent == T_Nil)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    // make x as left child of y
    y->left = x;
    // update parent pointer of x
    x->parent = y;

    // Return new root
    return root;
}

/**
 * Right rotate RBT subtree rooted with y
 * @param root rbt_node RBT root
 * @param y rbt_node node to rotate
 * @return rotated RBT
 */
struct rbt_node* rbt_right_rotate(rbt_node* root, rbt_node* y)
{
    // x stored pointer of left child of y
    rbt_node *x = y->left;
    // turn x's right subtree into y's left subtree
    y->left = x->right;
    // update parent pointer of x's right
    if (x->right != T_Nil)
        x->right->parent = y;
    // update x's parent pointer
    x->parent = y->parent;
    // if y's parent is T_Nil make x as root of tree
    if (y->parent == T_Nil)
        root = x;
    else if (y == y->parent->right)
        y->parent->right = x;
    else
        y->parent->left  = x;
    // make y as right child of x
    x->right = y;
    // update parent pointer of y
    y->parent = x;

    // Return new root
    return root;
}

struct rbt_node* fixup(rbt_node* root, rbt_node* node)
{
    rbt_node* temp;
    while (node->parent->color == RED)
    {
        /* Case : A
         * Parent of node is left child
         * of Grand-parent of node
         */
        if (node->parent == node->parent->parent->left)
        {
            temp = node->parent->parent->right;
            /* Case : 1
             *   The uncle of node is also red
             *   Only Recoloring required
             */
            if (temp->color == RED)
            {
                node->parent->color = BLACK;
                temp->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            }
            else {
                /* Case : 2
                 *   node is right child of its parent
                 *   Left-rotation required
                 */
                if (node == node->parent->right)
                {
                    node = node->parent;
                    root = rbt_left_rotate(root, node);
                }
                /* Case : 3
                 *   node is left child of its parent
                 *   Right-rotation required
                 */
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                root = rbt_right_rotate(root, node->parent->parent);
            }
        }
        else
        {
            /* Case : B
             *   Parent of node is right child
             *   of Grand-parent of node
             */
            temp = node->parent->parent->left;
            /* Case : 1
             *   The uncle of node is also red
             *   Only Recoloring required
             */
            if (temp->color == RED)
            {
                node->parent->color = BLACK;
                temp->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            }
            else {
                /* Case : 2
                 *  node is left child of its parent
                 *  Right-rotation required
                 */
                if (node == node->parent->left)
                {
                    node = node->parent;
                    root = rbt_right_rotate(root, node);
                }
                /* Case : 3
                 * node is right child of its parent
                 * Left-rotation required
                 */
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                root = rbt_left_rotate(root, node->parent->parent);
            }
        }
    }
    root->color = BLACK;
    return root;
}

/**
 * Insert new node in a RBT
 * @param node RBT root
 * @param key key to insert
 * @param data value to insert
 */
struct rbt_node* rbt_insert(struct rbt_node *node, int key, char* data)
{
    rbt_node* z = rbt_create(key, data);
    rbt_node* y = T_Nil;
    rbt_node* x = node;

    // Find where to Insert new node Z into the RBT
    while (x != T_Nil) {
        y = x;
        if (z->key < x->key)
            x = x->left;
        else
            x = x->right;
    }

    z->parent = y;
    if (y == T_Nil)
        node = z;
    else if (z->key < y->key)
        y->left  = z;
    else
        y->right = z;

    // Init z as a red leaf
    z->left  = T_Nil;
    z->right = T_Nil;
    z->color = RED;

    // Ensure the Red-Black property is maintained
    node = fixup(node, z);
    return node;
}

/**
 * Search a node with key and, if found, print its value
 * @param node BST to search for the key
 * @param key key to search
 */
void rbt_find(struct rbt_node* node, int key) {
    if (node->key == key) {
        printf("%s", node->data);
        printf("\n");

    } else if (node->key < key) {
        if (node->right != NULL)
            return rbt_find(node->right, key);
    } else {
        if (node->left != NULL)
            return rbt_find(node->left, key);
    }
}

/**
 * Remove all nodes from RBT
 * Given a RBT, remove its nodes in postorder (left, right, root)
 * @param node
 */
void rbt_clear(struct rbt_node* node) {
    if (node == NULL || node == T_Nil)
        return;

    // first recur on left subtree
    rbt_clear(node->left);

    // then recur on right subtree
    rbt_clear(node->right);

    // now deal with the node
    free(node);
    node = NULL;
}

/**
 * Show current rbt with prefix expression (Polish notation)
 * Given a RBT, print its nodes in preorder (root, left, right)
 * @param node rbt to traverse
 */
void rbt_show(struct rbt_node* node)
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
    rbt_show(node->left);

    /* now recur on right subtree */
    rbt_show(node->right);
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
 * @return RBT root after operation
 */
struct rbt_node* doCommand(struct rbt_node* root, char *command, int key, char *data)  {
    if (strcmp(command, "insert") == 0)
    {
        root = rbt_insert(root, key, data);
    }
    else if (strcmp(command, "find") == 0)
    {
        rbt_find(root, key);
    }
    else if (strcmp(command, "clear") == 0)
    {
        rbt_clear(root);
        root = T_Nil;
    }
    else if (strcmp(command, "show") == 0)
    {
        rbt_show(root);
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
    // Initialize T_Nil sentinel
    T_Nil = (struct rbt_node *) malloc(sizeof(rbt_node));
    struct rbt_node* root = T_Nil;
    int key = 0;
    char command[MAX_CMD_LENGTH];
    char data[MAX_CMD_LENGTH];

    while ((strcmp(command, "exit") != 0))
    {
        scanLine(command, &key, data); // read command, key and data from stdin
        // execute command
        root = doCommand(root, (char *) &command, key, (char *) &data);
    }
    free(T_Nil);
    return 0;
}
