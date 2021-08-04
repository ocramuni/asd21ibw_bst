#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

#define MIN_N_LENGTH           1000          // minimum number of operations
#define MAX_N_LENGTH           1000000       // maximum number of operations
#define CHART_DATA_POINTS      100           // number of points to plot on chart
#define ERROR_MAX              0.01          // maximum relative error
#define MAXSIZE 100000
#define MAX_CMD_LENGTH 15   // maximum length of a command name

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



void bst_search_and_insert(int n) {
    struct bst_node* root = NULL;
    //int key = 0;
    //char data[5];
    char result;
    int hit = 0;
    int miss = 0;

    for (int i; i < n; i++) {
        // In the GNU C Library the largest value the rand function can return is 2147483647.
        int randomNumber;
        randomNumber = rand();
        if (root != NULL)
            result = bst_find(root, randomNumber);
        if ((strcmp(&result, "data") != 0)) {
            miss++;
            root = bst_insert(root, randomNumber, "data");
        } else {
            hit++;
        }
    }
    //printf("hit: %d / miss: %d\n", hit, miss);
    //bst_show(root);
    bst_clear(root);
    root = NULL;
}

void avl_search_and_insert(int n) {
    struct avl_node* root = NULL;
    //int key = 0;
    //char data[5];
    char result;
    int hit = 0;
    int miss = 0;

    for (int i; i < n; i++) {
        // In the GNU C Library the largest value the rand function can return is 2147483647.
        int randomNumber;
        randomNumber = rand();
        if (root != NULL)
            result = avl_find(root, randomNumber);
        if ((strcmp(&result, "data") != 0)) {
            miss++;
            root = avl_insert(root, randomNumber, "data");
        } else {
            hit++;
        }
    }
    //printf("hit: %d / miss: %d\n", hit, miss);
    //bst_show(root);
    avl_clear(root);
    root = NULL;
}

void rbt_search_and_insert(int n);

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

/**
 * Search and insert "n" node in a binary tree of type "type"
 * @param n string length
 * @param record data_point record
 * @param type which binary tree to use (0 - bst, 1 - avl, 2 - rbt)
 */
void get_search_and_insert_time(int n, struct Records *record, int type) {
    clock_t start, end, w_start;

    start = clock();
    // Do the work.
    double samples[MAXSIZE];
    double samples_sum = 0;
    ssize_t k = 0;
    do {
        // Reset start time on every loop
        w_start = clock();
        switch(type)
        {
            case 0:
                bst_search_and_insert(n);
                break;
            case 1:
                avl_search_and_insert(n);
                break;
            case 2:
                //rbt_search_and_insert(n);
                break;
            default:
                printf("Error! type is not correct");
        }
        end = clock();
        // Save amortized time
        //samples[k] = ((double)(end - w_start) / (double) n);
        samples[k] = (double)(end - w_start) / CLOCKS_PER_SEC;
        //printf("%ld - %ld = %f\n", end, w_start, samples[k]);
        samples_sum += samples[k]; // useful to calculate mean
        k++;

    } while ((double)(end - start) < ((double) resolution / ERROR_MAX + (double) resolution));

    // Average time
    double mean;
    mean = (double) samples_sum / (double) (k);
    //printf("sum: %f | mean: %f\n", samples_sum, mean);
    // Standard deviation
    double sd;
    for (int i = 0; i < k; ++i) {
        sd += pow(samples[i] - mean, 2);
    }
    sd = sqrt(sd / k);
    //printf("sd: %f\n", sd);
    switch(type)
    {
        case 0:
            record->t1 = (mean);
            record->d1 = sd;
            break;
        case 1:
            record->t2 = (mean);
            record->d2 = sd;
            break;
        case 2:
            record->t3 = (mean / CLOCKS_PER_SEC);
            record->d3 = sd;
            break;
        default:
            printf("Error! type is not correct");
    }
}

int main (void) {
    /* Initializes random number generator */
    time_t t;
    srand((unsigned) time(&t));

    /* Initialize global variables */

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
        /* Search longest period on string of length n with smart algo */
        get_search_and_insert_time(iterations, &data_points[i], 0);
        //get_period_time(length, &data_points[i], 1);
        get_search_and_insert_time(iterations, &data_points[i], 1);
        /* Search longest period on string of length n with naive algo */
        //get_search_and_insert_time(iterations, &data_points[i], 2);
        /* string length,time min smart,time average smart,time max smart,time min naive,time average naive,time max naive */
        printf("%d %f %f %f %f %f %f\n",
               data_points[i].n,
               data_points[i].t1,
               data_points[i].d1,
               data_points[i].t2,
               data_points[i].d2,
               data_points[i].t3,
               data_points[i].d3);

        }

    return 0;
}
