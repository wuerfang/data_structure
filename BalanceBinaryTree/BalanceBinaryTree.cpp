#include"BalanceBinaryTree.h"
#include<vector>

int main() {

	BalanceBinaryTree<int> tree;
	std::vector<int> v = { 4,5,6,3,2,1,9,8};
	for (int i = 0; i < v.size(); ++i) {
		tree.insert(v[i]);
	}
	return 0;
}