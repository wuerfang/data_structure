#ifndef BALANCEBINARYTREE_H
#define BALANCEBINARYTREE_H
#include<iostream>
#include <cmath>

template<typename T> class BalanceBinaryTree;
template<typename T>
class Node {
	T m_data;
	Node *m_left = nullptr, *m_right = nullptr;
	int m_bf;	//ƽ������
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
	Node<T> *m_root = nullptr;   //�����
public:
	BalanceBinaryTree() = default;
	void insert(const T &val);
	void insert_(Node<T> *& root, Node<T> *node);   //��ָ��S��ָ�ڵ�������������
	int getDepth(Node <T> * T);                     //�����ĸ߶�
	int getNodeFactor(Node<T> *node);               //�����нڵ��ƽ������
	void bfForTree(Node<T> *&root);                 //�����е�ÿ���ڵ��ƽ������
	//void nodeBfIsTwo(Node<T> *&root, Node<T> *&p);        //���ƽ������Ϊ2��-2�Ľڵ�
	//void nodeBfIsTwoFather(Node<T> *&root, Node<T> *&f);  //���ƽ������Ϊ2��-2�Ľڵ�ĸ��ڵ�
	void bfIsTwo(Node<T> *&root, Node<T> *&f, Node<T>* &p);
	void LLAdjust(Node<T> *&root, Node<T> *&p, Node<T> *&f); //LL����
	void LRAdjust(Node<T> *&root, Node<T> *&p, Node<T> *&f); //LR����
	void RLAdjust(Node<T> *&root, Node<T> *&p, Node<T> *&f); //RL����
	void RRAdjust(Node<T> *&root, Node<T> *&p, Node<T> *&f); //RR����
	void allAdjust(Node<T> *&root);                       //�������ֵ�������ʵʱ����ƽ������
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
//�����нڵ��ƽ������
template<typename T>
int BalanceBinaryTree<T>::getNodeFactor(Node<T> *node) {
	int ldepth = 0, rdepth = 0;
	if (node) {
		ldepth = getDepth(node->m_left);
		rdepth = getDepth(node->m_right);
	}
	return ldepth - rdepth;
}
//�����е�ÿ���ڵ��ƽ������
template<typename T>
void BalanceBinaryTree<T>::bfForTree(Node<T> *&root) {
	if (root) {
		root->m_bf = getNodeFactor(root);
		bfForTree(root->m_left);
		bfForTree(root->m_right);
	}
}
////���ƽ������Ϊ2��-2�Ľڵ�
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
////���ƽ������Ϊ2��-2�Ľڵ�ĸ��ڵ�
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
		root = p->m_left;		//��P����������Ϊ�µĸ��ڵ�
		r = root->m_right;
		root->m_right = p;		//��p��Ϊ�����ӵ��Һ���
		p->m_left = r;			//��pԭ�������ӵ��Һ���������p������

	}
	else {
		if (f->m_left == p) {			//f��������p			
			f->m_left = p->m_left;		//��P����������Ϊ�µĸ��ڵ�
			r = f->m_left->m_right;
			f->m_left->m_right = p;		//��p��Ϊ�����ӵ��Һ���
			p->m_left = r;				//��pԭ�������ӵ��Һ���������p������
		}
		if (f->m_right == p){			//f��������p
			f->m_right = p->m_left;		//��P����������Ϊ�µĸ��ڵ�
			r = f->m_right->m_right;
			f->m_right->m_right = p;	//��p��Ϊ�����ӵ��Һ���
			p->m_left = r;				//��pԭ�������ӵ��Һ���������p������
		}
	}
}

template<typename T>
void BalanceBinaryTree<T>::LRAdjust(Node<T> *&root, Node<T> *&p, Node<T> *&f)
{
	Node<T> *l, *r;
	if (root == p) {           //->m_bf==2&&root->m_left->m_bf!=2
		root = p->m_left->m_right;    //��P�����ӵ��Һ�������Ϊ�µĸ��ڵ�
		r = root->m_right;
		l = root->m_left;
		root->m_right = p;
		root->m_left = p->m_left;
		root->m_left->m_right = l;
		root->m_right->m_left = r;
	}
	else {
		if (f->m_right == p) {    //f��������p
			f->m_right = p->m_left->m_right;    //��P�����ӵ��Һ�������Ϊ�µĸ��ڵ�
			r = f->m_right->m_right;
			l = f->m_right->m_left;
			f->m_right->m_right = p;
			f->m_right->m_left = p->m_left;
			f->m_right->m_left->m_right = l;
			f->m_right->m_right->m_left = r;
		}
		if (f->m_left == p) {     //f��������p
			f->m_left = p->m_left->m_right;    //��P�����ӵ��Һ�������Ϊ�µĸ��ڵ�
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
		if (f->m_right == p){     //f��������p
			f->m_right = p->m_right->m_left;
			r = f->m_right->m_right;
			l = f->m_right->m_left;
			f->m_right->m_left = p;
			f->m_right->m_right = p->m_right;
			f->m_right->m_left->m_right = l;
			f->m_right->m_right->m_left = r;
		}
		if (f->m_left == p) {    //f��������p
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
		root = p->m_right;		//��P���Һ�������Ϊ�µĸ��ڵ�
		l = root->m_left;
		root->m_left = p;		//��p��Ϊ���Һ��ӵ�����
		p->m_right = l;			//��pԭ�����Һ��ӵ�����������p���Һ���
								//ע�⣺p->m_right->m_bf==0����ڵ�ʱ�ò��ϣ�ɾ���ڵ�ʱ����
	}
	else {
		if (f->m_right == p){			//f���Һ�����p
			f->m_right = p->m_right;	//��P���Һ�������Ϊ�µĸ��ڵ�
			l = f->m_right->m_left;
			f->m_right->m_left = p;		//��p��Ϊ���Һ��ӵ�����
			p->m_right = l;				//��pԭ�����Һ��ӵ�����������p���Һ���
		}
		if (f->m_left == p) {			//f��������p
			f->m_left = p->m_right;		//��P����������Ϊ�µĸ��ڵ�
			l = f->m_left->m_left;
			f->m_left->m_left = p;		//��p��Ϊ�����ӵ�����
			p->m_right = l;				//��pԭ�����Һ��ӵ�����������p���Һ���
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
