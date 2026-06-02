#include "splay_tree_api.h"
#include <iostream>

int main() {
	SplayTree<uint32_t, double> tree;

	tree.insert(14, 1.5);
	//tree.insert(17, 0.5);
	//tree.insert(18, 2.5);
	//tree.remove(17);
		
	double* value = tree.search(14);
	if (value) {
		std::cout << "value = " << *value << std::endl;
	}
       	else {
		std::cout << "failed to find" << std::endl;
	}
	
	std::cout << "Size = " << tree.size() << std::endl;
	std::cout << "Is valid: " << tree.isValidBST() << std::endl;
	
	SplayTree<std::string, double> tree2;

	tree2.insert("str1", 1.5);
	tree2.insert("str2", 0.5);
	double* value2 = tree2.search("str1");
	if (value2) {
		std::cout << "value = " << *value2 << std::endl;
	}
       	else {
		std::cout << "failed to find" << std::endl;
	}
	
	std::cout << "Size = " << tree2.size() << std::endl;
	std::cout << "Is valid: " << tree2.isValidBST() << std::endl;
}
