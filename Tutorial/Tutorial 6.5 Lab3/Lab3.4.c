#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define INF -999999

typedef enum {PUT = 1, GET, ERASE, SIZE, PRINT, ERROR_OP} OP;

// AVL tree node
struct AVLTreeNode{
    int key;
    int value;
    int height;
    struct AVLTreeNode* left;
    struct AVLTreeNode* right;
};

typedef struct AVLTreeNode* TreeNode;

// Map Data Structure
struct Map {
    int size;
    TreeNode root;
};

typedef struct Map* MapADT;

OP get_op() {
    char str[20];
    scanf("%s", str);
    if (strcmp(str, "put") == 0) {
        return PUT;
    } else if (strcmp(str, "get") == 0) {
        return GET;
    } else if (strcmp(str, "erase") == 0) {
        return ERASE;
    } else if (strcmp(str, "size") == 0) {
        return SIZE;
    } else if (strcmp(str, "print") == 0) {
        return PRINT;
    } else {
        return ERROR_OP;
    }
}

// AVL tree
TreeNode createNode(int key, int value) {
    TreeNode node = (TreeNode)malloc(sizeof(struct AVLTreeNode));
    node->key = key;
    node->height = 1;
    node->left = NULL;
    node->right = NULL;
    node->value = value;
    return node;
}

TreeNode Lchild(TreeNode root) {
    return root->left;
}

TreeNode Rchild(TreeNode root) {
    return root->right;
}

int Data(TreeNode root) {
    return root->key;
}

bool isEmpty(TreeNode root) {
    return root == NULL;
}

void Preorder(TreeNode root) {
    if (!isEmpty(root)) {
        printf("<%d,%d> ", root->key, root->value);
        Preorder(Lchild(root));
        Preorder(Rchild(root));
    }
}

void Inorder(TreeNode root) {
    if (!isEmpty(root)) {
        Inorder(Lchild(root));
        printf("<%d,%d> ", root->key, root->value);
        Inorder(Rchild(root));
    }
}

void Postorder(TreeNode root) {
    if (!isEmpty(root)) {
        Postorder(Lchild(root));
        Postorder(Rchild(root));
        printf("<%d,%d> ", root->key, root->value);
    }
}

int max(int a, int b) {
    if (a > b) {
        return a;
    }
    else {
        return b;
    }
}

int Height(TreeNode root) {
    if (isEmpty(root)) {
        return 0;
    }
    return root->height;
}

int calHeight(TreeNode root)
{
    if (isEmpty(root)) {
        return 0;
    }
    return 1+max(Height(root->left), Height(root->right));
}

int Search(TreeNode root, int key) {
    while (root != NULL) {
        if (key == root->key) {
            return root->value;
        } else if (key < root->key) {
            root = root->left;
        } else {
            root = root->right;
        }
    }
    return INF;
}

TreeNode llRotation(TreeNode y) {
    TreeNode x = y->left;
    y->left = x->right;
    x->right = y;

    y->height = calHeight(y);
    x->height = calHeight(x);

    return x;
}

// right-right imbalance
TreeNode rrRotation(TreeNode x) {
    TreeNode y = x->right;
    x->right = y->left;
    y->left = x;

    x->height = calHeight(x);
    y->height = calHeight(y);

    return y;
}

// left-right imbalance
TreeNode lrRotation(TreeNode y) {
    y->left = rrRotation(y->left);
    return llRotation(y);
}

// right-left imbalance
TreeNode rlRotation(TreeNode x) {
    x->right = llRotation(x->right);
    return rrRotation(x);
}

int balanceFactor(TreeNode root)
{
    if (root == NULL) {
        return 0;
    }
    return Height(root->left) - Height(root->right);
}

TreeNode insertNode(TreeNode root, int key, int value) {
    if (root == NULL) 
        return createNode(key, value);

    if (key < root->key) {
        root->left = insertNode(root->left, key, value);
    } else if (key > root->key) {
        root->right = insertNode(root->right, key, value);
    } else { // Update value if key already exists
        root->value = value;
        return root;
    }

    root->height = calHeight(root);

    int balance = balanceFactor(root);

    if (balance > 1 && key < root->left->key) {
        return llRotation(root);
    }
    if (balance < -1 && key > root->right->key) {
        return rrRotation(root);
    }
    if (balance > 1 && key > root->left->key) {
        return lrRotation(root);
    }
    if (balance < -1 && key < root->right->key) {
        return rlRotation(root);
    }

    return root;
}

