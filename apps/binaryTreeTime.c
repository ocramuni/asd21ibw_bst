#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

#define MIN_N_LENGTH           1000          // minimum number of operations
#define MAX_N_LENGTH           1000000       // maximum number of operations
#define CHART_DATA_POINTS      100           // number of points to plot on chart
#define ERROR_MAX              0.01          // maximum relative error
#define MAX_TIMES              10000         // maximum number of iterations
#define MAX_CMD_LENGTH         15            // maximum length of a command name

/* Global variables */
double b;
long resolution;

/* Data point record */
struct Records {
    int n; // numero iterazioni di ricerca
    double t1; //
    double t2; // tempo medio e ammortizzato di ciascuna operazione
    double t3; //
    double d1; //
    double d2; // deviazione standard
    double d3; //
};

/***********************************
 *  BST
 ************************************/

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
char bst_find(struct bst_node* node, int key) {
    if (node->key == key)
        return *node->data;
    if (node->key < key) {
        if (node->right != NULL)
            return bst_find(node->right, key);
    } else {
        if (node->left != NULL)
            return bst_find(node->left, key);
    }
    return *strdup("");
}

/**
 * Remove all nodes from BST
 * Given a BST, remove its nodes in postorder (left, right, root)
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
 * Given a BST, print its nodes in preorder (root, left, right)
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
 * Search and insert n keys in an Binary Search Tree
 * @param n number of keys to search and insert
 * @return BST root node
 */
struct bst_node* bst_search_and_insert(int n) {
    struct bst_node* root = NULL;
    char result;
    int hit = 0;
    int miss = 0;

    for (int i; i < n; i++) {
        // In the GNU C Library the largest value the rand function can return is 2147483647.
        int randomNumber;
        randomNumber = rand();
        if (root != NULL)
            result = bst_find(root, randomNumber);
        if ((strcmp(&result, "d") != 0)) {
            miss++;
            root = bst_insert(root, randomNumber, "d");
        } else {
            hit++;
        }
    }
    //printf("hit: %d / miss: %d\n", hit, miss);
    return root;
}

/**
 * Get time of "n" search-and-insert operation in a Binary Search Tree
 * @param n number of keys to search and insert
 * @param record data_point record
 */
void bst_search_and_insert_time(int n, struct Records *record) {
    clock_t start, end, w_start;

    struct bst_node* pt_clear_nodes[MAX_TIMES];
    start = clock();
    // Do the work.
    double times[MAX_TIMES];
    double times_sum = 0;
    ssize_t k = 0;
    do {
        // Reset start time on every loop
        w_start = clock();
        pt_clear_nodes[k] = bst_search_and_insert(n);
        end = clock();
        // Save amortized time
        times[k] = (double)(end - w_start) / CLOCKS_PER_SEC / (double) n;
        times_sum += times[k]; // useful to calculate mean
        k++;

    } while ((double)(end - start) < ((double) resolution / ERROR_MAX + (double) resolution));

    for(int j = 0; j < k; j++){
        bst_clear(pt_clear_nodes[j]);
        pt_clear_nodes[j] = NULL;
    }
    // Average time
    double mean;
    mean = (double) times_sum / (double) (k);
    // Standard deviation
    double sd;
    for (int i = 0; i < k; ++i) {
        sd += pow(times[i] - mean, 2);
    }
    sd = sqrt(sd / k);
    record->t1 = mean;
    record->d1 = sd;
}


