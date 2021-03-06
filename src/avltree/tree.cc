/**
 * tree.cc
 * Purpose: Implementing AVLTree from scratch
 *  
 * @author Rahul W
 * @version 0.1 01/28/20
 */


/**
 * Pending implementations:
 * 1. Check if the tree is balanced - done
 * 2. Do rotations when a node is inserted - done
 * 3. Create delete
 * 3.1 Create delete min
 * 3.2 Create delete max
 * 4. Min - done
 * 5. Max - done
 * 6. Successor
 * 7. Predecessor
 */

#include <iostream>
#include <algorithm>
#include <iomanip>
#include <queue>
#include <map>
#include <vector>

#include "tree.h"


AVLTree::AVLTree() {
  this->root = nullptr;
}


void AVLTree::Insert(int data) {
  root = InsertHelper(root, data);
}


Node* AVLTree::InsertHelper(Node *root, int data) {
  if (root == nullptr) {
    Node *toInsert = new Node;
    toInsert->data = data;
    toInsert->left = nullptr;
    toInsert->right = nullptr;
    return toInsert;
  }
  if (data < root->data) {
    root->left = InsertHelper(root->left, data);
    root = RebalanceTree(root);
  } else {
    root->right = InsertHelper(root->right, data); 
    root = RebalanceTree(root);
  }
  return root;
}


Node* AVLTree::RebalanceTree(Node *root) {
  // If the balance factor > 1 at the root that means there is some rebalancing
  // required
  int balancefactor = BalanceFactor(root);
  if(balancefactor > 1) {
    if(root->left != nullptr && BalanceFactor(root->left) > 1) {
      // TODO: Pending implementation
      root = LeftRotate(root);
    }
    root = RightRotate(root);
  } else if (balancefactor < -1) {
    if(root->right != nullptr && BalanceFactor(root->right) < -1) {
      // TODO: Pending implementation
      root = RightRotate(root);
    }
    root = LeftRotate(root);
  }
  return root;
}

/*
 *      y                               x
 *     / \     Right Rotation          /  \
 *    x   T3   - - - - - - - >        T1   y 
 *   / \       < - - - - - - -            / \
 *  T1  T2     Left Rotation            T2  T3
 */


Node* AVLTree::LeftRotate(Node *root) {
  Node *tempRoot = root;
  if (root->right != nullptr) {
    root = root->right;
    tempRoot->right = root->right->left;
    root->left = tempRoot;
  }
  return root;
}


Node* AVLTree::RightRotate(Node *root) {
  Node *tempRoot = root;
  if(root->left != nullptr) {
    root = root->left;
    tempRoot->left = root->left->right;
    root->right = tempRoot;
  }
  return root;
}


void AVLTree::PrintTree() {
  PrintTree(root);
}


void AVLTree::PrintTree(Node *root) {
  if (root == nullptr) return;
  PrintTree(root->left);
  std::cout << root->data << std::endl;
  PrintTree(root->right);
}


int AVLTree::GetTreeSize() {
  return GetTreeSize(this->root);
}


int AVLTree::GetTreeSize(Node *root) {
  // 1. Nullptrs are marked as -1
  // 2. Bottom most level is size 0
  // 2.1 Have to take the max or both the subtrees
  if(root == nullptr) {
    return -1;
  }
  int leftTreeSize = GetTreeSize(root->left) + 1;
  int rightTreeSize = GetTreeSize(root->right) + 1;
  return std::max(leftTreeSize, rightTreeSize);
}


std::pair<int, bool> AVLTree::SearchKey(int key) {
  return SearchKey(root, key);
}


std::pair<int, bool> AVLTree::SearchKey(Node *root, int key) {
  if(root == nullptr) {
    return std::make_pair(key, false);
  } else if (key == root->data) {
    return std::make_pair(root->data, true);
  }
  if(key < root->data) {
    return SearchKey(root->left, key);
  } else {
    return SearchKey(root->right, key);
  }
}


bool AVLTree::IsBalanced() {
  return IsBalanced(root);
}


bool AVLTree::IsBalanced(Node *root) {
  if (root == nullptr) return true;
  int leftSubTreeSize = GetTreeSize(root->left);
  int rightSubTreeSize = GetTreeSize(root->right);
  int difference = GetAbsoluteInteger(leftSubTreeSize) -
    GetAbsoluteInteger(rightSubTreeSize);
  if (difference <= 1) return true;
  else return false;
}


