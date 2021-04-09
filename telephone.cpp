#include <bits/stdc++.h>
using namespace std;

// to be used for nodes for coloring
enum Color {red, black};

// class to store info of a single person
class node {
  public :
    // for persons info
    string name;
    long long mob_number;
    // for node info
    node *parent, *left, *right;
    bool color;

    // constructor...
    node (string R_name, long long R_mob_number);
};

node :: node (string R_name, long long R_mob_number) {
    // initialize the basic info
    name = R_name;
    mob_number = R_mob_number;
    // all pointers are initialized to NULL
    // color by default is set to red; can change in future
    parent = left = right = NULL;
    color = red;
}

// class to store a tree
class RedBlackTree {
   
  // these protected functions will only be accessed my the member functions
  protected :
    // removes violations of Red Black tree
    void validateTree (node *&root, node *&newNode);
    // rotates nodes towards left
    void rotateLeft (node *&root, node *&newNode);
    // rotates nodes towards right
    void rotateRight (node *&root, node *&newNode);

  public :
    node *root;
    // constructor...
    RedBlackTree ();
    // to insert the nodes into tree
    void Insert (node *&newNode);
    // after insertion validate function is called
};

// constructor...
RedBlackTree :: RedBlackTree () {
    root = NULL;
}

// inserting the elements into RBTree like BST
node* insertLikeBST (node *root, node *newNode) {
    // if root is a null node
    if ( !root ) {
        // so the new node will be root node
        return newNode;
    }
    // if number is greater than root's number
    if (newNode->mob_number > root->mob_number) {
        // move towards right side
        root->right = insertLikeBST (root->right, newNode);
        root->right->parent = root;
    }
    else {
        // else move to left side
        root->left = insertLikeBST (root->left, newNode);
        root->left->parent = root;
    }
    // return root after insertion
    return root;
}

// insertion of node into RBTree
void RedBlackTree :: Insert (node *&newNode) {
    // first normal BSTlike insertion
    root = insertLikeBST (root, newNode);
    // then we fix violations of red black tree
    validateTree (root, newNode);
}

// fighting violations caused by insertion
void RedBlackTree :: validateTree (node *&root, node *&newNode) {
    // these two are dummy nodes
    node *parent_D = NULL;
    node *grandparent_D = NULL;

    while ((newNode != root) && (newNode->color != black) && (newNode->parent->color == red)) {
        // assign dummy nodes to actual parent and grandparent
        parent_D = newNode->parent;
        grandparent_D = newNode->parent->parent;
        /* Case 1 :
           parent of newNode is left child
           of grandparent of newNode     */
        if (parent_D == grandparent_D->left) {
            /* initialize a dummy uncle of newNode
               to right child of grandparent    */
            node *uncle_D = grandparent_D->right;
            /* case 1.1 :
               uncle is red
               so only coloring is required    */
            if ((uncle_D != NULL) && (uncle_D->color == red)) {
                grandparent_D->color = red;
                parent_D->color = black;
                uncle_D->color = black;
                newNode = grandparent_D;
            }
            else {
                /* case 1.2 :
                   newNode is right child of parent
                   so left rotation is required    */
                if (newNode == parent_D->right) {
                    rotateLeft (root, parent_D);
                    newNode = parent_D;
                    parent_D = newNode->parent;
                }
                /* case 1.3 :
                   newNode id left child of its parent
                   so right rotation is required    */
                rotateRight (root, grandparent_D);
                swap (parent_D->color, grandparent_D->color);
                newNode = parent_D;
            }
        }
        /* Case 2 :
           parent of newNode is right child
           of grandparent of newNode    */
        else {
            /* initialize a dummy uncle of newNode
               to left child of grandparent    */
            node *uncle_D = grandparent_D->left;
            /* case 2.1 :
               uncle is red
               so only coloring is required    */
            if ((uncle_D != NULL) && (uncle_D->color == red)) {
                grandparent_D->color = red;
                parent_D->color = black;
                uncle_D->color = black;
                newNode = grandparent_D;
            }
            else {
                /* case 2.2 :
                   newNode is left child of parent
                   so only right rotation is required    */
                if (newNode == parent_D->left) {
                    rotateRight (root, parent_D);
                    newNode = parent_D;
                    parent_D = newNode->parent;
                }
                /* case 2.3 :
                   newNode is right child of parent
                   so left rotation is required    */
                rotateLeft (root, grandparent_D);
                swap (parent_D->color, grandparent_D->color);
                newNode = parent_D;
            }
        }
    }
    // since root is always black, so we......
    root->color = black;
}

// left rotation of nodes
void RedBlackTree :: rotateLeft (node *&root, node *&newNode) {
    // initialize a dummy node right_D
    node *right_D = newNode->right;
    newNode->right = right_D->left;
    // if right child of newNode is not NULL
    if (newNode->right != NULL) {
        newNode->right->parent = newNode;
    }
    right_D->parent = newNode->parent;
    // if parents of newNode is NULL
    if (newNode->parent == NULL) {
        root = right_D;
    }
    else if (newNode == newNode->parent->left) {
        newNode->parent->left = right_D;
    }
    else {
        newNode->parent->right = right_D;
    }
    right_D->left = newNode;
    newNode->parent = right_D;
}

// right rotation of nodes
void RedBlackTree :: rotateRight (node *&root, node *&newNode) {
    // initialize a dummy node left_D
    node *left_D = newNode->left;
    newNode->left = left_D->right;
    // if left child of newNode is not NULL
    if (newNode->left != NULL) {
        newNode->left->parent = newNode;
    }
    left_D->parent = newNode->parent;
    // if parents of newNode is NULL
    if (newNode->parent == NULL) {
        root = left_D;
    }
    else if (newNode == newNode->parent->left) {
        newNode->parent->left = left_D;
    }
    else {
        newNode->parent->right = left_D;
    }
    left_D->right = newNode;
    newNode->parent = left_D;
}



int main () {

    

    return 0;
}