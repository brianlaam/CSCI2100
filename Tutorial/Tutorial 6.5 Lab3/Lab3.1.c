#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct treeNode {
    int value;
    struct treeNode* left;
    struct treeNode* right;
};

typedef struct treeNode* TreeNode;

TreeNode CreateTreeNode(int value) {
    TreeNode node = (TreeNode) malloc(sizeof(struct treeNode));
    node->value = value;
    node->left = NULL;
    node->right = NULL;

    return node;
}

TreeNode BuildTree(int* inOrder, int* postOrder, int n) {
    if (n == 0)
        return NULL;

    // Create root node
    int rootValue = postOrder[n - 1];
    TreeNode root = CreateTreeNode(rootValue);

    // Find index of root in in-order traversal
    int rootIndex;
    for (rootIndex = 0; rootIndex < n; rootIndex++) {
        if (inOrder[rootIndex] == rootValue)
            break;
    }

    // Build Ltree
    root->left = BuildTree(inOrder, postOrder, rootIndex);

    // Build Rtree
    root->right = BuildTree(inOrder + rootIndex + 1, postOrder + rootIndex, n - rootIndex - 1);

    return root;
}

void PreOrderPrint(TreeNode root) {
    if (root == NULL) {
        return;
    }

    printf("%d ", root->value);
    PreOrderPrint(root->left);
    PreOrderPrint(root->right);
}


int main() {
    int n, operation, value;
    scanf("%d", &n);

    int* inOrder = (int*) malloc(n * sizeof(int));
    int* postOrder = (int*) malloc(n * sizeof(int));

    for (int i=0;i<n;++i) {
        scanf("%d", inOrder + i);
    }

    for (int i=0;i<n;++i) {
        scanf("%d", postOrder + i);
    }

    TreeNode root = BuildTree(inOrder, postOrder, n);

    PreOrderPrint(root);
}
