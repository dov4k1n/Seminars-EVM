#include <iostream>
#include <limits>

struct TreeNode {
  int value;
  TreeNode* left;
  TreeNode* right;

  TreeNode(int value,
            TreeNode* left = nullptr,
            TreeNode* right = nullptr) :
      value(value),
      left(left),
      right(right)
  {}

  ~TreeNode() {
    if (left)
      delete left;
    if (right)
      delete right;
  }
};

TreeNode* findMinimum(TreeNode* root) {
  TreeNode* node = root;
  while (node->left != nullptr)
    node = node->left;
  return node;
}

TreeNode* findMaximum(TreeNode* root) {
  TreeNode* node = root;
  while (node->right != nullptr)
    node = node->right;
  return node;
}

bool isBinarySearchTree(TreeNode* root) {
  if (root->left != nullptr)
    if (!isBinarySearchTree(root->left))
      return 0;
  if (root->right != nullptr)
    if (!isBinarySearchTree(root->right))
      return 0;

  TreeNode* min = findMinimum(root);
  TreeNode* max = findMaximum(root);
  
  return std::min(min->value < root->value, max->value >= root->value);
}

TreeNode* addChildBST(TreeNode* root, int value) {
  if (root == nullptr) // Дерево было пустое, создаём новое
    return new TreeNode(value);

  TreeNode* node = root;

  /* Этот цикл завершится тогда, когда в дерево будет добавлен новый элемент. */
  while (true) {
    /* Определяем, в какую ветвь нужно добавить новый элемент. */
    if (value < node->value) {
      if (node->left == nullptr) {
        /* Вставляем элемент в дерево. */
        node->left = new TreeNode(value);
        return root;
      }

      /* Спускаемся дальше по ветви. */
      node = node->left;
    } else {
      if (node->right == nullptr) {
        /* Вставляем элемент в дерево. */
        node->right = new TreeNode(value);
        return root;
      }

      /* Спускаемся дальше по ветви. */
      node = node->right;
    }
  }
  return root;
}

TreeNode* buildBinarySearchTree() {
  TreeNode* root = nullptr;
  int value;
  while (std::cin >> value) {
    root = addChildBST(root, value);
  }

  std::cin.clear(); // сбросить состояние fail в cin
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); // очистить буфер ввода
  
  return root;
}

TreeNode* addChild(TreeNode* root, int value) {
  
  addChild(root->left, value);
  addChild(root->right, value);
}

TreeNode* buildBinaryTree() {
  TreeNode* root = nullptr;
  int value;
  while (std::cin >> value) {
    if (!root)
      root = addChild(root, value);
    
  }

  std::cin.clear(); // сбросить состояние fail в cin
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); // очистить буфер ввода
  
  return root;
}

void printTree(TreeNode* root) {
  if (root->left != nullptr)
    printTree(root->left);
  std::cout << root->value << " ";
  if (root->right != nullptr)
    printTree(root->right);
}

int main() {
  TreeNode* root = buildBinarySearchTree();

  printTree(root); std::cout << std::endl;

  return 0;
}