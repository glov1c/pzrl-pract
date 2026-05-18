#include "forwardlist.h"

#include <iostream>


int main() {
	ForwardList list;
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);
	list.push_back(4);
	list.push_back(5);
	list.push_back(6);
	list.cycle(4);
	std::pair<ForwardList::Node*, size_t> res = list.floyd();
	if (res.first != nullptr) {
		std::cout << (res.first)->val << " " << res.second << std::endl;
	}
	else std::cout << "no cycle found";
	//list.display();	
	return 0;
}
