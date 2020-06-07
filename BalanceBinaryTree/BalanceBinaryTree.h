#ifndef BALANCEBINARYTREE_H
#define BALANCEBINARYTREE_H
#include<iostream>
#include <cmath>

template<typename T> class BalanceBinaryTree;
template<typename T>
class Node {
	T m_data;
	Node *m_left = nullptr, *m_right = nullptr;
	int m_bf;	//平衡因子
	friend class BalanceBinaryTree<T>;
public:
	Node(const T &val) :m_data(val), m_bf(0) {  }
	Node(const Node &) = delete;
	Node& operator=(const Node &) = delete;
	const T& data() const { return m_data; }
	T& data() { return m_data; }
	const int& bf() const { return m_bf; }
	int& bf() { return m_bf; }
	Node* left() { return m_left; }
	Node* right() { return m_right; }
};


template<typename T>
class BalanceBinaryTree {
	Node<T> *m_root = nullptr;   //根结点
public:
	BalanceBinaryTree() = default;
	void insert(const T &val);
	void insert_(Node<T> *& root, Node<T> *node);   //将指针S所指节点插入二叉排序中
	int getDepth(Node <T> * T);                     //求树的高度
	int getNodeFactor(Node<T> *node);               //求树中节点的平衡因子
	void bfForTree(Node<T> *&root);                 //求树中的每个节点的平衡因子
	//void nodeBfIsTwo(Node<T> *&root, Node<T> *&p);        //获得平衡因子为2或-2的节点
	//void nodeBfIsTwoFather(Node<T> *&root, Node<T> *&f);  //获得平衡因子为2或-2的节点的父节点
	void bfIsTwo(Node<T> *&root, Node<T> *&f, Node<T>* &p);
	void LLAdjust(Node<T> *&root, Node<T> *&p, Node<T> *&f); //LL调整
	void LRAdjust(Node<T> *&root, Node<T> *&p, Node<T> *&f); //LR调整
	void RLAdjust(Node<T> *&root, Node<T> *&p, Node<T> *&f); //RL调整
	void RRAdjust(Node<T> *&root, Node<T> *&p, Node<T> *&f); //RR调整
	void allAdjust(Node<T> *&root);                       //集成四种调整，并实时更新平衡因子
};


template<typename T>
void BalanceBinaryTree<T>::insert(const T &val) {
	Node<T>* node = new Node<T>(val);
	insert_(m_root, node);
	allAdjust(m_root);
}

template<typename T>
void BalanceBinaryTree<T>::insert_(Node<T> *& root, Node<T> * node) {
	if (root == nullptr)
		root = node;
	else if (node->m_data<root->m_data)
		insert_(root->m_left, node);
	else
		insert_(root->m_right, node);
}

