/**
 * binary_tree.h
 * Purpose: Header file for binary tree configuration
 *  
 * @author Rahul W
 * @version 0.1 10/15/19
 */

// struct for node. Node in the binary tree
struct node {
    int value;
    node *left;
    node *right;
};

// Class for binary tree
class binarytree {

public:

    // default constructors
    binarytree();
    binarytree(const int elements[], const int size);

    // default destructor
    ~binarytree();

    /**
     * @brief  Inserts a node in the binary tree
     * @param  key: Key to be inserted
     * @retval None
     */
    void insertNode(int key);

    /**
     * @brief  Searches the binary tree for a key
     * @param  key: Key to be searches in the tree
     * @retval Returns the node which has the key
     */
    node* search(int key);

    /**
     * @brief  Deletes the tree
     * @retval None
     */
    void destroy_tree();

    /**
     * @brief  Prints the tree in in-orderal traversal
     * @retval None
     */
    void printInOrder();

    /**
     * @brief  Returns the size of the binary tree
     * @retval int tree size
     */
    int size();

    /**
     * @brief  The tilt of a tree node is defined as the absolute difference
     * between the sum of all left subtree node values and the sum of all right
     * subtree node values. Null node has a tilt 0
     * The tilt of the whole tree is defined as the sum of all nodes's tilt
     * @note https://leetcode.com/problems/binary-tree-tilt/  
     * @retval int tilt total
     */
    int tiltTree();


    /**
     * @brief  A binary tree is univalued if every node in the tree has the same
     * value. This is what the function checks
     * @note   https://leetcode.com/problems/univalued-binary-tree/
     * @retval Returns true if the binary tree is univalued
     */
    bool isUnivalTree();


    /**
     * @brief  Invert a binary tree.
     * @note   https://leetcode.com/problems/invert-binary-tree/
     *       4
     *     /   \
     *    2     7
     *   / \   / \
     *  1   3 6   9
     *      
     *       4
     *     /   \
     *    7     2
     *   / \   / \
     *  9   6 3   1
     * 
     * @retval None
     */
    void invertBinaryTree();

private:

    // Helper function to add nodes to the tree
    void insertNode(int key, node *&leaf);

    // Helper function for searching a key in the tree
    node *search(int key, node *leaf);

    // Destroy tree 
    void destroy_tree(node *leaf);

    /**
     * @brief  Prints the tree in in-order traversal format
     * @param  *leaf: leaf to start with
     * @retval None
     */
    void printInOrder(node *leaf);

    /**
     * @brief  Helper function for the tilt tree problem
     * @param  *leaf: 
     * @retval 
     */
    int tiltTree(node *leaf, int *total);

    /**
     * @brief  Helper function for inUnivalTree()
     * @note   https://leetcode.com/problems/univalued-binary-tree/
     * @param  *leaf: Node to check
     * @retval 
     */
    bool isUnivalTree(node *leaf);

    /**
     * @brief  Helper function to invert the binary tree
     * @note   
     * @param  *leaf: Changes to be made to this node
     * @retval None
     */
    node* invertBinaryTree(node *root);

    node *root;
    int treeSize;
};