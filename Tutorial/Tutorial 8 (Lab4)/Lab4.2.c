#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// tree structure
struct treeNode {
    int value;
    struct treeNode* left;
    struct treeNode* right;
};

typedef struct treeNode* TreeNode;


// Queue ADT
struct queueNode {
    TreeNode value; // each node in the Queue contains a TreeNode
    struct queueNode* next;
    struct queueNode* prev;
};

typedef struct queueNode* QueueNode;

struct queue {
    int capacity;
    QueueNode head;
    QueueNode tail;
    int size;
};

typedef struct queue* QueueADT;

QueueNode AllocateEmptyQueueNode() {
    QueueNode newNode = (QueueNode) malloc(sizeof(struct queueNode));
    newNode->value = NULL;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

QueueADT CreateQueue(int capacity) {
    QueueADT q = (QueueADT) malloc(sizeof(struct queue));
    q->capacity = capacity;
    q->size = 0;
    q->head = AllocateEmptyQueueNode();
    q->tail = AllocateEmptyQueueNode();
    q->head->next = q->tail;
    q->tail->prev = q->head;
    return q;
}

int IsEmpty(QueueADT q) {
    return q->size == 0;
}

int IsFull(QueueADT q) {
    return q->size == q->capacity;
}

void Enqueue(QueueADT q, TreeNode value) {
    if (q->size < q->capacity) {
        QueueNode tmp = AllocateEmptyQueueNode();
        tmp->value = value;

        QueueNode prev = q->tail->prev;
        prev->next = tmp;
        tmp->prev = prev;

        tmp->next = q->tail;
        q->tail->prev = tmp;

        q->size++;
    }
}

TreeNode Dequeue(QueueADT q) {
    if (!IsEmpty(q)) {
        q->size--;

        TreeNode v;
        QueueNode tmp = q->head->next;
        q->head->next = tmp->next;
        tmp->next->prev = q->head;
        v = tmp->value;
        free(tmp);

        return v;
    } else {
        return NULL;
    }
}

// BST
TreeNode CreateTreeNode(int value) {
    TreeNode newNode = (TreeNode) malloc(sizeof(struct treeNode));
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

TreeNode Insert(TreeNode root, int value) {
    if (root == NULL) {
        return CreateTreeNode(value);
    }

    if (value > root->value) {
        root->right = Insert(root->right, value);
    } else if (value < root->value) {
        root->left = Insert(root->left, value);
    }

    return root;
}

void PrintNode(TreeNode root) {
    if (root != NULL) {
        printf("%d\n", root->value);
    }
}

// level order traversal
// Use the function PrintNode to print the value in a tree node
// number of nodes is smaller than 20000
void LevelOrder(TreeNode root) {
    if (root == NULL)
        return;

    QueueADT queue = CreateQueue(20000);
    Enqueue(queue, root);

    while (!IsEmpty(queue)) {
        TreeNode current = Dequeue(queue);
        PrintNode(current);

        if (current->left != NULL)
            Enqueue(queue, current->left);
        if (current->right != NULL)
            Enqueue(queue, current->right);
    }
}


int main() {
    int n, value;
    scanf("%d", &n);

    TreeNode root = NULL;

    for (int i=0;i<n;++i) {
        scanf("%d", &value);
        root = Insert(root, value);
    }

    LevelOrder(root);
}
