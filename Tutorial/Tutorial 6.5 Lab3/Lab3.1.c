/*
I, Lam Hoi Chun, am submitting the assignment for
an individual project.
I declare that the assignment here submitted is original except for
source material explicitly acknowledged, the piece of work, or a part
of the piece of work has not been submitted for more than one purpose
(i.e. to satisfy the requirements in two different courses) without
declaration. I also acknowledge that I am aware of University policy
and regulations on honesty in academic work, and of the disciplinary
guidelines and procedures applicable to breaches of such policy and
regulations, as contained in the University website
http://www.cuhk.edu.hk/policy/academichonesty/.
It is also understood that assignments without a properly signed
declaration by the student concerned will not be graded by the
teacher(s).
*/

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