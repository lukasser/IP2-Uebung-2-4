#include <iostream>
using namespace std;

struct node {
    int data;
    node *link[2];
};

struct tree {
    node *root;
};

int find_r(node*, int);
int find(tree*, int);

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
