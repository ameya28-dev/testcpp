#include <iostream>
#include <queue>
// #include <chrono>
// #include <cmath>

class Node
{
public:
    int data;
    Node *left;
    Node *right;

    Node(int val)
    {
        data = val;
        left = nullptr;
        right = nullptr;
    }
};

void preOrder(Node *root)
{
    if (root == nullptr)
    {
        return;
    }
    std::cout << root->data << '\t';
    preOrder(root->left);
    preOrder(root->right);
}

void inOrder(Node *root)
{
    if (root == nullptr)
    {
        return;
    }

    inOrder(root->left);
    std::cout << root->data << '\t';
    inOrder(root->right);
}

void postOrder(Node *root)
{
    if (root == nullptr)
    {
        return;
    }

    postOrder(root->left);
    postOrder(root->right);
    std::cout << root->data << '\t';
}

int search(int inorder[], int start, int end, int curr)
{
    for (int i = start; i <= end; i++)
    {
        if (inorder[i] == curr)
        {
            return i;
        }
    }
    return -1;
}

Node *buildTreePreIn(int preorder[], int inorder[], int start, int end)
{
    static int idx = 0;
    if (start > end)
    {
        return nullptr;
    }

    int curr = preorder[idx];
    idx++;

    Node *node = new Node(curr);
    if (start == end)
    {
        return node;
    }

    int pos = search(inorder, start, end, curr);
    node->left = buildTreePreIn(preorder, inorder, start, pos - 1);
    node->right = buildTreePreIn(preorder, inorder, pos + 1, end);

    return node;
}

Node *buildTreePostIn(int postorder[], int inorder[], int start, int end)
{
    static int index = end;
    if (start > end)
    {
        return nullptr;
    }

    int curr = postorder[index];
    index--;
    Node *node = new Node(curr);
    if (start == end)
    {
        return node;
    }

    int pos = search(inorder, start, end, curr);
    node->right = buildTreePostIn(postorder, inorder, pos + 1, end);
    node->left = buildTreePostIn(postorder, inorder, start, pos - 1);

    return node;
}

void levelOrder(Node *root)
{
    if (root == nullptr)
    {
        return;
    }

    std::queue<Node *> q;
    q.push(root);
    q.push(nullptr);

    while (!q.empty())
    {
        Node *node = q.front();
        q.pop();
        if (node != nullptr)
        {
            std::cout << node->data << ' ';
            if (node->left != nullptr)
            {
                q.push(node->left);
            }
            if (node->right != nullptr)
            {
                q.push(node->right);
            }
        }
        else if (!q.empty())
        {
            q.push(nullptr);
        }
    }
}

int sumAtLevelK(Node *root, int k)
{
    if (root == nullptr)
    {
        return -1;
    }

    std::queue<Node *> q;
    q.push(root);
    q.push(nullptr);
    int sum = 0, level = 0;

    while (!q.empty())
    {
        Node *node = q.front();
        q.pop();
        if (node != nullptr)
        {
            if (level == k)
            {
                sum += node->data;
            }
            if (node->left != nullptr)
            {
                q.push(node->left);
            }
            if (node->right != nullptr)
            {
                q.push(node->right);
            }
        }
        else if (!q.empty())
        {
            q.push(nullptr);
            level++;
        }
    }

    return sum;
}

int numberOfNodes(Node *root)
{
    if (root == nullptr)
    {
        return 0;
    }

    return numberOfNodes(root->left) + numberOfNodes(root->right) + 1;
}

int sumOfAllNodes(Node *root)
{
    if (root == nullptr)
    {
        return 0;
    }
    return sumOfAllNodes(root->left) + sumOfAllNodes(root->right) + root->data;
}

int heightOfTree(Node *root)
{
    if (root == nullptr)
    {
        return 0;
    }

    int lHeight = heightOfTree(root->left);
    int rHeight = heightOfTree(root->right);

    return std::max(lHeight, rHeight) + 1;
}

