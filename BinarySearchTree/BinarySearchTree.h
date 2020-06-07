#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include<iostream>

template<typename T> class BinarySearchTree;

template<typename T>
class Node {
	T m_data;
	Node *m_left = nullptr, *m_right = nullptr;
	friend class BinarySearchTree<T>;
public:
	Node(const T &val) :m_data(val) {  }
	Node(const Node &) = delete;
	Node& operator=(const Node &) = delete;
	const T& data() const { return m_data; }
	T& data() { return m_data; }
	Node* left() { return m_left; }
	Node* right() { return m_right; }
};

template<typename T>
class BinarySearchTree {
	Node<T> *m_root;
public:
	BinarySearchTree() = default;
	~BinarySearchTree() { destory(m_root); }
	Node<T>* root() { return m_root; }
	Node<T>* insert(const T &val) { return insert_(m_root, val); }
	Node<T>* search(const T &val) { return search_(m_root, val); }
	void inOrder() { inOrder_(m_root); }
private:
	void destory(Node<T> *p);
	Node<T>* insert_(Node<T> * &p, const T &val);
	Node<T>* search_(Node<T> *p, const T &val);	
	void inOrder_(Node<T> *p);
	void visit(T &val) { std::cout << val << " "; }
};

template<typename T>
void BinarySearchTree<T>::destory(Node<T> *p) {
	while (p != nullptr) {
		destory(p->m_left);
		destory(p->m_right);
		delete p;
	}	
}

template<typename T>
Node<T>* BinarySearchTree<T>::insert_(Node<T> * &p, const T &val) {
	if (p == nullptr)			//找到插入的位置，插入结点，若new失败，std::nothrow能够保证返回空指针
		return p = new (std::nothrow) Node<T>(val);
	else if (val < p->m_data)	//从左子树中查找
		return insert_(p->m_left, val);
	else                        //从左子树中查找
		return insert_(p->m_right, val);
}

template<typename T>
Node<T>* BinarySearchTree<T>::search_(Node<T> *p, const T &val) {
	while (p != nullptr && val != p->m_data) {
		if (val < p->m_data)
			p = p->m_left;
		else
			p = p->m_right;
	}
	return p;
}

template<typename T>
void BinarySearchTree<T>::inOrder_(Node<T> *p) {
	if (p != nullptr) {
		inOrder_(p->m_left);
		visit(p->m_data);
		inOrder_(p->m_right);
	}
}

#endif