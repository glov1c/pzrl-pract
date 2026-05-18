#include <iostream>

#include "forwardlist.h"

ForwardList::ForwardList() :
	head(nullptr) 
{}

/*
ForwardList::~ForwardList() {
	Node* elem = head;
	while (elem != nullptr && elem->next != head) {
		Node* tmp = elem;	
		elem = elem->next;
		delete tmp;
	}
}
*/

ForwardList::ForwardList(ForwardList&& other) : head(other.head) {
	other.head = nullptr;
}


ForwardList& ForwardList::operator=(ForwardList&& other) {
	if (this != &other) {
		ForwardList::clear();
		head = other.head;
		other.head = nullptr;
	}
	throw std::runtime_error("");
}

void ForwardList::push_front(double newval) {
	Node* first = new Node;
	first->val = newval;
	first->next = head;
	head = first;
}

void ForwardList::push_back(double newval) {
	Node* last = new Node;
	last->val = newval;
	last->next = nullptr;
	Node* tmp = head;
	if (tmp == nullptr) head = last;
	else {
		while (tmp->next != nullptr) {
			tmp = tmp->next;
		}
		tmp->next = last;
	}
}

void ForwardList::pop_front() {
	if (head == nullptr) return;
	Node* tmp = head;
	head = head->next;
	delete tmp;
}

void ForwardList::pop_back() {
	Node* tmp = head;
	Node* ntmp = tmp->next;
	while (ntmp->next != nullptr) {
		tmp = tmp->next;
		ntmp = ntmp->next;
	}
	tmp->next = nullptr;
	delete ntmp;
}

ForwardList::Node* ForwardList::front() const{
	return head;
}

ForwardList::Node* ForwardList::find(double val) const{
	Node* elem = head;
	while (elem != nullptr) {
		if (elem->val == val) return elem;
		elem = elem->next;
	}
	throw std::runtime_error("no such element");
}

int ForwardList::size() const {
	int count = 0;
	Node* elem = head;
	while (elem != nullptr) {
		count++;
		elem = elem->next;
	}
	return count;
}

bool ForwardList::empty() const {
	if (head == nullptr) return true;
	return false;
}

void ForwardList::display() const {
	Node* elem = head;
	while (elem != nullptr) {
		std::cout << elem->val << " ";
		elem = elem->next;
	}
	std::cout << std::endl;
}

void ForwardList::erase(double val1) {
	Node* elem = head->next;
	Node* prev = head;
	while (elem != nullptr) {
		if (elem->val == val1) {
			prev->next = elem->next;
			delete elem;
			elem = prev->next;	
		}
		else {
			prev = prev->next;
			elem = elem->next;
		}
	}
	if (head->val == val1) {
		head = head->next;
	}
}

void ForwardList::clear() {
	Node* elem = head;
	while (elem != nullptr) {
		Node* tmp = elem;	
		elem = elem->next;
		delete tmp;
	}
	head = nullptr;
}

void ForwardList::cycle(double _val) {
	Node* elem = head;
	Node* n = nullptr;
	while (elem->next != nullptr) {
		if (elem->val == _val) n = elem;
		elem = elem->next;
	}
	elem->next = n;
}

std::pair<ForwardList::Node*, size_t> ForwardList::floyd() const {
        if (head == nullptr) return {nullptr, 0};
        
        Node* tortoise = head->next;
        Node* hare = head->next->next;
        
        while (tortoise != hare) {
            if (hare == nullptr || hare->next == nullptr) return {nullptr, 0};
            tortoise = tortoise->next;
            hare = hare->next->next;
        }
        
	ForwardList::Node* start;
        tortoise = head;
        while (tortoise != hare) {
            tortoise = tortoise->next;
            hare = hare->next;
        }
	start = tortoise;
        
        size_t len = 1;
        hare = tortoise->next;
        while (tortoise != hare) {
            hare = hare->next;
            len++;
        }
        
        return {start, len};
}
