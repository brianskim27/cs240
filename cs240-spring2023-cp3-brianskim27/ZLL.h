#ifndef __ZLL_H_
#define __ZLL_H_

template <typename T>
class ZLL {
	public:
		ZLL();
		~ZLL();
		bool isEmpty() const;
		bool empty();
		bool front(const T &d);
		bool back(const T &d);
		bool join(ZLL &other);
		ZLL &operator+=(const ZLL &other);
		bool contains(const T &d) const;
		ZLL &operator-=(const ZLL &other);
		int removeZany();
		int removeNonZany();
		bool promoteZany();
		bool start();
		bool done() const;
		T getNext();

	private:
		struct Node {
			T data;
			Node *prev, *next;
			Node(const T &d = T(), Node *p = nullptr, Node *n = nullptr): data(d), prev(p), next(n) {}
		};

		Node *head, *tail, *current;
};

#include "ZLL.cpp"
#endif
