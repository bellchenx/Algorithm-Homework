#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

/* 
    Node Structure Definition
*/
struct Node
{
    long long key;
    long long sum;
    struct Node *left, *right;
};

/* 
    Create new node.
    args
        key(long long): key of the new node
    return
        the pointer of new node
*/
Node *createNode(long long key)
{
    Node *tempNode = new Node;
    tempNode->key = key;
    tempNode->sum = key;
    tempNode->left = NULL;
    tempNode->right = NULL;
    return tempNode;
}

/* 
    Create and insert a new node to the tree.
    args
        tree(Node*): the root node of tree
        key(long long): key of the new node 
*/
void insert(Node *root, long long key)
{
    if (root->key < key)
        if (root->right != NULL)
            insert(root->right, key);
        else
            root->right = createNode(key);
    else if (root->left != NULL)
        insert(root->left, key);
    else
        root->left = createNode(key);
    root->sum += key;
}

/* 
    Sum the all nodes greater than upper bound
    args
        tree(Node*): the root node of tree
        low(long long): the lower bound of the range
    return
        the sum of nodes greater than upper bound
*/
long long sumRangeLeft(Node *root, long long low)
{
    if (root == NULL)
        return 0;
    if (low < root->key)
    {
        long long rightSum = 0;
        if (root->right != NULL)
            rightSum = root->right->sum;
        return root->key + sumRangeLeft(root->left, low) + rightSum;
    }
    else
    {
        long long rightSum = 0, rootSum = 0;
        if (root->right != NULL)
            rightSum = sumRangeLeft(root->right, low);
        if (root->key == low)
            rootSum = root->key;
        return rootSum + rightSum;
    }
}

/* 
    Sum the all nodes less than upper bound
    args
        tree(Node*): the root node of tree
        high(long long): the upper bound of the range
    return
        the sum of nodes less than upper bound
*/
long long sumRangeRight(Node *root, long long high)
{
    if (root == NULL)
        return 0;
    if (high > root->key)
    {
        long long leftSum = 0;
        if (root->left != NULL)
            leftSum = root->left->sum;
        return root->key + sumRangeRight(root->right, high) + leftSum;
    }
    else
    {
        long long leftSum = 0, rootSum = 0;
        if (root->left != NULL)
            leftSum = sumRangeRight(root->left, high);
        if (root->key == high)
            rootSum = root->key;
        return rootSum + leftSum;
    }
}

/* 
    Sum the values of all nodes between an interval
    args
        tree(Node*): the root node of tree
        low(long long): the lower bound of the range
        high(long long): the upper bound of the range
    return
        the sum of nodes in range
*/
long long sumRange(Node *root, long long low, long long high)
{
    return sumRangeLeft(root, low) + sumRangeRight(root, high) - root->sum;
}

/* 
    Main function.
    args
        arg(int): number of args from command line
        argv[](char*): the pointer of args array
    return 
        return value to system
*/
int main(int arg, char *argv[])
{
    // Input Data and Construct Tree
    ifstream dataStream(argv[1]);
    long long rootKey;
    dataStream >> rootKey;
    Node *tree = createNode(rootKey);
    for (long long n; dataStream >> n;)
    {
        insert(tree, n);
    }

    // Input Range Numbers and Compute
    ifstream rangeStream(argv[2]);
    long long low, high;
    for (long long n, i = 0; rangeStream >> n; i++)
    {
        if (i % 2 == 0)
            low = n;
        else
        {
            high = n;
            long long sum = sumRange(tree, low, high);
            cout << "Range [" << low << "," << high << "]. ";
            cout << "Sum = " << sum << "." << endl;
        }
    }
    return 0;
}