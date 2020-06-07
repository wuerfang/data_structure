#include"BinarySearchTree.h"
#include<vector>

int main() {
	BinarySearchTree<int> BST;
	std::vector<int> v = { 3,6,4,8,2,23,12,15 };
	for (int i = 0; i < v.size(); ++i) {
		BST.insert(v[i]);
	}
	BST.inOrder();

	return 0;
}