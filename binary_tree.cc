/* Implementaion of several binary search tree (BST) functions.
 *
 * See COPYING for copyright information
 * inspired by http://eternallyconfuzzled.com/tuts/datastructures 
 */

#include <iostream>
#include "binary_tree.h"
using namespace std;

/*  SEARCH  */
// NOTE: only returns first found element.
/* find_r: Recursive search
 *
 * Args: pointer to root, data to search for
 * Returns: NULL pointer if not found, pointer to node if found
 *
 */
node*
find_r(node *root, double data)
{
    if (root == NULL) {
        return NULL; // not found
    } else if (root->data == data) {
        return root; // found
    } else {
        int dir = root->data < data; // which subtree to follow?
        return find_r(root->link[dir], data);
    }
}

/* find: Convenience wrapper for find_r
 */
node*
find(tree *tree, double data)
{
    return find_r(tree->root, data);
}

/* find_nr: Non-recursive search
 *
 * Args: pointer to tree, data to search for
 * Returns: NULL pointer if not found, pointer to node if found
 */
node*
find_nr(tree *tree, double data)
{
    node *it = tree->root;

    while (it != NULL) {
        if (it->data == data)
            return it;   // found
        else {
            int dir = it->data < data; // which direction?
            it = it->link[dir];
        }
    }

    return NULL; // not found
}

/*  INSERTION  */
/* insert_r: Recursive insertion
 *
 * Args: root pointer, data to store
 * Returns: pointer to root
 *
 */
node*
insert_r(node *root, double data, unsigned int id)
{
    if (root == NULL)
        root = make_node(data, id);
    // else if (root->data == data)  // accept dups
    //    return root;
    else {
        int dir = root->data < data;
        root->link[dir] = insert_r(root->link[dir], data, id);
    }

    return root;
}

/* insert: Conveneince wrapper for insert_r
 *
 * Returns: 1 if successful
 */
bool
insert(tree *tree, double data, unsigned int id)
{
    tree->root = insert_r(tree->root, data, id);
    return true;
}

/* insert_nr: Non-recursive insertion
 *
 * Args: pointer to tree, data to insert
 * Returns: true if successful, false if not
 *
 */
bool
insert_nr(tree *tree, double data, unsigned int id)
{
    if (tree->root == NULL) // empty tree 
        tree->root = make_node(data, id);
    else {
        node *it = tree->root; // help pointer 
        int dir;

        for (;;) {
            dir = it->data < data; // which direction?
            
            if (it->link[dir] == NULL) // we've reached a leaf
                break;
            /* 
            if (it->data == data) // already in tree, won't insert duplicates
                return false;
            else if (it->link[dir] == NULL) // we've reached a leaf, don't continue
                break;
            */

            it = it->link[dir]; // link to the node we want to insert the data
        }

        it->link[dir] = make_node(data, id);
    }

    return true; // successfully inserted data
}


/*  REMOVAL  */
/* remove: Delete a node from the tree
 *
 * Args: tree pointer, data to delete
 * Returns: true if successful, false if not
 *
 */
bool
remove(tree *tree, unsigned int id)
{
    if (tree->root != NULL) { //non-empty tree
        node head = {0};   // dummy root
        node *it = &head;   // current position
        node *p, *f = NULL; // parent node, help pointer if found
        unsigned int dir = 1;  // traverse to the right

        it->link[1] = tree->root;

        while (it->link[dir] != NULL) { // traverse to the bottom
            p = it;  // save parent node
            it = it->link[dir]; // proceed the current pointer
            dir = it->id <= id; // which direction?

            if (it->id == id)
                f = it;  // found it
        }

        if (f != NULL) { // if we found the node to delete
            f->data = it->data; // copy
            f->id = it->id;
            p->link[p->link[1] == it] = it->link[it->link[0] == NULL]; // :)
            delete it;
        }

        tree->root = head.link[1];
    
    if (f == NULL) // node not found
        return false;

    return true;
    
    }

    return false;
}

/* destroy_r: Recurse delete entire tree
 *
 * Args: pointer to root
 * Returns: nothing
 */
void
destroy_r(node *root)
{
    if (root != NULL) {
        destroy_r(root->link[0]);
        destroy_r(root->link[1]);
        delete root;
    }
}

void
destroy(tree *tree)
{
    destroy_r(tree->root);
}

/* destroy_nr: Non-recurse delete entire tree
 *
 * Args: pointer to tree
 */

void
destroy_nr(tree *tree)
{
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
preorder_r(node *root)
{
    if (root != NULL) {
        cout << "ID: " << root->id << " MW: "<< root->data << endl;
        preorder_r(root->link[0]);
        preorder_r(root->link[1]);
    }
}

void
preorder(tree *tree)
{
    preorder_r(tree->root);
}

// Inorder
void
inorder_r(node *root)
{
    if (root != NULL) {
        inorder_r(root->link[0]);
        cout << "ID: " << root->id << " MW: "<< root->data << endl;
        inorder_r(root->link[1]);
    }
}

void
inorder(tree *tree)
{
    inorder_r(tree->root);
}


// Postorder
void
postorder_r(node *root)
{
    if (root != NULL) {
        postorder_r(root->link[0]);
        postorder_r(root->link[1]);
        cout << "ID: " << root->id << " MW: "<< root->data << endl;
    }
}

void
postorder(tree *tree)
{
    postorder_r(tree->root);
}

/* make_node: Create a node
 *
 * Args: data 
 * Returns: pointer to new node
 */
node*
make_node(double data, unsigned int id)
{
    node *it = new node;

    it->data = data;
    it->id = id;
    it->link[0] = NULL;
    it->link[1] = NULL;

    return it;
}
