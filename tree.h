#include "treeNode.h"
#include <iomanip>

using namespace std;
template <class V>
class AVLtree 
{
    TreeNode<V>* root;

    // Helper function to calculate the height of a node
    int height(TreeNode<V>* node) {
        if (node == nullptr)
            return 0;
        return node->height;
    }

    // Helper function to calculate balance factor of a node
    int getBalance(TreeNode<V>* node) {
        if (node == nullptr)
            return 0;
        return height(node->left) - height(node->right);
    }

    // Right rotation to fix left-heavy imbalance
    TreeNode<V>* rightRotate(TreeNode<V>* y) {
        TreeNode<V>* x = y->left;
        TreeNode<V>* T2 = x->right;

        // Perform rotation
        x->right = y;
        y->left = T2;

        // Update heights
        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;

        return x;  // New root
    }

    // Left rotation to fix right-heavy imbalance
    TreeNode<V>* leftRotate(TreeNode<V>* x) {
        TreeNode<V>* y = x->right;
        TreeNode<V>* T2 = y->left;

        // Perform rotation
        y->left = x;
        x->right = T2;

        // Update heights
        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;

        return y;  // New root
    }

    // Insert a node into the tree
    TreeNode<V>* insert(TreeNode<V>* node, V key) {
        // Perform normal BST insert
        if (node == nullptr)
            return new TreeNode<V>(key);

        if (key < node->datum)
            node->left = insert(node->left, key);
        else if (key > node->datum)
            node->right = insert(node->right, key);
        else  // Duplicates are not allowed
            return node;

        // Update the height of this ancestor node
        node->height = 1 + max(height(node->left), height(node->right));

        // Get the balance factor to check whether this node became unbalanced
        int balance = getBalance(node);

        // If this node becomes unbalanced, there are 4 cases

        // Left Left Case
        if (balance > 1 && key < node->left->datum)
            return rightRotate(node);

        // Right Right Case
        if (balance < -1 && key > node->right->datum)
            return leftRotate(node);

        // Left Right Case
        if (balance > 1 && key > node->left->datum) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Right Left Case
        if (balance < -1 && key < node->right->datum) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        // Return the (unchanged) node pointer
        return node;
    }

    // Search for a key in the tree
    bool search(TreeNode<V>* node, V key) {
        if (node == nullptr)
            return false;
        if (key == node->datum)
            return true;
        else if (key < node->datum)
            return search(node->left, key);
        else
            return search(node->right, key);
    }

    // Print the tree
    void print(TreeNode<V>* node) 
    {
        if (node == nullptr) return;
    
        print(node->left);

        cout<< node->datum << endl;

        print(node->right);
        
    }

    // Delete a node and maintain the AVL property
    TreeNode<V>* deleteNode(TreeNode<V>* root, V key) {
        if (root == nullptr)
            return root;

        if (key < root->datum)
            root->left = deleteNode(root->left, key);
        else if (key > root->datum)
            root->right = deleteNode(root->right, key);
        else {
            // Node to be deleted found

            // Node with only one child or no child
            if (root->left == nullptr || root->right == nullptr) {
                TreeNode<V>* temp = root->left ? root->left : root->right;

                // No child case
                if (temp == nullptr) {
                    temp = root;
                    root = nullptr;
                } else {  // One child case
                    *root = *temp;
                }

                delete temp;
            } else {
                // Node with two children: Get the inorder successor (smallest in the right subtree)
                TreeNode<V>* temp = minValueNode(root->right);

                // Copy the inorder successor's content to this node
                root->datum = temp->datum;

                // Delete the inorder successor
                root->right = deleteNode(root->right, temp->datum);
            }
        }

        // If the tree had only one node, return
        if (root == nullptr)
            return root;

        // Update the height of the current node
        root->height = 1 + max(height(root->left), height(root->right));

        // Get the balance factor to check whether this node became unbalanced
        int balance = getBalance(root);

        // If this node becomes unbalanced, then there are 4 cases

        // Left Left Case
        if (balance > 1 && getBalance(root->left) >= 0)
            return rightRotate(root);

        // Left Right Case
        if (balance > 1 && getBalance(root->left) < 0) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        // Right Right Case
        if (balance < -1 && getBalance(root->right) <= 0)
            return leftRotate(root);

        // Right Left Case
        if (balance < -1 && getBalance(root->right) > 0) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }

    // Get the node with the minimum value
    TreeNode<V>* minValueNode(TreeNode<V>* node) {
        TreeNode<V>* current = node;
        while (current->left != nullptr)
            current = current->left;
        return current;
    }

    public:
        AVLtree() {
            root = nullptr;
        }

        void insert(V key) {
            root = insert(root, key);
        }

        bool search(V key) {
            return search(root, key);
        }

        void deleteNode(V key) {
            root = deleteNode(root, key);
        }

        void print() {
            print(root);
        }
};
