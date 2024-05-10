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