int diameterOfTree1(Node *root)
{
    if (root == nullptr)
    {
        return 0;
    }

    int lHeight = heightOfTree(root->left);
    int rHeight = heightOfTree(root->right);

    int lDiameter = diameterOfTree1(root->left);
    int rDiameter = diameterOfTree1(root->right);

    return std::max(lHeight + rHeight + 1, std::max(lDiameter, rDiameter));
}

int diameterOfTree2(Node *root, int *height)
{
    if (root == nullptr)
    {
        *height = 0;
        return 0;
    }

    int lHeight = 0, rHeight = 0;

    int lDiameter = diameterOfTree2(root->left, &lHeight);
    int rDiameter = diameterOfTree2(root->right, &rHeight);

    int currentDiameter = lHeight + rHeight + 1;
    *height = std::max(lHeight, rHeight) + 1;

    return std::max(currentDiameter, std::max(lDiameter, rDiameter));
}

void sumReplace(Node *root)
{
    if (root == nullptr)
    {
        return;
    }

    sumReplace(root->left);
    sumReplace(root->right);

    if (root->left != nullptr)
    {
        root->data += root->left->data;
    }
    if (root->right != nullptr)
    {
        root->data += root->right->data;
    }
}

bool isBalancedHeightTree1(Node *root)
{
    if (root == nullptr)
    {
        return true;
    }

    if (!isBalancedHeightTree1(root->left))
    {
        return false;
    }
    if (!isBalancedHeightTree1(root->right))
    {
        return false;
    }

    int lh = heightOfTree(root->left);
    int rh = heightOfTree(root->right);

    if (abs(lh - rh) <= 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool isBalancedHeightTree2(Node *root, int &height)
{
    if (root == nullptr)
    {
        return true;
    }

    int lh = 0, rh = 0;
    if (!isBalancedHeightTree2(root->left, lh))
    {
        return false;
    }

    if (!isBalancedHeightTree2(root->right, rh))
    {
        return false;
    }

    height = std::max(lh, rh) + 1;

    if (abs(lh - rh) <= 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void rightViewOfBinaryTree(Node *root)
{
    if (root == nullptr)
    {
        return;
    }

    std::queue<Node *> q;
    q.push(root);

    while (!q.empty())
    {
        std::size_t queueLengthAtLevel = q.size();
        for (std::size_t i = 0; i < queueLengthAtLevel; i++)
        {
            Node *curr = q.front();
            q.pop();

            if (i == queueLengthAtLevel - 1)
            {
                std::cout << curr->data << '\t';
            }
            if (curr->left != nullptr)
            {
                q.push(curr->left);
            }
            if (curr->right != nullptr)
            {
                q.push(curr->right);
            }
        }
    }

    std::cout << '\n';
}

void leftViewOfBinaryTree(Node *root)
{
    if (root == nullptr)
    {
        return;
    }

    std::queue<Node *> q;
    q.push(root);

    while (!q.empty())
    {
        std::size_t queueLengthAtLevel = q.size();
        for (std::size_t i = 0; i < queueLengthAtLevel; i++)
        {
            Node *curr = q.front();
            q.pop();

            if (i == 0)
            {
                std::cout << curr->data << '\t';
            }
            if (curr->left != nullptr)
            {
                q.push(curr->left);
                continue;
            }
            if (curr->right != nullptr)
            {
                q.push(curr->right);
            }
        }
    }

    std::cout << '\n';
}

Node *findLowestCommonAncestor(Node *root, int n1, int n2)
{
    if (root == nullptr)
    {
        return nullptr;
    }

    if (root->data == n1 || root->data == n2)
    {
        return root;
    }

    Node *left = findLowestCommonAncestor(root->left, n1, n2);
    Node *right = findLowestCommonAncestor(root->right, n1, n2);

    if (left == nullptr && right == nullptr)
    {
        return nullptr;
    }

    if (left != nullptr && right != nullptr)
    {
        // std::cout << "Found in both";
        return root;
    }

    if (left != nullptr)
    {
        return left;
    }

    else
    {
        return right;
    }
}

int findDistance(Node *root, int k, int dist){
    if(root == nullptr){
        return -1;
    }

    if(root->data==k){
        return dist;
    }

    int left = findDistance(root->left, k, dist+1);
    if(left !=-1) {
        return left;
    }
    return findDistance(root->right, k, dist+1);
}

int findShortestDistance(Node *root, int n1, int n2){
    Node *lca = findLowestCommonAncestor(root, n1, n2);
    int d1 = findDistance(lca, n1, 0);
    int d2 = findDistance(lca, n2, 0);

    return d1+d2;
}

int main()
{
    Node *root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->right->left = new Node(6);
    root->right->right = new Node(7);
    Node *root2 = new Node(1);
    root2->left = new Node(2);
    root2->right = new Node(3);
    root2->left->left = new Node(4);
    root2->left->right = new Node(5);
    root2->right->left = new Node(6);
    root2->right->right = new Node(7);

    preOrder(root);
    std::cout << '\n';
    inOrder(root);
    std::cout << '\n';
    postOrder(root);

    std::cout << "\n\n"
              << "Tree from inorder and preorder list:\n\n";
    int preorder[] = {1, 2, 4, 3, 5};
    int inorder[] = {4, 2, 1, 5, 3};
    int postorder[] = {4, 2, 5, 3, 1};

    Node *rootPreIn = buildTreePreIn(preorder, inorder, 0, 4);
    inOrder(rootPreIn);

    std::cout << "\n\n"
              << "Tree from inorder and postorder list:\n\n";
    Node *rootPostIn = buildTreePostIn(postorder, inorder, 0, 4);
    inOrder(rootPostIn);

    std::cout << "\n\n"
              << "Level order traversal:\n\n";
    levelOrder(root);
    std::cout << "\n\nSum at level 2: " << sumAtLevelK(root, 2);

    std::cout << "\n\nNumber of nodes in a tree:\t" << numberOfNodes(root);
    std::cout << "\n\nSum of all the nodes in a tree:\t" << sumOfAllNodes(root);
    std::cout << "\n\nHeight of a tree:\t" << heightOfTree(root);
    std::cout << "\n\nDiameter of a tree (1):\t" << diameterOfTree1(root);

    int height = 0;
    std::cout << "\n\nDiameter of a tree (2):\t" << diameterOfTree2(root, &height);

    std::cout << "\n\n Replacing nodes with sum of their subtrees\n";
    std::cout << "Initial tree: \t";
    preOrder(root2);
    sumReplace(root2);
    std::cout << "\nFinal tree: \t";
    preOrder(root2);

    std::cout << "\n\nIs root a balanced height tree 1:\t" << isBalancedHeightTree1(root);
    height = 0;
    root2->left->left->left = new Node(8);
    root2->left->left->left->left = new Node(9);
    std::cout << "\n\nIs root a balanced height tree 2:\t" << isBalancedHeightTree2(root, height);
    height = 0;
    std::cout << "\n\nIs root2 a balanced height tree 2:\t" << isBalancedHeightTree2(root2, height);

    Node *root3 = new Node(1);
    root3->right = new Node(2);
    root3->right->right = new Node(3);

    std::cout << "\n\nRight view of a binary tree:\n";
    rightViewOfBinaryTree(root2);
    rightViewOfBinaryTree(root);
    rightViewOfBinaryTree(root3);
    std::cout << "\n\nLeft view of a binary tree:\n";
    leftViewOfBinaryTree(root2);
    leftViewOfBinaryTree(root);
    leftViewOfBinaryTree(root3);

    std::cout << "\n\nShortest distance between 2 nodes:\n";
    std::cout << findShortestDistance(root, 1,7) << '\n';
    std::cout << findShortestDistance(root2, 11,7)<< '\n';
    std::cout << findShortestDistance(root3, 1,3)<< '\n';

    std::cout << '\n';
    return 0;
}