// if the target node has two children, replace this node with its successor, which is the smallest item in the tree rooted at its right child.
TreeNode deleteNode(TreeNode root, int key) {
    if (root == NULL)
        return root;

    if (key < root->key) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->key) {
        root->right = deleteNode(root->right, key);
    } else {
        // Node with only one child or no child
        if (root->left == NULL) {
            TreeNode temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            TreeNode temp = root->left;
            free(root);
            return temp;
        }

        // Node with two children
        TreeNode temp = root->right;
        while (temp->left != NULL) {
            temp = temp->left;
        }
        root->key = temp->key;
        root->value = temp->value;
        root->right = deleteNode(root->right, temp->key);
    }

    if (root == NULL) {
        return root;
    }

    root->height = calHeight(root);

    // Check balance factor
    int balance = balanceFactor(root);

    // Perform rotations if needed
    if (balance > 1 && balanceFactor(root->left) >= 0) {
        return llRotation(root);
    }
    if (balance < -1 && balanceFactor(root->right) <= 0) {
        return rrRotation(root);
    }
    if (balance > 1 && balanceFactor(root->left) < 0) {
        return lrRotation(root);
    }
    if (balance < -1 && balanceFactor(root->right) > 0) {
        return rlRotation(root);
    }

    return root;
}

// map ADT
void PrintMap(MapADT myMap) {
    printf("Preorder: ");
    Preorder(myMap->root);

    printf("\nInorder: ");
    Inorder(myMap->root);

    printf("\nPostorder: ");
    Postorder(myMap->root);

    printf("\n");
}

MapADT CreateMap() {
    MapADT myMap = (MapADT) malloc(sizeof(struct Map));
    myMap->size = 0;
    myMap->root = NULL;

    return myMap;
}

// If there is no this key, return INF
int Get(MapADT myMap, int key) {
    return Search(myMap->root, key);
}

// If there exists this key, update the value
void Put(MapADT myMap, int key, int value) {
    myMap->root = insertNode(myMap->root, key, value);
    if (Get(myMap, key) == INF) {
        myMap->size++;
    }
}

void Erase(MapADT myMap, int key) {
    if (Get(myMap, key) != INF) {
        myMap->root = deleteNode(myMap->root, key);
        myMap->size--;
    }
}

int Size(MapADT myMap) {
    return myMap->size;
}

int main() {
    int n, m, key, value;
    TreeNode root = NULL;
    MapADT myMap = CreateMap();
    scanf("%d", &n);

    for(int i=0; i<n; i++)
    {
        switch (get_op()) {
            case PUT:
                scanf(" %d%d", &key, &value);
                Put(myMap, key, value);
                break;
            case GET:
                scanf(" %d", &key);
                printf("%d\n", Get(myMap, key));
                break;
            case ERASE:
                scanf(" %d", &key);
                Erase(myMap, key);
                break;
            case SIZE:
                printf("%d\n", Size(myMap));
                break;
            case PRINT:
                PrintMap(myMap);
                break;
            default:
                printf("Error Input\n");
        }
    }
    return 0;
}



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

#define INF -999999

typedef enum {PUT = 1, GET, ERASE, SIZE, PRINT, ERROR_OP} OP;

// AVL tree node
struct AVLTreeNode{
    int key;
    int value;
    int height;
    struct AVLTreeNode* left;
    struct AVLTreeNode* right;
};

typedef struct AVLTreeNode* TreeNode;

// Map Data Structure
struct Map {
    int size;
    TreeNode root;
};

typedef struct Map* MapADT;

OP get_op() {
    char str[20];
    scanf("%s", str);
    if (strcmp(str, "put") == 0) {
        return PUT;
    } else if (strcmp(str, "get") == 0) {
        return GET;
    } else if (strcmp(str, "erase") == 0) {
        return ERASE;
    } else if (strcmp(str, "size") == 0) {
        return SIZE;
    } else if (strcmp(str, "print") == 0) {
        return PRINT;
    } else {
        return ERROR_OP;
    }
}

// AVL tree
TreeNode createNode(int key, int value) {
    TreeNode node = (TreeNode)malloc(sizeof(struct AVLTreeNode));
    node->key = key;
    node->height = 1;
    node->left = NULL;
    node->right = NULL;
    node->value = value;
    return node;
}

TreeNode Lchild(TreeNode root) {
    return root->left;
}

TreeNode Rchild(TreeNode root) {
    return root->right;
}

int Data(TreeNode root) {
    return root->key;
}

bool isEmpty(TreeNode root) {
    return root == NULL;
}

void Preorder(TreeNode root) {
    if (!isEmpty(root)) {
        printf("<%d,%d> ", root->key, root->value);
        Preorder(Lchild(root));
        Preorder(Rchild(root));
    }
}

void Inorder(TreeNode root) {
    if (!isEmpty(root)) {
        Inorder(Lchild(root));
        printf("<%d,%d> ", root->key, root->value);
        Inorder(Rchild(root));
    }
}

void Postorder(TreeNode root) {
    if (!isEmpty(root)) {
        Postorder(Lchild(root));
        Postorder(Rchild(root));
        printf("<%d,%d> ", root->key, root->value);
    }
}

int max(int a, int b) {
    if (a > b) {
        return a;
    }
    else {
        return b;
    }
}

int Height(TreeNode root) {
    if (isEmpty(root)) {
        return 0;
    }
    return root->height;
}

int calHeight(TreeNode root)
{
    if (isEmpty(root)) {
        return 0;
    }
    return 1+max(Height(root->left), Height(root->right));
}

int Search(TreeNode root, int key) {
    if (root == NULL) {
        return INF;
    }
    if (key < root->key) {
        return Search(root->left, key);
    } else if (key > root->key) {
        return Search(root->right, key);
    } else {
        return root->value;
    }
}

