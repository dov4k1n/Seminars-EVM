 #include <iostream>
using namespace std;

struct TreeNode{
    int value;
    TreeNode* left;
    TreeNode* right;
};

TreeNode* create_new_element(const int& value){
    TreeNode* element = new TreeNode;
    element->value = value;
    element->left = nullptr;
    element->right = nullptr;
    return element;
}

void insert_element(TreeNode* element, TreeNode* head){
    if (element->value < head->value){
        if (head->left == nullptr)
            head->left = element;
        else
            insert_element(element, head->left);
    }
    else{
        if (head->right == nullptr)
            head->right = element;
        else
            insert_element(element, head->right);
    }
}

int number_of_nodes(TreeNode* head){
    int s = 0;
    if (head->left != nullptr)
        s += number_of_nodes(head->left);
    s += 1;
    if (head->right != nullptr)
        s += number_of_nodes(head->right);
    return s;
}

void delete_tree(TreeNode* head){
    if (head->left != nullptr)
        delete_tree(head->left);
    if (head->right != nullptr)
        delete_tree(head->right);
    delete head;
}

void print(TreeNode* head){
    if (head->left != nullptr)
        print(head->left);
    cout << head->value << endl;
    if (head->right != nullptr)
        print(head->right);
}

int main(){
    int value;
    cin >> value;
    TreeNode* head;
    head = create_new_element(value);
    while (cin >> value){
        TreeNode* element;
        element = create_new_element(value);
        insert_element(element, head);
    }
    print(head);
    int s = number_of_nodes(head);
    cout << s << endl;
    delete_tree(head);
    return 0;
}