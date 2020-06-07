#ifndef SLIST_H
#define SLIST_H
#include<iostream>
//using namespace std;

template<typename T> class SList;	//前向声明
template<typename T> std::ostream& operator<<(std::ostream &os, const SList<T> &list);	//前向声明，友元函数

template<typename T>
class Node {
	T m_data;
	Node *m_next = nullptr;
	friend class SList<T>;		//将SList声明为Node的友元
public:
	Node(const T &val) :m_data(val) {  }
	Node(const Node &) = delete;			//禁止复制
	Node& operator=(const Node &) = delete;	//禁止赋值
	const T& data() const { return m_data; }
	T& data() { return m_data; }
	Node* next() { return m_next; }
};

template<typename T>
class SList {
	Node<T> *m_head = nullptr, *m_tail = nullptr;
public:
	SList() = default;
	~SList();
	SList(const SList &) = delete;			 //禁止复制
	SList& operator=(const SList &) = delete;//禁止赋值
	void clear();
	void push_back(const T &val);
	Node<T>* insert(Node<T> *pos, const T &val);
	void erase(const T &val);
	Node<T>* find(const T &val);
	friend std::ostream& operator<< <T>(std::ostream &os, const SList<T> &list);
};

template<typename T>
SList<T>::~SList() {
	clear();
}

template<typename T>
void SList<T>::clear() {
	Node<T> *p = nullptr;
	while (m_head != nullptr) {
		p = m_head;
		m_head = m_head->m_next;
		delete p;
	}
	m_tail = nullptr;
}

template<typename T>
void SList<T>::push_back(const T &val) {
	Node<T>* node = new Node<T>(val);
	if (m_head == nullptr) {
		m_head = m_tail = node;
	}
	else {
		m_tail->m_next = node;
		m_tail = node;
	}
}

template<typename T>
Node<T>* SList<T>::insert(Node<T> *pos, const T &val) {
	Node<T>* node = new Node<T>(val);
	if (pos == m_tail) {		//判断插入的位置是否为尾结点
		m_tail->m_next = node;	
		m_tail = node;
	}
	else {
		node->m_next = pos->m_next;	
		pos->m_next = node;			
	}
	return node;
}

template<typename T>
void SList<T>::erase(const T &val) {
	Node<T> *p = m_head, *q = p;
	while (p != nullptr&&p->m_data != val) {
		q = p;
		p = p->m_next;
	}
	if (p)
		q->m_next = p->m_next;
	if (p == m_tail)
		m_tail = q;
	if (p == m_head && p)
		m_head = p->m_next;
	
	delete p;
}

template<typename T>
Node<T>* SList<T>::find(const T &val) {
	Node<T> *p = m_head;
	while (p != nullptr && p->m_data != val) {
		p = p->m_next;
	}
	return p;
}

template<typename T>
std::ostream& operator<<(std::ostream &os, const SList<T> &list) {
	Node<T> *p = list.m_head;
	while (p != nullptr) {
		os << p->data() << " ";
		p = p->next();
	}
	return os;
}

#endif