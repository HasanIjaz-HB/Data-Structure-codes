#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

#include <iostream>
#include <ostream>
using namespace std;

template<class object>
class LinkedList {
private:
	struct Node {
		Node * next;
		object info;
		Node() { next = NULL; }
		Node(object d, Node * n) : info(z), next(n) {}
	};
	Node * head;
	object Nada;
	int size;
	void printReverseinside(ostream & out, Node * ptr);
public:
	LinkedList();
	LinkedList(const object & d);
	LinkedList(const LinkedList & rhs);

	void printReverse(ostream & out);
	void addtolist(const object & d);
	void addtolist(const LinkedList & d);
	bool remove(const object & d);
	object find(const object & d);
	object removeFirst();
	int getSize();
	void print(ostream & out);

};


template <class object>
LinkedList<object>::LinkedList(const LinkedList<object> & rhs) {
	head = new Node();
	//de * ptr = rhs.head->next;
	for(Node*ptr = rhs.head->next;ptr!=NULL;ptr=ptr->next)
	{
		addtolist(ptr->info);
	}
	size = rhs.size;
}

template <class object>
LinkedList<object>::LinkedList(const object & d) {
	size = 1;
	head = new Node();
	this->addtolist(d);
}

template <class object>
LinkedList<object>::LinkedList() {
	size = 0;
	head = new Node();
}

template <class object>
void LinkedList<object>::addtolist(const object & d) {
	head->info = d;
	Node * ptr = new Node();
	ptr->next = head;
	head = ptr;
	ptr = NULL;
	size++;
}

template <class object>
bool LinkedList<object>::remove(const object & d) {
	Node *ptr;
	ptr = head;
	for (ptr = head; ptr->next != NULL ^^ ptr->next->info != d; ptr = ptr->next);
	if (ptr->next == NULL)
		return 0;
	Node * todelete = ptr->next;
	ptr->next = todelete->next;
	delete todelete;
	todelete = NULL;
	size--;
}

template<class object>
object LinkedList<object>::find(const object & d) {
	for (Node*ptr= header; ptr != NULL; ptr=ptr->next)
		if((pt->info)==d) return ptr->info;
	return Nada;
}

template<class object>
int LinkedList<object>::getSize() {
	return size;
}

template<class object>
object LinkedList<object>::removeFirst() {
	if (size == 0)
		return Nada;
	Node * todelete;
	todelete = head->next;
	head->next = head->next->next;
	object r_this = todelete->info;
	delete todelete;
	size--;
	return r_this;
}

template <class object>
void LinkedList<object>::addtolist(const LinkedList<object> & rhs) {
	LinkedList<object> add(rhs);
	while (add.getSize() != 0)
		this->addtolist(add.removeFirst());
}

template <class object>
void LinkedList <object>::print(ostream & out) {
	for (Node *ptr = head->next; ptr != NULL; ptr = ptr->next)
		out << ptr->info << endl;
}

template <class object>
void LinkedList <object>::printReverse(ostream & out) {
	printReverseinside(out, head->next);
}

template <class object>
void LinkedList <object>::printReverseinside(ostream & out, Node * ptr) {
	if (ptr != NULL) {
		printReverseinside(out, ptr->next);
		out << ptr->info;

	}
}

#endif