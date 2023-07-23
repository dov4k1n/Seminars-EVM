#include <iostream>
 
int numElems = 0;
 
struct TreeNode {
	int value;
	TreeNode* left;
	TreeNode* right;
 
        TreeNode* next;
        int level;
 
	TreeNode (int value, TreeNode* left = NULL,
                          TreeNode* right = NULL, TreeNode* next = NULL, int level = 0):
		value(value),
		left(left),
                right(right),
                next(next),
                level(level)
		{ }
};
 
class Queue {
	private:
		TreeNode** data;
		int size;
		int start;
		int finish;
 
	public:
		Queue(int size) :
			data(new TreeNode*[size]),
			size(size),
			start(size - 1),
			finish(size - 1)
		{ }
 
		~Queue() {
			if (data)
				delete[] data;
		}
 
		void Push(TreeNode* node) {
			if(finish - start == 1 || start - finish == size-1)
				throw std::runtime_error("Queue is full!");
 
			data[finish--] = node;
 
			if(finish < 0)
				finish = size - 1;
		}
 
		TreeNode* Pull() {
			if(start == finish)
				throw std::runtime_error("Queue is empty!");
 
			TreeNode* node = data[start--];
 
			if(start<0)
				start = size - 1;
 
			return node;
		}
 
		TreeNode* Front(){ return data[start]; }
 
		TreeNode* Second() { return data[start - 1]; }
 
		bool Empty() { return start == finish; }
};
 
void Process(TreeNode* root, int numElems){
	TreeNode* node;
        Queue queue(numElems+1);
 
	if (root == NULL)
		return;
 
	queue.Push(root);
 
	while (!queue.Empty()){
		node = queue.Front();
                //int nodeLevel = elemLevel(root, node);
                int nodeLevel = node->level;
                queue.Pull();
                int nextNodeLevel;
 
                if (queue.Empty())
                    nextNodeLevel = 0;
                else
                    nextNodeLevel = queue.Front()->level;
                    //nextNodeLevel = elemLevel(root, queue.Front());
 
		if ( nodeLevel == nextNodeLevel )
			node->next = queue.Front();
		else node->next = NULL;
 
		if (node->left)
			queue.Push((node->left));
 
		if (node->right)
			queue.Push((node->right));
	}
}
 
void PrintTree(TreeNode* root, int numElems){
	TreeNode* node;
        Queue queue(numElems+1);
 
	std::cout << "List of pairs:" << std::endl;
 
	if (root == NULL){
		std::cout << "..empty!" << std::endl;
		return;
	}
 
	queue.Push(root);
 
	while (!queue.Empty()){
		node = queue.Front();
		queue.Pull();
 
		if (node->next != NULL)
			std::cout << node->value << " " 
				<< node->next->value << std::endl;
		else std::cout << node->value << " " 
				<< "NULL" << std::endl;
		if (node->left)
			queue.Push((node->left));
 
		if (node->right)
			queue.Push((node->right));
	}
}
 
void ReadTree(TreeNode*& node){
    int newValue;
 
    std::cin >> newValue;
 
    if (newValue == 0){
        node = nullptr;
        return;
    }
    numElems++;
    node = new TreeNode(newValue);
 //   node->value = newValue;
    node->level++;
    ReadTree(node->left);
    ReadTree(node->right);
}
 
void DeleteTree(TreeNode*& node){
    if (node->left != nullptr)
        DeleteTree(node->left);
 
    if (node->right != nullptr)
        DeleteTree(node->right);
 
    delete node;
 
    node = nullptr;
}
 
int main (void){
        TreeNode* root;
 
        ReadTree(root);
 
	Process(root, numElems);
 
	PrintTree(root, numElems);
 
        DeleteTree(root);
 
	return 0;
}