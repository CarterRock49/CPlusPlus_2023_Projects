
#include "BSTree.h"

template <typename DataType, class KeyType>
BSTree<DataType, KeyType>::BSTreeNode::BSTreeNode ( const DataType &nodeDataItem, BSTreeNode *leftPtr, BSTreeNode *rightPtr )
{
    dataItem = nodeDataItem;
    left = leftPtr;
    right = rightPtr;
}

template < typename DataType, class KeyType >
BSTree<DataType, KeyType>::BSTree ()
{
	root = NULL;
}

template < typename DataType, class KeyType >
BSTree<DataType, KeyType>::BSTree ( const BSTree<DataType,KeyType>& other )
{
    root = NULL;
    *this = other;
}

template < typename DataType, class KeyType >
BSTree<DataType, KeyType>& BSTree<DataType, KeyType>:: operator= ( const BSTree<DataType,KeyType>& other )
{
    if (this != &other) {
        clear();

        if (other.root != NULL) {
            root = new BSTreeNode(other.root->dataItem);
            *root = *other.root;
        }
    }

    return *this;
}

template < typename DataType, class KeyType >
BSTree<DataType, KeyType>::~BSTree ()
{
	clear();
}

template < typename DataType, class KeyType >
void BSTree<DataType, KeyType>::insert ( const DataType& newDataItem )
{
    BSTreeNode* current = root;
    BSTreeNode* trail = NULL;
    BSTreeNode* newNode = new BSTreeNode(newDataItem, NULL, NULL);

    if (root == NULL)
    {
        root = newNode;
    }
    else
    {
        while (current != NULL)
        {
            trail = current;
            if (newDataItem.getKey() < current->dataItem.getKey())
            {
                current = current->left;
            }
            else
            {
                current = current->right;
            }
        }

        if (newDataItem.getKey() < trail->dataItem.getKey())
        {
            trail->left = newNode;
        }
        else
        {
            trail->right = newNode;
        }
    }
}

template < typename DataType, class KeyType >
bool BSTree<DataType, KeyType>::retrieve ( const KeyType& searchKey, DataType& searchDataItem ) const
{
    BSTreeNode* current = root;

    // Traverse the tree to find the node with the specified key
    while (current != NULL) {
        if (searchKey == current->dataItem.getKey()) {
            searchDataItem = current->dataItem;
            return true;
        }
        else if (searchKey < current->dataItem.getKey()) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }

    // Key not found
    return false;
}

template < typename DataType, class KeyType >
bool BSTree<DataType, KeyType>::remove ( const KeyType& deleteKey )
{
    // Check if the tree is empty
    if (root == NULL) {
        return false;
    }
 
    // Find the node to delete
    BSTreeNode* current = root;
    BSTreeNode* parent = NULL;
    bool isLeftChild = true;

    while (current->dataItem.getKey() != deleteKey) {
        parent = current;

        if (deleteKey < current->dataItem.getKey()) {
            current = current->left;
            isLeftChild = true;
        }
        else {
            current = current->right;
            isLeftChild = false;
        }

        if (current == NULL) {
            return false;
        }
    }

    // Node has been found, now delete it
    if (current->left == NULL && current->right == NULL) {
        // Node has no children
        if (current == root) {
            root = NULL;
        }
        else if (isLeftChild) {
            parent->left = NULL;
        }
        else {
            parent->right = NULL;
        }
    }
    else if (current->left == NULL) {
        // Node has one child on the right
        if (current == root) {
            root = current->right;
        }
        else if (isLeftChild) {
            parent->left = current->right;
        }
        else {
            parent->right = current->right;
        }
    }
    else if (current->right == NULL) {
        // Node has one child on the left
        if (current == root) {
            root = current->left;
        }
        else if (isLeftChild) {
            parent->left = current->left;
        }
        else {
            parent->right = current->left;
        }
    }
    else {
        // Node has two children
        BSTreeNode* successor = getSuccessor(current);

        if (current == root) {
            root = successor;
        }
        else if (isLeftChild) {
            parent->left = successor;
        }
        else {
            parent->right = successor;
        }

        successor->left = current->left;
    }

    delete current;
    return true;
}

template < typename DataType, class KeyType >
void BSTree<DataType, KeyType>::writeKeys () const
{
    if (isEmpty()) {
        cout << "Tree is empty." << endl;
        return;
    }

    // Use inorder traversal to output keys in ascending order
    stack<BSTreeNode*> nodes;
    BSTreeNode* current = root;
    while (current != NULL || !nodes.empty()) {
        // Reach the leftmost node of the current subtree
        while (current != NULL) {
            nodes.push(current);
            current = current->left;
        }

        // Process the leftmost node and move to its right subtree
        current = nodes.top();
        nodes.pop();
        cout << current->dataItem.getKey() << " "; // Output the key of the current node
        current = current->right;
    }
    cout << endl;
}

template < typename DataType, class KeyType >
void BSTree<DataType, KeyType>::clear ()
{
    while (root != NULL) {  // loop until the root is NULL
        remove(root->dataItem.getKey()); // remove the node with the root key
    }
}

template < typename DataType, class KeyType >
bool BSTree<DataType, KeyType>::isEmpty () const
{
	return (root == NULL);
}

template < typename DataType, class KeyType >
int BSTree<DataType, KeyType>::getHeight () const
{
    if (isEmpty()) { // empty tree has a height of 0
        return 0;
    }
    else {
        // recursively find the height of the left and right subtrees
        int leftHeight = root->left ? root->left->getHeight() : 0;
        int rightHeight = root->right ? root->right->getHeight() : 0;
        // return the height of the larger subtree plus 1 (for the root node)
        return max(leftHeight, rightHeight) + 1;
    }
}

template < typename DataType, class KeyType >
int BSTree<DataType, KeyType>::getCount () const
{
    int count = 0;
    stack<BSTreeNode*> s;
    BSTreeNode* current = root;
    while (current != NULL || !s.empty()) {
        while (current != NULL) {
            s.push(current);
            current = current->left;
        }
        current = s.top();
        s.pop();
        count++;
        current = current->right;
    }
    return count;
}

template < typename DataType, class KeyType >
void BSTree<DataType, KeyType>::writeLessThan ( const KeyType& searchKey ) const
{
    // Create a stack to hold the nodes that we will visit
    stack<BSTreeNode*> nodeStack;
    BSTreeNode* currNode = root;

    // Traverse the tree until we reach a null node or a node with key greater than or equal to searchKey
    while (currNode != NULL) {
        if (currNode->dataItem < searchKey) {
            nodeStack.push(currNode);
            currNode = currNode->right;
        }
        else {
            currNode = currNode->left;
        }
    }

    // Pop nodes off the stack and output their keys until the stack is empty or we reach a node with key greater than or equal to searchKey
    while (!nodeStack.empty()) {
        currNode = nodeStack.top();
        nodeStack.pop();

        if (currNode->dataItem < searchKey) {
            cout << currNode->dataItem.getKey() << " ";
            currNode = currNode->left;

            // Traverse the right subtree of the popped node and push its nodes onto the stack
            while (currNode != NULL) {
                if (currNode->dataItem < searchKey) {
                    nodeStack.push(currNode);
                    currNode = currNode->right;
                }
                else {
                    break;
                }
            }
        }
    }
}

#include "show9.cpp"