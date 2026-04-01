#include <bits/stdc++.h>
using namespace std;

struct Node {
    int val;
    Node *left;
    Node *right;
    Node(int v) : val(v), left(nullptr), right(nullptr) {}
};

// Read extended preorder where -1 means null, -2 means end of input
// Build the binary tree accordingly.
// Returns pointer to root.
Node* buildTree(vector<int>& seq, size_t& idx) {
    if (idx >= seq.size()) return nullptr;
    int x = seq[idx++];
    if (x == -1) return nullptr;
    if (x == -2) return nullptr; // Should not occur during recursive build
    Node* node = new Node(x);
    node->left = buildTree(seq, idx);
    node->right = buildTree(seq, idx);
    return node;
}

// Prune subtrees that contain only 0s (i.e., node value 0 and both pruned children are null)
Node* prune(Node* root) {
    if (!root) return nullptr;
    root->left = prune(root->left);
    root->right = prune(root->right);
    if (root->val == 0 && root->left == nullptr && root->right == nullptr) {
        delete root;
        return nullptr;
    }
    return root;
}

// Print preorder including -1 for null pointers
void printPreorder(Node* root, vector<int>& out) {
    if (!root) {
        out.push_back(-1);
        return;
    }
    out.push_back(root->val);
    printPreorder(root->left, out);
    printPreorder(root->right, out);
}

void freeTree(Node* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<int> a;
    int x;
    while (cin >> x) {
        a.push_back(x);
        if (x == -2) break;
    }
    if (a.empty()) return 0;

    // Remove trailing -2 if present
    if (!a.empty() && a.back() == -2) a.pop_back();

    // Build tree
    size_t idx = 0;
    Node* root = buildTree(a, idx);

    // Prune and print
    root = prune(root);
    vector<int> out;
    printPreorder(root, out);

    // Print space-separated
    for (size_t i = 0; i < out.size(); ++i) {
        if (i) cout << ' ';
        cout << out[i];
    }
    cout << "\n";

    freeTree(root);
    return 0;
}

