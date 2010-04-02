#include <iostream>
using namespace std;

/* The structs for the tree */
struct node {
    int data;       /* data to store */
    node *link[2];  /*  left(0)/right(1) links */
};

struct tree {
    node *root;
};


/* Search Functions */
int find_nr(tree*, int);   /* non-recursive search */
int find_r(node*, int);    /* recursive search */
int find(tree*, int);      /* conveneince wrapper for find_r */

/* Insertion Functions */
node* insert_r(node*, int);  /* recursive insertion */ 

/* Auxillary Functions */
node* make_node(int);      /* create a node with data */

int
main() {
    return 0;
}


/* find_r: Recursive search
 *
 * Args: pointer to root, data to search for
 * Returns: 1 if found, 0 if not found
 *
 */
int
find_r(node *root, int data) {
    if (root == NULL) {
        return 0; // not found
    } else if (root->data == data) {
        return 1; // found
    } else {
        int dir = root->data < data; // which subtree to follow?
        return find_r(root->link[dir], data);
    }
}

/* find: Convenience wrapper for find_r
 */
int
find(tree *tree, int data) {
    return find_r(tree->root, data);
}

/* find_nr: Non-recursive search
 *
 * Args: pointer to tree, data to search for
 * Returns: 0 if not found, 1 if found
 */
int
find_nr(tree *tree, int data) {
    node *it = tree->root;

    while (it != NULL) {
        if (it->data == data)
            return 1;   // found
        else {
            int dir = it->data < data; // which direction?
            it = it->link[dir];
        }
    }

    return 0; // not found
}


/* insert_r: Recursive insertion
 *
 * Args: root pointer, data to store
 * Returns: pointer to root
 *
 */
node*
insert_r(node *root, int data) {
    if (root == NULL)
        root = make_node(data);
    else if (root->data == data)
        return root;
    else {
        int dir = root->data < data;
        root->link[dir] = insert_r(root->link[dir], data);
    }

    return root;
}

/* insert: Conveneince wrapper for insert_r
 *
 * Returns: 1 if successful
 */
int
insert(tree *tree, int data) {
    tree->root = insert_r(tree->root, data);
    return 1;
}

/* insert_nr: Non-recursive insertion
 *
 * Args: pointer to tree, data to insert
 * Returns: 1 if successful, 0 if not
 *
 */
int
insert_nr(tree *tree, int data) {
    if (tree->root == NULL) // empty tree 
        tree->root = make_node(data);
    else {
        node *it = tree->root; // help pointer 
        int dir;

        for (;;) {
            dir = it->data < data; // which direction?

            if (it->data == data) // already in tree
                return 0;
            else if (it->link[dir] == NULL) // we've reached a leaf, don't continue
                break;

            it = it->link[dir]; // link to the node we want to insert the data
        }

        it->link[dir] = make_node(data);
    }

    return 1; // successfully inserted data
}

/* make_node: Create a node
 *
 * Args: data 
 * Returns: pointer to new node
 */
node*
make_node(int data) {
    node *it = new node;

    it->data = data;
    it->link[0] = NULL;
    it->link[1] = NULL;

    return it;
}
