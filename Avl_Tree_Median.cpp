#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

// AVL tree node
struct Node {
    int key;
    int height;
    Node* left;
    Node* right;
    Node(int k) : key(k), height(1), left(nullptr), right(nullptr) {}
};

// AVL tree class
class AVLTree {
private:
    Node* root;

    // Helper functions
    int height(Node* node) {
        return node ? node->height : 0;
    }

    int balanceFactor(Node* node) {
        return height(node->right) - height(node->left);
    }

    void fixHeight(Node* node) {
        node->height = max(height(node->left), height(node->right)) + 1;
    }

    Node* rotateRight(Node* node) {
        Node* q = node->left;
        node->left = q->right;
        q->right = node;
        fixHeight(node);
        fixHeight(q);
        return q;
    }

    Node* rotateLeft(Node* node) {
        Node* p = node->right;
        node->right = p->left;
        p->left = node;
        fixHeight(node);
        fixHeight(p);
        return p;
    }

    Node* balance(Node* node) {
        fixHeight(node);
        if (balanceFactor(node) == 2) {
            if (balanceFactor(node->right) < 0) {
                node->right = rotateRight(node->right);
            }
            return rotateLeft(node);
        }
        if (balanceFactor(node) == -2) {
            if (balanceFactor(node->left) > 0) {
                node->left = rotateLeft(node->left);
            }
            return rotateRight(node);
        }
        return node;
    }

    Node* insert(Node* node, int key) {
        if (!node) {
            return new Node(key);
        }
        if (key < node->key) {
            node->left = insert(node->left, key);
        }
        else {
            node->right = insert(node->right, key);
        }
        return balance(node);
    }

    Node* findMin(Node* node) {
        return node->left ? findMin(node->left) : node;
    }

    Node* removeMin(Node* node) {
        if (!node->left) {
            return node->right;
        }
        node->left = removeMin(node->left);
        return balance(node);
    }

    Node* remove(Node* node, int key) {
        if (!node) {
            return nullptr;
        }
        if (key < node->key) {
            node->left = remove(node->left, key);
        }
        else if (key > node->key) {
            node->right = remove(node->right, key);
        }
        else {
            Node* left = node->left;
            Node* right = node->right;
            delete node;
            if (!right) {
                return left;
            }
            Node* min = findMin(right);
            min->right = removeMin(right);
            min->left = left;
            return balance(min);
        }
        return balance(node);
    }
    void printInOrder(Node* node) {
        if (!node) {
            return;
        }
        printInOrder(node->left);
        cout << node->key << " ";
        printInOrder(node->right);
    }

public:
    AVLTree() : root(nullptr) {}

    // Public methods
    void insert(int key) {
        root = insert(root, key);
    }

    void remove(int key) {
        root = remove(root, key);
    }
    double getMedian() {
        int count = getCount(root);
        if (count == 0) {
            return 0;
        }
        if (count % 2 == 1) {
            return getKthElement(root, count / 2 + 1);
        }
        else {
            return (getKthElement(root, count / 2) + getKthElement(root, count / 2 + 1)) / 2.0;
        }
    }
    
    // Count the number of nodes in the subtree rooted at 'node'
    int getCount(Node* node) {
        if (!node) {
            return 0;
        }
        return getCount(node->left) + getCount(node->right) + 1;
    }
    
    // Get the k-th smallest element in the subtree rooted at 'node'
    int getKthElement(Node* node, int k) {
        int leftCount = getCount(node->left);
        if (k <= leftCount) {
            return getKthElement(node->left, k);
        }
        if (k == leftCount + 1) {
            return node->key;
        }
        return getKthElement(node->right, k - leftCount - 1);
    }
    void printInOrder() {
        printInOrder(root);
    }
};

int main() {
  AVLTree tree;
  ifstream inputFile("entrada.txt");
  string line;
  while (getline(inputFile, line)) {
    stringstream ss(line);
    char op;
    int value;
    ss >> op >> value;
    if (op == 'A') {
      tree.insert(value);
    }
    else if (op == 'E') {
      tree.remove(value);
    }
  }
  inputFile.close();

  
  tree.printInOrder();
  cout << endl;
  double median = tree.getMedian();
  cout << "Median: " << median << endl;

 
  
  return 0;
}