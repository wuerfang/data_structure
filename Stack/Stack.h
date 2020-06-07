#ifndef STACK_H
#define STACK_H
#include<iostream>

template<typename T> class Stack;

template<typename T>
class Node {					//node结点类与单链表中的node相同
	T m_data;
	Node *m_next = nullptr;
	friend class Stack<T>;		//将SList声明为Node的友元
public:
	Node(const T &val) :m_data(val) {  }
	Node(const Node &) = delete;			//禁止复制
	Node& operator=(const Node &) = delete;	//禁止赋值
	const T& data() const { return m_data; }
	T& data() { return m_data; }
	Node* next() { return m_next; }
};

template<typename T>
class Stack {
	Node<T> *m_top = nullptr;
public:
	Stack() = default;
	~Stack();
	Stack(const Stack &) = delete;				//禁止复制
	Stack& operator=(const Stack&) = delete;	//禁止赋值
	void clear();
	bool empty() { return m_top == nullptr; }
	void push(const T &val);
	void pop();
	const T& top(){ return m_top->m_data; }
};

template<typename T>
Stack<T>::~Stack() {
	clear();
}

template<typename T>
void Stack<T>::clear() {
	Node<T> *p = nullptr;
	while (m_top != nullptr) {
		p = m_top;
		m_top = m_top->m_next;
		delete p;
	}
}

template<typename T>
void Stack<T>::push(const T &val) {
	Node<T> *node = new Node<T>(val);
	node->m_next = m_top;
	m_top = node;
}

template<typename T>
void Stack<T>::pop() {
	Node<T> *p = m_top;
	m_top = m_top->m_next;
	delete p;
}



#endif