template<typename T>
int BalanceBinaryTree<T>::getDepth(Node<T> * root) {	
	if (root == nullptr)
		return 0;
	else {
		int ldepth = getDepth(root->m_left);
		int rdepth = getDepth(root->m_right);
		int depth = ldepth > rdepth ? ldepth : rdepth;
		depth += 1;
		return depth;
	}
}
//求树中节点的平衡因子
template<typename T>
int BalanceBinaryTree<T>::getNodeFactor(Node<T> *node) {
	int ldepth = 0, rdepth = 0;
	if (node) {
		ldepth = getDepth(node->m_left);
		rdepth = getDepth(node->m_right);
	}
	return ldepth - rdepth;
}
//求树中的每个节点的平衡因子
template<typename T>
void BalanceBinaryTree<T>::bfForTree(Node<T> *&root) {
	if (root) {
		root->m_bf = getNodeFactor(root);
		bfForTree(root->m_left);
		bfForTree(root->m_right);
	}
}
////获得平衡因子为2或-2的节点
//template<typename T>
//void BalanceBinaryTree<T>::nodeBfIsTwo(Node<T> *&root, Node<T> *&p) {
//	if (root) {
//		if (root->m_bf == 2 || root->m_bf == -2) {
//			p = root;
//		}
//		nodeBfIsTwo(root->m_left, p);
//		nodeBfIsTwo(root->m_right, p);
//	}
//}
////获得平衡因子为2或-2的节点的父节点
//template<typename T>
//void BalanceBinaryTree<T>::nodeBfIsTwoFather(Node<T> *&root, Node<T> *&f) {
//	if (root) {
//		if (root->m_left != nullptr) {
//			if (root->m_left->m_bf == 2 || root->m_left->m_bf == -2) {
//				f = root;
//			}
//		}
//		if (root->m_right != nullptr) {
//			if (root->m_right->m_bf == 2 || root->m_right->m_bf == -2) {
//				f = root;
//			}
//		}
//		nodeBfIsTwoFather(root->m_left, f);
//		nodeBfIsTwoFather(root->m_right, f);
//	}
//}
template<typename T>
void BalanceBinaryTree<T>::bfIsTwo(Node<T> *&root, Node<T> *&f, Node<T>* &p) {
	if (root) {
		if (root->m_left != nullptr) {
			if (root->m_left->m_bf == 2 || root->m_left->m_bf == -2) {
				f = root;
				p = root->m_left;
			}
		}
		if (root->m_right != nullptr) {
			if (root->m_right->m_bf == 2 || root->m_right->m_bf == -2) {
				f = root;
				p = root->m_right;
			}
		}
		bfIsTwo(root->m_left, f, p);
		bfIsTwo(root->m_right, f, p);
	}
}

template<typename T>
void BalanceBinaryTree<T>::LLAdjust(Node<T> *&root, Node<T> *&p, Node<T> *&f) {
	Node<T> *r;
	if (root == p) {
		root = p->m_left;		//将P的左孩子提升为新的根节点
		r = root->m_right;
		root->m_right = p;		//将p降为其左孩子的右孩子
		p->m_left = r;			//将p原来的左孩子的右孩子连接其p的左孩子

	}
	else {
		if (f->m_left == p) {			//f的左孩子是p			
			f->m_left = p->m_left;		//将P的左孩子提升为新的根节点
			r = f->m_left->m_right;
			f->m_left->m_right = p;		//将p降为其左孩子的右孩子
			p->m_left = r;				//将p原来的左孩子的右孩子连接其p的左孩子
		}
		if (f->m_right == p){			//f的左孩子是p
			f->m_right = p->m_left;		//将P的左孩子提升为新的根节点
			r = f->m_right->m_right;
			f->m_right->m_right = p;	//将p降为其左孩子的右孩子
			p->m_left = r;				//将p原来的左孩子的右孩子连接其p的左孩子
		}
	}
}

template<typename T>
void BalanceBinaryTree<T>::LRAdjust(Node<T> *&root, Node<T> *&p, Node<T> *&f)
{
	Node<T> *l, *r;
	if (root == p) {           //->m_bf==2&&root->m_left->m_bf!=2
		root = p->m_left->m_right;    //将P的左孩子的右孩子提升为新的根节点
		r = root->m_right;
		l = root->m_left;
		root->m_right = p;
		root->m_left = p->m_left;
		root->m_left->m_right = l;
		root->m_right->m_left = r;
	}
	else {
		if (f->m_right == p) {    //f的左孩子是p
			f->m_right = p->m_left->m_right;    //将P的左孩子的右孩子提升为新的根节点
			r = f->m_right->m_right;
			l = f->m_right->m_left;
			f->m_right->m_right = p;
			f->m_right->m_left = p->m_left;
			f->m_right->m_left->m_right = l;
			f->m_right->m_right->m_left = r;
		}
		if (f->m_left == p) {     //f的左孩子是p
			f->m_left = p->m_left->m_right;    //将P的左孩子的右孩子提升为新的根节点
			r = f->m_left->m_right;
			l = f->m_left->m_left;
			f->m_left->m_right = p;
			f->m_left->m_left = p->m_left;
			f->m_left->m_left->m_right = l;
			f->m_left->m_right->m_left = r;
		}
	}
}

