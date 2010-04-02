/* ---------- STRUCTS -------- */
struct node {
    int data;       /* data to store */
    node *link[2];  /*  left(0)/right(1) links */
};

struct tree {
    node *root;
};

/* ----------- API ---------- */ 

/* Search Functions */
int find_nr(tree*, int);    /* non-recursive search */
int find_r(node*, int);     /* recursive search */
int find(tree*, int);       /* convenience wrapper for find_r */

/* Insertion Functions */
node* insert_r(node*, int); /* recursive insertion */ 
int insert(tree*, int);   /* convenience wrapper for insert_r */
int insert_nr(tree*, int);/* non-recursive insertion */

/* Deletion Functions */
int remove(tree*, int);     /* delete a node */
void destroy_r(node*);      /* recursive destruction of entire tree */
void destroy(tree*);        /* convenience wrapper for destroy_r */

/* Traversal Functions */
void preorder_r(node*);     /* recursive preorder */
void preorder(tree*);       /* convenience wrapper for preorder_r */
void inorder_r(node*);      /* recursive inorder */
void inorder(tree*);        /* convenience wrapper for inorder_r */
void postorder_r(node*);    /* recursive postorder */
void postorder(tree*);      /* convenience wrapper for postorder_r */
void print_tree(node*, int);/* print a tree horizontally  */

/* Auxillary Functions */
node* make_node(int);       /* create a node with data */
