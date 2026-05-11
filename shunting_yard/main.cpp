#include <iostream>
#include <vector>
#include <map>

bool isOperator(const std::string& str) {
	if (str == "^" || str == "*" || str == "/" || str == "+" || str == "-") return true;
	return false;
}

bool isNum(const std::string& str) {
	if (str[0] == '0') return false;
	for(char c : str) {
		if (!std::isdigit(c)) return false;
	}
	return true;
}

int main() {
	std::string str;
	size_t count = 0;
	std::map<std::string, size_t> operators = {{"(", 0}, {")", 0}, {"^", 1}, {"*", 2}, {"/", 2}, {"+", 3}, {"-", 3}};
	std::vector<std::string> result;
	std::stack<std::string> operatorStack;
	while (std::cin >> str) {
		if (isOperator(str)) {
			while (!operatorStack.empty() && operatorStack.top() != "(" ) {
				if (str == "^") {
					if (!operatorStack.empty() && operators[operatorStack.top()] < operators[str]) {
						result.push_back(operatorStack.top());
						operatorStack.pop();
					}
					else break;
				}
				else {
					if (!operatorStack.empty() && operators[operatorStack.top()] <= operators[str]) {
						result.push_back(operatorStack.top());
						operatorStack.pop();
					}
					else break;
				}
			}
			operatorStack.push(str);
		}
		if (isNum(str)) result.push_back(str);
		if (str == "(") {
			operatorStack.push(str);
			count++;
		}
		if (str == ")") {
			while (!operatorStack.empty() && operatorStack.top() != "(") {
				result.push_back(operatorStack.top());
				operatorStack.pop();
			}
			if (operatorStack.empty()) throw std::runtime_error("-");
			count--;
			operatorStack.pop();
		}
		if (std::cin.peek() == '\n') break;
	}

	if (count != 0) throw std::runtime_error("-");

	while (!operatorStack.empty()) {
		if (operatorStack.top() == ")" || operatorStack.top() == "(") throw std::runtime_error("-");
		result.push_back(operatorStack.top());
		operatorStack.pop();
	}



	for(auto elem: result) {
		std::cout << elem << " ";
	}

	return 0;
}
