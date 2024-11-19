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
public:
	Node* head;
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
			stackForOp->pop();
			stackForNum->push(currentNumber);
		}
		else if (c == '+' || c == '*') {
			stackForOp->push(c);
		}
		else if (c == '~') {
			stackForOp->push(c);
		}
	}
	currentNumber = calculate(stackForNum, stackForOp, currentNumber);
	delete stackForNum;
	delete stackForOp;
	return currentNumber;
}

bool calculate(Stack<bool>* boolStack,Stack<char>* charStack, bool currentNumber ) {
	char op = charStack->peek();
	switch (op)
	{
	case '+': {
		if (boolStack->head->next->symbol == 0 && boolStack->peek() == 0) {
			return 0;
		}
		else {
			return 1;
		}
		break;
	}
	case '*': {
		if (boolStack->head->next->symbol == 1 && boolStack->peek() == 1) {
			return 1;
		}
		else {
			return 0;
		}
		break;
	}
	case '~': {
		return !boolStack->peek();
		break;
	}
	default:
		break;
	}

}

int main() {
	setlocale(LC_ALL, "ru");
	cout << "Press 1 for start:\n"
		<< "1. Ввести логическое выражение\n\n" <<
		"Правила ввода: <ЛВ>::=1|0|(~<ЛВ>)|(<ЛВ>*<ЛВ>)|(<ЛВ>+<ЛВ>), где 0 означает false, 1 - true, ~ - отрицание\n"
		<< "* - конъюнкцию, + - дизъюнкцию\n" << endl;
	int choice = 0;
	do {
		cout << "Ввод: ";
		cin >> choice;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Ошибка: введите число 1." << endl;
		}
	} while (choice != 1);

	char choiceForDo;
	do {
		system("cls");
		cout << "Пример ввода: (1+1)*0" << endl;
		cout << "Введите логическое выражениe:   ";
		string logic;
		cin >> logic;
		cout << boolalpha;
		cout << realization(logic) << endl;
		cout << "Для выхода нажать - N/n" << endl;
		cout << "Ввод:";
		cin >> choiceForDo;

	} while (choiceForDo != 'n' && choiceForDo != 'N');
}