/***********************************
 *  AVL
 ************************************/

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
int max(int aa, int bb)
{
    return (aa > bb)? aa : bb;
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
char avl_find(struct avl_node* node, int key) {
    if (node->key == key)
        return *node->data;
    if (node->key < key) {
        if (node->right != NULL)
            return avl_find(node->right, key);
    } else {
        if (node->left != NULL)
            return avl_find(node->left, key);
    }
    return *strdup("");
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
 * Search and insert n keys in an AVL Binary Tree
 * @param n number of keys to search and insert
 * @return AVL root node
 */
struct avl_node* avl_search_and_insert(int n) {
    struct avl_node* root = NULL;
    char result;
    int hit = 0;
    int miss = 0;

    for (int i; i < n; i++) {
        // In the GNU C Library the largest value the rand function can return is 2147483647.
        int randomNumber;
        randomNumber = rand();
        if (root != NULL)
            result = avl_find(root, randomNumber);
        if ((strcmp(&result, "d") != 0)) {
            miss++;
            root = avl_insert(root, randomNumber, "d");
        } else {
            hit++;
        }
    }
    //printf("hit: %d / miss: %d\n", hit, miss);
    return root;
}

/**
 * Get time of "n" search-and-insert operations in an AVL Tree
 * @param n number of keys to search and insert
 * @param record data_point record
 */
void avl_search_and_insert_time(int n, struct Records *record) {
    clock_t start, end, w_start;

    struct avl_node* pt_clear_nodes[MAX_TIMES];
    start = clock();
    // Do the work.
    double times[MAX_TIMES];
    double times_sum = 0;
    ssize_t k = 0;
    do {
        // Reset start time on every loop
        w_start = clock();
        pt_clear_nodes[k] = avl_search_and_insert(n);
        end = clock();
        // Save amortized time
        times[k] = (double)(end - w_start) / CLOCKS_PER_SEC / (double) n;
        times_sum += times[k]; // useful to calculate mean
        k++;

    } while ((double)(end - start) < ((double) resolution / ERROR_MAX + (double) resolution));

    for(int j = 0; j < k; j++){
        avl_clear(pt_clear_nodes[j]);
        pt_clear_nodes[j] = NULL;
    }
    // Average time
    double mean;
    mean = (double) times_sum / (double) (k);
    // Standard deviation
    double sd;
    for (int i = 0; i < k; ++i) {
        sd += pow(times[i] - mean, 2);
    }
    sd = sqrt(sd / k);
    record->t2 = mean;
    record->d2 = sd;
}


/***********************************
 *  RBT
 ************************************/

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

/**
 * Resort the Red-Black tree properties
 * @param root RBT root
 * @param node node to fixup
 * @return RBT root node
 */
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
char rbt_find(struct rbt_node* node, int key) {
    if (node->key == key) {
        return *node->data;
    } else if (node->key < key) {
        if (node->right != T_Nil)
            return rbt_find(node->right, key);
    } else {
        if (node->left != T_Nil)
            return rbt_find(node->left, key);
    }
    return *strdup("");
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
    node = T_Nil;
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
 * Search and insert n keys in a Red-Black Tree
 * @param n number of keys to search and insert
 * @return RBT root node
 */
struct rbt_node* rbt_search_and_insert(int n) {
    struct rbt_node* root = T_Nil;

    char result;
    int hit = 0;
    int miss = 0;

    for (int i; i < n; i++) {
        // In the GNU C Library the largest value the rand function can return is 2147483647.
        int randomNumber;
        randomNumber = rand();
        if (root != T_Nil)
            result = rbt_find(root, randomNumber);
        if ((strcmp(&result, "d") != 0)) {
            miss++;
            root = rbt_insert(root, randomNumber, "d");
        } else {
            hit++;
        }
    }
    //printf("hit: %d / miss: %d\n", hit, miss);
    return root;
}

/**
 * Get time of "n" search-and-insert operations in a Red-Black Tree
 * @param n number of keys to search and insert
 * @param record data_point record
 */
void rbt_search_and_insert_time(int n, struct Records *record) {
    clock_t start, end, w_start;

    struct rbt_node* pt_clear_nodes[MAX_TIMES];
    start = clock();
    // Do the work.
    double times[MAX_TIMES];
    double times_sum = 0;
    ssize_t k = 0;
    do {
        // Reset start time on every loop
        w_start = clock();
        pt_clear_nodes[k] = rbt_search_and_insert(n);
        end = clock();
        // Save amortized time
        times[k] = (double)(end - w_start) / CLOCKS_PER_SEC / (double) n;
        times_sum += times[k]; // useful to calculate mean
        k++;

    } while ((double)(end - start) < ((double) resolution / ERROR_MAX + (double) resolution));

    for(int j = 0; j < k; j++){
        rbt_clear(pt_clear_nodes[j]);
        pt_clear_nodes[j] = T_Nil;
    }
    // Average time
    double mean;
    mean = (double) times_sum / (double) (k);
    // Standard deviation
    double sd;
    for (int i = 0; i < k; ++i) {
        sd += pow(times[i] - mean, 2);
    }
    sd = sqrt(sd / k);
    record->t3 = mean;
    record->d3 = sd;
}


/*************************
 *
 *  Utilities
 *
 *************************/

/**
 * Get system clock resolution
 * @return clock resolution in nano seconds
 */
long getResolution() {
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    do {
        clock_gettime(CLOCK_MONOTONIC, &end);
    } while(start.tv_nsec == end.tv_nsec);
    return (end.tv_nsec - start.tv_nsec);
}

/**
 * Get number of iterations from data point number (Nj=ab^j)
 * @param dp number for data point
 * @return string length
 */
int get_iterations_number(ssize_t dp) {
    int length;
    length = MIN_N_LENGTH * (pow (b, (double) dp));
    return length;
}


int main (void) {
    /* Initializes random number generator */
    time_t t;
    srand((unsigned) time(&t));

    /* Initialize global variables */
    T_Nil = (struct rbt_node *) malloc(sizeof(rbt_node));

    /* Get b parameter needed to calculate number of iterations based on position on x-axis */
    b = (double) exp(((double) log(MAX_N_LENGTH) - (double) log(MIN_N_LENGTH)) / (CHART_DATA_POINTS - 1));

    /* Get CPU clock resolution */
    resolution = getResolution();

    struct Records data_points[CHART_DATA_POINTS];

    /* Do the work. */
    for (ssize_t i = 0; i < CHART_DATA_POINTS; i++) {
        /* Get string length */
        int iterations;
        iterations = get_iterations_number(i);
        data_points[i].n = iterations;
        // Get time of search-and-insert in a BST
        bst_search_and_insert_time(iterations, &data_points[i]);
        // Get time of search-and-insert in an AVL Tree
        avl_search_and_insert_time(iterations, &data_points[i]);
        // Get time of search-and-insert in a Red-Black Tree
        rbt_search_and_insert_time(iterations, &data_points[i]);
        // n iterations,time BST, S.D, BST, time AVL, SD AVL, time RBT, S.D. RBT
        printf("%d %.15f %.15f %.15f %.15f %.15f %.15f\n",
               data_points[i].n,
               data_points[i].t1,
               data_points[i].d1,
               data_points[i].t2,
               data_points[i].d2,
               data_points[i].t3,
               data_points[i].d3);

        }
    free(T_Nil);
    return 0;
}
