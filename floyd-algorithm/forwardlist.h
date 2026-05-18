#pragma once

#include <iostream>

class ForwardList {
	
	public:
		struct Node {
			double val;
			Node* next = nullptr;
		};
		Node* head = nullptr;

		ForwardList();
		//~ForwardList();
		ForwardList(ForwardList&& other);
		ForwardList& operator=(ForwardList&& other);
		void push_front(double newval);
		void push_back(double newval);
		void pop_front();
		void pop_back();
		Node* front() const;
		int size() const;
		bool empty() const;
		void display() const;
		Node* find(double val) const;
		void erase(double val);
		void clear();
		void cycle(double _val);
		std::pair<Node*, size_t> floyd() const;
};
