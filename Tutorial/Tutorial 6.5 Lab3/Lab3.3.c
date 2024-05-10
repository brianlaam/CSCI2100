#include <stdio.h>
#include <stdlib.h>
#define INF -999999

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

TreeNode Insert(TreeNode root, int value) {
    if (root == NULL) 
        return CreateTreeNode(value);

    if (value < root->value) {
        root->left = Insert(root->left, value);
    } else {
        root->right = Insert(root->right, value);
    }

    return root;
}

// If there is no element in BST, which is no less than the value, return INF
// This function should cost O(log N) time
int LowerBound(TreeNode root, int value) {
    int lower_bound = INF;
    while (root != NULL) {
        if (root->value >= value) {
            lower_bound = root->value;
            root = root->left;
        } else {
            root = root->right;
        }
    }
    return lower_bound;    
}


int main() {
    int n, operation, value;
    scanf("%d", &n);

    TreeNode root = NULL;

    for (int i=0;i<n;i++) {
        scanf("%d", &value);
        root = Insert(root, value);
    }

    scanf("%d", &n);

    for (int i=0;i<n;i++) {
        scanf("%d", &value);
        printf("%d\n", LowerBound(root, value));
    }
}
