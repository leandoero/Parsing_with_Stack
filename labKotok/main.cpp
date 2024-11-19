#include <iostream>
#include <string>
#include <cctype>

using namespace std;

template<typename T>
class Stack {
	string inputString;
	struct Node {
		T symbol;
		Node* next;

		Node(T inputSymbol) :symbol(inputSymbol), next(nullptr) {};
	};
	Node* head;
public:
	Stack() :head(nullptr) {};
	void push(T symbol) {
		Node* newEl = new Node(symbol);
		newEl->next = head;
		head = newEl;
	}
	void pop() {
		if (head == nullptr) {
			return;
		}
		Node* temp = head;
		if (head->next) {
			head = head->next;
		}
		else {
			head = nullptr;
		}
		delete temp;
		temp = nullptr;
	}
	T peek() {
		if (head == nullptr) {
			return -1;
		}
		return head->symbol;
	}

	~Stack() {
		while (head) {
			pop();
		}
	}
};

bool calculate(Stack<bool>* boolStack, Stack<char>* charStack, bool currentNumber);

bool realization(string inputString) {

	if (inputString == "0") {
		return false;
	}
	else if (inputString == "1") {
		return true;
	}

	bool currentNumber = 0;
	bool curForPush = 0;
	Stack<bool>* stackForNum = new Stack<bool>();
	Stack<char>* stackForOp = new Stack<char>();

	for (int i = 0; i < inputString.size(); i++)
	{
		char c = inputString[i];
		if (isdigit(c)) {
			curForPush = c - '0';
			stackForNum->push(curForPush);
		}
		else if (c == '(') {
			continue;
		}
		else if (c == ')') {
			currentNumber = calculate(stackForNum, stackForOp, currentNumber);
			stackForNum->pop();
			stackForNum->pop();
		}
		else if (c == '+' || c == '*') {
			stackForOp->push(c);
		}
		else if (c == '~') {
			stackForOp->push(c);
		}
	}
	currentNumber = calculate(stackForNum, stackForOp, currentNumber);
	return currentNumber;
}

bool calculate(Stack<bool>* boolStack,Stack<char>* charStack, bool currentNumber ) {
	char op = charStack->peek();
	switch (op)
	{
	case '+': {
		if (currentNumber == 0 && boolStack->peek() == 0) {
			return 0;
		}
		else {
			return 1;
		}
		break;
	}
	case '*': {
		if (currentNumber == 1 && boolStack->peek() == 1) {
			return 1;
		}
		else {
			return 0;
		}
		break;
	}
	case '~': {
		currentNumber = !currentNumber;
		break;
	}
	default:
		break;
	}

}

int main() {
	string str = "(0*1)+(1*0)";
	cout << boolalpha;
	cout << realization(str);
	return 0;
}