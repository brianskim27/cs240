#include <iostream>
#include <string>
#include <stdlib.h>
#include "zany.h"
using namespace std;

template <typename T>
ZLL<T>::ZLL(): head(nullptr), tail(nullptr), current(nullptr) {}

template <typename T>
ZLL<T>::~ZLL() {
	empty();
}

template <typename T>
bool ZLL<T>::isEmpty() const {
	return head == nullptr;
}

template <typename T>
bool ZLL<T>::empty() {
	while(!isEmpty()) {
		Node *newNode = head;
		head = head->next;
		delete newNode;
	}

	tail = nullptr;
	return true;
}

template <typename T>
bool ZLL<T>::front(const T &d) {
	Node *newNode = new Node(d, nullptr, head);
	if(!newNode) {
		return false;
	}

	if(head) {
		head->prev = newNode;
	}
	else {
		tail = newNode;
	}
	
	head = newNode;
	return true;
}

template <typename T>
bool ZLL<T>::back(const T &d) {
	Node* newNode = new Node(d, tail, nullptr);
	if(!newNode) {
		return false;
	}

	if(tail) {
		tail->next = newNode;
	}
	else {
		head = newNode;
	}
	
	tail = newNode;
	return true;
}

template <typename T>
bool ZLL<T>::join(ZLL &other) {
	if(this == &other) {
		return true;
	}
	if(other.isEmpty()) {
		return true;
	}

	if(isEmpty()) {
		head = other.head;
		tail = other.tail;
	}
	else {
		tail->next = other.head;
		other.head->prev = tail;
		tail = other.tail;
	}

	other.head = nullptr;
	other.tail = nullptr;
	return true;
}

template <typename T>
ZLL<T> &ZLL<T>::operator+=(const ZLL &other) {
	if(this == &other) {
		return *this;
	}
	
	Node *curr = other.head;
	while(curr != nullptr) {
		this->back(curr->data);
		curr = curr->next;
	}
	
	return *this;
}

template<typename T>
bool ZLL<T>::contains(const T &value) const {
	Node *curr = head;
	while(curr != nullptr) {
		if(curr->data == value) {
			return true;
		}
		curr = curr->next;
	}
	return false;
}

template <typename T>
ZLL<T> &ZLL<T>::operator-=(const ZLL &other) {
	if(this == &other) {
		return *this;
	}

	Node *curr = head;
	while(curr != nullptr) {
		if(other.contains(curr->data)) {
			Node *remNode = curr;
			curr = curr->next;
			delete remNode;
		}
	}
	return *this;
}

template <typename T>
int ZLL<T>::removeZany() {
	int count = 0;
	Node *curr = head;
	while(curr != nullptr) {
		if(isZany(curr->data)) {
			if(curr == head) {
				head = curr->next;
				if(head != nullptr) {
					head->prev = nullptr;
				}
				else {
					tail = nullptr;
				}
			}
			else if(curr == tail) {
				tail = curr->prev;
				tail->next = nullptr;
			}
			else {
				curr->prev->next = curr->next;
				curr->next->prev = curr->prev;
			}
			
			Node *remNode = curr;
			curr = curr->next;
			delete remNode;
			count++;
		}
		else {
			curr = curr->next;
		}
	}

	return count;
}

template <typename T>
int ZLL<T>::removeNonZany() {
	int count = 0;
	Node *curr = head;
	while(curr != nullptr) {
		if(!isZany(curr->data)) {
			if(curr == head) {
				head = curr->next;
				if(head != nullptr) {
					head->prev = nullptr;
				}
				else {
					tail = nullptr;
				}
			}
			else if(curr == tail) {
				tail = curr->prev;
				tail->next = nullptr;
			}
			else {
				curr->prev->next = curr->next;
				curr->next->prev = curr->prev;
			}
			
			Node *remNode = curr;
			curr = curr->next;
			delete remNode;
			count++;
		}
		else {
			curr = curr->next;
		}
	}

	return count;
}

template <typename T>
bool ZLL<T>::promoteZany() {
	if(isEmpty() || head == tail) {
		return false;
	}

	Node *curr = head;
	while(curr != nullptr) {
		if(isZany(curr->data)) {
			if(curr != head) {
				curr->prev->next = curr->next;
				if(curr->next != nullptr) {
					curr->next->prev = curr->prev;
				}
				else {
					tail = curr->prev;
				}

				curr->next = head;
				curr->prev = nullptr;
				head->prev = curr;
				head = curr;
			}

			curr = curr->next;
		}
		else {
		curr = curr->next;
		}
	}

	return true;
}

template <typename T>
bool ZLL<T>::start() {
	if(head == nullptr) {
		current = nullptr;
		return false;
	}
	
	current = head;
	return true;
}

template <typename T>
bool ZLL<T>::done() const {
	if(current == nullptr) {
		return true;
	}
	
	return false;
}

template <typename T>
T ZLL<T>::getNext() {
	if(current == nullptr) {
		return T();
	}
	
	T value = current->data;
	current = current->next;
	return value;
}
