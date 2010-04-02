#include <iostream>
#include "binary_tree.h"

using namespace std;

/*  SEARCH  */
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


/*  INSERTION  */
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
    // else if (root->data == data)  // accept dups
    //    return root;
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
            
            if (it->link[dir] == NULL) // we've reached a leaf
                break;
            /* 
            if (it->data == data) // already in tree, won't insert duplicates
                return 0;
            else if (it->link[dir] == NULL) // we've reached a leaf, don't continue
                break;
            */

            it = it->link[dir]; // link to the node we want to insert the data
        }

        it->link[dir] = make_node(data);
    }

    return 1; // successfully inserted data
}


/*  REMOVAL  */
/* remove: Delete a node from the tree
 *
 * Args: tree pointer, data to delete
 * Returns: 1 if successful, 0 if not
 *
 */
int
remove(tree *tree, int data) {
    if (tree->root != NULL) { //non-empty tree
        node head = {0};   // dummy root
        node *it = &head;   // current position
        node *p, *f = NULL; // parent node, help pointer if found
        int dir = 1;  // traverse to the right

        it->link[1] = tree->root;

        while (it->link[dir] != NULL) { // traverse to the bottom
            p = it;  // save parent node
            it = it->link[dir]; // proceed the current pointer
            dir = it->data <= data; // which direction?

            if (it->data == data)
                f = it;  // found it
        }

        if (f != NULL) { // if we found the node to delete
            f->data = it->data; // copy 
            p->link[p->link[1] == it] = it->link[it->link[0] == NULL]; // :)
            delete it;
        }

        tree->root = head.link[1];
    }

    return 1;
}

/* destroy_r: Recurse delete entire tree
 *
 * Args: pointer to root
 * Returns: nothing
 */
void
destroy_r(node *root) {
    if (root != NULL) {
        destroy_r(root->link[0]);
        destroy_r(root->link[1]);
        delete root;
    }
}

void
destroy(tree *tree) {
    destroy_r(tree->root);
}

void
destroy_nr(tree *tree) {
    node *it = tree->root;
    node *save;

    while (it != NULL) {
        if (it->link[0] != NULL) {
            // right rotation
            save = it->link[0];
            it->link[0] = save->link[1];
            save->link[1] = it;
        } else {
            save = it->link[1];
            delete it;
        }
        
        it = save;
    }
}

/* TRAVERSAL */
// Preorder
void
preorder_r(node *root) {
    if (root != NULL) {
        cout << "MW: " << root->data << endl;
        preorder_r(root->link[0]);
        preorder_r(root->link[1]);
    }
}

void
preorder(tree *tree) {
    preorder_r(tree->root);
}

// Inorder
void
inorder_r(node *root) {
    if (root != NULL) {
        inorder_r(root->link[0]);
        cout << "MW: " << root->data << endl;
        inorder_r(root->link[1]);
    }
}

void
inorder(tree *tree) {
    inorder_r(tree->root);
}


// Postorder
void
postorder_r(node *root) {
    if (root != NULL) {
        postorder_r(root->link[0]);
        postorder_r(root->link[1]);
        cout << "MW: " << root->data << endl;
    }
}

void
postorder(tree *tree) {
    postorder_r(tree->root);
}

/* print_tree: Print the tree 90degree cc
 *
 * Args: pointer to root, depth to print
 */
void
print_tree(node *root, int level) {
    int i;

    if (root == NULL) {
        for (i=0; i<level; i++)
            cout << "\t";
        cout << "~\n";
    } else {
        print_tree(root->link[1], level++);

        for (i=0; i<level; i++)
            cout << "\t";
        cout << root->data;

        print_tree(root->link[0], level++);
    }
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
