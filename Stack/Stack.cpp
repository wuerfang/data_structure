
#include<vector>
#include"Stack.h"

int main() {
	Stack<int> L;
	std::vector<int> v = { 3,6,4,8,2,23,12,15 };
	for (int i = 0; i < v.size(); ++i) {
		L.push(v[i]);
	}
	int top1 = L.top();
	L.pop();
	int top2 = L.top();
	bool flag1 = L.empty();
	L.clear();
	bool flag2 = L.empty();

	return 0;
}