#include<vector>
#include"SList.h"

int main() {
	SList<int> L;
	std::vector<int> v = { 3,6,4,8,2,23,12,15 };
	for (int i = 0; i < v.size(); ++i) {
		L.push_back(v[i]);
	}
	std::cout << L << std::endl;

	L.insert(L.find(6), 55);
	std::cout << L << std::endl;

	L.erase(23);
	std::cout << L << std::endl;

	return 0;
}