template<typename T>
void BalanceBinaryTree<T>::RLAdjust(Node<T> *&root, Node<T> *&p, Node<T> *&f)
{
	Node<T> *l, *r;
	if (root == p) {          //->m_bf==-2&&root->m_right->m_bf!=-2
		root = p->m_right->m_left;
		r = root->m_right;
		l = root->m_left;
		root->m_left = p;
		root->m_right = p->m_right;
		root->m_left->m_right = l;
		root->m_right->m_left = r;
	}
	else {
		if (f->m_right == p){     //f的左孩子是p
			f->m_right = p->m_right->m_left;
			r = f->m_right->m_right;
			l = f->m_right->m_left;
			f->m_right->m_left = p;
			f->m_right->m_right = p->m_right;
			f->m_right->m_left->m_right = l;
			f->m_right->m_right->m_left = r;
		}
		if (f->m_left == p) {    //f的左孩子是p
			f->m_left = p->m_right->m_left;
			r = f->m_left->m_right;
			l = f->m_left->m_left;
			f->m_left->m_left = p;
			f->m_left->m_right = p->m_right;
			f->m_left->m_left->m_right = l;
			f->m_left->m_right->m_left = r;
		}
	}
}

template<typename T>
void BalanceBinaryTree<T>::RRAdjust(Node<T> *&root, Node<T> *&p, Node<T> *&f) {
	Node<T> *l;
	if (root == p){				//->m_bf==-2&&root->m_right->m_bf!=-2
		root = p->m_right;		//将P的右孩子提升为新的根节点
		l = root->m_left;
		root->m_left = p;		//将p降为其右孩子的左孩子
		p->m_right = l;			//将p原来的右孩子的左孩子连接其p的右孩子
								//注意：p->m_right->m_bf==0插入节点时用不上，删除节点时可用
	}
	else {
		if (f->m_right == p){			//f的右孩子是p
			f->m_right = p->m_right;	//将P的右孩子提升为新的根节点
			l = f->m_right->m_left;
			f->m_right->m_left = p;		//将p降为其右孩子的左孩子
			p->m_right = l;				//将p原来的右孩子的左孩子连接其p的右孩子
		}
		if (f->m_left == p) {			//f的左孩子是p
			f->m_left = p->m_right;		//将P的左孩子提升为新的根节点
			l = f->m_left->m_left;
			f->m_left->m_left = p;		//将p降为其左孩子的左孩子
			p->m_right = l;				//将p原来的右孩子的左孩子连接其p的右孩子
		}
	}
}

template<typename T>
void BalanceBinaryTree<T>::allAdjust(Node<T> *&root) {
	Node<T> *f = nullptr, *p = nullptr;
	bfForTree(root);
	/*nodeBfIsTwoFather(root, f);
	nodeBfIsTwo(root, p);*/
	bfIsTwo(root, f, p);
	while (p) {
		bfForTree(root);
		if (p->m_bf == 2 && (p->m_left->m_bf == 1 || p->m_left->m_bf == 0))	{
			LLAdjust(root, p, f);
			bfForTree(root);
		}
		else if (p->m_bf == 2 && p->m_left->m_bf == -1) {
			LRAdjust(root, p, f);
			bfForTree(root);
		}
		else if (p->m_bf == -2 && p->m_right->m_bf == 1) {
			RLAdjust(root, p, f);
			bfForTree(root);
		}
		else if (p->m_bf == -2 && (p->m_right->m_bf == -1 || p->m_right->m_bf == 0)) {
			RRAdjust(root, p, f);
		}
		f = nullptr;
		p = nullptr;
		/*nodeBfIsTwoFather(root, f);
		nodeBfIsTwo(root, p);*/
		bfIsTwo(root, f, p);
	}
}

#endif
