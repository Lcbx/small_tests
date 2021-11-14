
#include <iostream>


template<class T>
class SpecialList {
public:

	struct Node {
		T ptr = nullptr;
		Node* prev = nullptr;
		Node* next = nullptr;
	};

	SpecialList() {}

	void insert(Node* toAdd, Node* whereIt) {
		toAdd->prev = whereIt->prev;
		toAdd->next = whereIt;
		if (whereIt->prev != nullptr) whereIt->prev->next = toAdd;
		if (whereIt == begin) begin = toAdd;
		size++;
	}
	void insert_front(Node* n) {
		n->next = begin;
		if (begin != nullptr) begin->prev = n;
		begin = n;
		size++;
	}

	Node* erase(Node* n) {
		Node* ret = n->next;
		if (n->next != nullptr)
			n->next->prev = n->prev;
		if (n->prev != nullptr)
			n->prev->next = n->next;
		else begin = n->next;
		size--;
		return ret;
	}
	Node* erase_front() {
		Node* ret = begin;
		if (size != 0 && begin != nullptr) {
			begin = begin->next();
			begin->prev = nullptr;
			size--;
		}
		return ret;
	}

	unsigned int size = 0;
	Node* begin = nullptr;
	// end == nullptr
};


template<class T>
class CRTPlistStatique : public SpecialList<T*>::Node {
public:
	static SpecialList<T*> all;
	CRTPlistStatique() { ptr = static_cast<T*>(this); }

	void register_this() { all.insert_front(this); }
	void remove_this() { all.erase(this); }
};
template<class T>
SpecialList<T*> CRTPlistStatique<T>::all = SpecialList<T*>();