TreeNode llRotation(TreeNode y) {
    TreeNode x = y->left;
    y->left = x->right;
    x->right = y;
    y->height = max(Height(y->left), Height(y->right)) + 1;
    x->height = max(Height(x->left), y->height) + 1;
    return x;
}

// right-right imbalance
TreeNode rrRotation(TreeNode y) {
    TreeNode x = y->right;
    y->right = x->left;
    x->left = y;
    y->height = max(Height(y->left), Height(y->right)) + 1;
    x->height = max(y->height, Height(x->right)) + 1;
    return x;
}

// left-right imbalance
TreeNode lrRotation(TreeNode y) {
    y->left = rrRotation(y->left);
    return llRotation(y);
}

// right-left imbalance
TreeNode rlRotation(TreeNode y) {
    y->right = llRotation(y->right);
    return rrRotation(y);
}

int balanceFactor(TreeNode root)
{
    if (root == NULL) {
        return 0;
    }
    return Height(root->left) - Height(root->right);
}

TreeNode insertNode(TreeNode root, int key, int value) {
    if (root == NULL) {
        return createNode(key, value);
    }
    if (key < root->key) {
        root->left = insertNode(root->left, key, value);
    } else if (key > root->key) {
        root->right = insertNode(root->right, key, value);
    } else {
        root->value = value;
        return root;
    }
    root->height = 1 + max(Height(root->left), Height(root->right));
    int balance = balanceFactor(root);
    if (balance > 1 && key < root->left->key) {
        return llRotation(root);
    }
    if (balance < -1 && key > root->right->key) {
        return rrRotation(root);
    }
    if (balance > 1 && key > root->left->key) {
        return lrRotation(root);
    }
    if (balance < -1 && key < root->right->key) {
        return rlRotation(root);
    }
    return root;
}

TreeNode minValueNode(TreeNode root) {
    TreeNode current = root;
    while (current->left != NULL) {
        current = current->left;
    }
    return current;
}

// if the target node has two children, replace this node with its successor, which is the smallest item in the tree ed at its right child.
TreeNode deleteNode(TreeNode root, int key) {
    if (root == NULL) {
        return root;
    }
    if (key < root->key) {
        root->left = deleteNode(root->left, key);
    } else if(key > root->key) {
        root->right = deleteNode(root->right, key);
    } else {
        if( (root->left == NULL) || (root->right == NULL) ) {
            TreeNode temp = root->left ? root->left : root->right;
            if(temp == NULL) {
                temp = root;
                root = NULL;
            } else {
                *root = *temp;
            }
            free(temp);
        } else {
            TreeNode temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
    }
    if (root == NULL) {
        return root;
    }
    root->height = 1 + max(Height(root->left), Height(root->right));
    int balance = balanceFactor(root);
    if (balance > 1 && balanceFactor(root->left) >= 0) {
        return llRotation(root);
    }
    if (balance < -1 && balanceFactor(root->right) <= 0) {
        return rrRotation(root);
    }
    if (balance > 1 && balanceFactor(root->left) < 0) {
        return lrRotation(root);
    }
    if (balance < -1 && balanceFactor(root->right) > 0) {
        return rlRotation(root);
    }
    return root;
}

// map ADT
void PrintMap(MapADT myMap) {
    printf("Preorder: ");
    Preorder(myMap->root);

    printf("\nInorder: ");
    Inorder(myMap->root);

    printf("\nPostorder: ");
    Postorder(myMap->root);

    printf("\n");
}

MapADT CreateMap() {
    MapADT myMap = (MapADT) malloc(sizeof(struct Map));
    myMap->size = 0;
    myMap->root = NULL;

    return myMap;
}

// If there is no this key, return INF
int Get(MapADT myMap, int key) {
    return Search(myMap->root, key);
}

// If there exists this key, update the value
void Put(MapADT myMap, int key, int value) {
    if (Search(myMap->root, key) == INF) {
        myMap->size++;
    }
    myMap->root = insertNode(myMap->root, key, value);
}

void Erase(MapADT myMap, int key) {
    if (Search(myMap->root, key) != INF) {
        myMap->root = deleteNode(myMap->root, key);
        myMap->size--;
    }
}

int Size(MapADT myMap) {
    return myMap->size;
}

int main() {
    int n, m, key, value;
    TreeNode root = NULL;
    MapADT myMap = CreateMap();
    scanf("%d", &n);

    for(int i=0; i<n; i++)
    {
        switch (get_op()) {
            case PUT:
                scanf(" %d%d", &key, &value);
                Put(myMap, key, value);
                break;
            case GET:
                scanf(" %d", &key);
                printf("%d\n", Get(myMap, key));
                break;
            case ERASE:
                scanf(" %d", &key);
                Erase(myMap, key);
                break;
            case SIZE:
                printf("%d\n", Size(myMap));
                break;
            case PRINT:
                PrintMap(myMap);
                break;
            default:
                printf("Error Input\n");
        }
    }
    return 0;
}
