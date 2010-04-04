/* ---------- STRUCTS -------- */
struct node {
    double data;       /* data to store */
    unsigned int id;   /* id of entry */
    node *link[2];     /* left(0)/right(1) links */
};

struct tree {
    node *root;
};

/* ----------- API ---------- */ 

/* Search Functions */
node* find_nr(tree*, double);    /* non-recursive search */
node* find_r(node*, double);     /* recursive search */
node* find(tree*, double);       /* convenience wrapper for find_r */

/* Insertion Functions */
node* insert_r(node*, double, unsigned int); /* recursive insertion */ 
bool insert(tree*, double, unsigned int);   /* convenience wrapper for insert_r */
bool insert_nr(tree*, double, unsigned int);/* non-recursive insertion */

/* Deletion Functions */
bool remove(tree*, unsigned int);     /* delete a node */
void destroy_r(node*);      /* recursive destruction of entire tree */
void destroy(tree*);        /* convenience wrapper for destroy_r */
void destroy_nr(tree*);     /* non-recursive destrution of entire tree */

/* Traversal Functions */
void preorder_r(node*);     /* recursive preorder */
void preorder(tree*);       /* convenience wrapper for preorder_r */
void inorder_r(node*);      /* recursive inorder */
void inorder(tree*);        /* convenience wrapper for inorder_r */
void postorder_r(node*);    /* recursive postorder */
void postorder(tree*);      /* convenience wrapper for postorder_r */

/* Auxilary Functions */
node* make_node(double, unsigned int);   /* create a node with data */