inline int AVLTree::BalanceFactor(Node *root) {
  if (root == nullptr) return 0;
  return GetTreeSize(root->left) - GetTreeSize(root->right);
}


inline int AVLTree::GetAbsoluteInteger(int num) {
  if (num >= 0) return num;
  else return -num;
}


void AVLTree::DrawTree() {
  DrawTree(root, 1);
}


void AVLTree::DrawTree(Node *current, int indent) {
  if (current != nullptr)
    {
        DrawTree(current->right, indent + 4);
        if (indent > 0)
            std::cout << std::setw(indent) << " ";
        std::cout << current->data << std::endl;
        DrawTree(current->left, indent + 4);
    }
}


int AVLTree::GetMinElement() {
  return GetMinElement(root);
}


int AVLTree::GetMinElement(Node *root) {
  if (root->left == nullptr) return root->data;
  return GetMinElement(root->left);
}


int AVLTree::GetMaxElement() {
  return GetMaxElement(root);
}


int AVLTree::GetMaxElement(Node *root) {
  if (root->right == nullptr) return root->data;
  return GetMaxElement(root->right);
}


void AVLTree::LevelOrderTraversal() {
  LevelOrderTraversal(root);
}


void AVLTree::LevelOrderTraversal(Node* root) {
  if (root == nullptr) return;
  std::queue<Node*> nodeQueue;
  nodeQueue.push(root);
  while(!nodeQueue.empty()) {
    Node *current = nodeQueue.front();
    std::cout << current->data << " ";
    if (current->left != nullptr) nodeQueue.push(current->left);
    if (current->right != nullptr) nodeQueue.push(current->right);
    nodeQueue.pop();
  }
}


void AVLTree::VerticalOrderTraversal() {
  VerticalOrderTraversal(root);
}


void AVLTree::VerticalOrderTraversal(Node *root) {
  if (root == nullptr) return;
  // data and hd
  std::map<int, std::vector<int>> nodeMap;
  int hd = 0;
  std::queue<std::pair<Node*, int>> nodeQueue;
  nodeQueue.push(std::make_pair(root, hd));
  while(!nodeQueue.empty()) {
    auto current = nodeQueue.front();
    hd = current.second;
    Node *node = current.first;
    nodeMap[hd].push_back(node->data);
    if(node->left != nullptr)
      nodeQueue.push(std::make_pair(node->left, hd - 1));
    if(node->right != nullptr)
      nodeQueue.push(std::make_pair(node->right, hd + 1));
    nodeQueue.pop();
  }

  // Traverse the map and print the nodes at each horizontal distance
  for(auto it = nodeMap.begin(); it != nodeMap.end(); it++) {
    for (size_t i = 0; i < it->second.size(); ++i)
      std::cout << it->second[i] << " ";
    std::cout << std::endl;
  }
}


void AVLTree::TopView() {
  TopView(root);
}


void AVLTree::TopView(Node *root) {
  if (root == nullptr) return;

  std::map<int, std::vector<int>> nodeMap;
  std::queue<std::pair<Node*, int>> nodeQueue;
  int hd = 0;
  nodeQueue.push(std::make_pair(root, hd));
  while(!nodeQueue.empty()) {
    auto current = nodeQueue.front();
    hd = current.second;
    Node *node = current.first;
    // TODO: Understand the problems in using nodeMap
    nodeMap[hd].push_back(node->data);
    if(node->left != nullptr)
      nodeQueue.push(std::make_pair(node->left, hd-1));
    if(node->right != nullptr)
      nodeQueue.push(std::make_pair(node->right, hd+1));
    nodeQueue.pop();
  }

  // Traverse through the map and get only the first element
  for (auto it = nodeMap.begin(); it != nodeMap.end(); ++it) {
    std::cout << it->second[0] << " ";
  }
  std::cout << std::endl;
}


int AVLTree::LCA(int v1, int v2) {
  return LCAHelper(root, v1, v2)->data;
}


Node* AVLTree::LCAHelper(Node *root, int v1, int v2) {
  if (v1 < root->data && v2 < root->data) {
    return LCAHelper(root->left, v1, v2);
  }
  if (v1 > root->data && v2 > root->data) {
    return LCAHelper(root->right, v1, v2);
  }
  return root;
}


int main() {
  AVLTree t;
  for (int i = 0; i < 100; i += 15) {
    t.Insert(i);
  }
  t.DrawTree();
  std::cout << "Lowest Common ancestor: " << t.LCA(60, 90) << std::endl;
}
