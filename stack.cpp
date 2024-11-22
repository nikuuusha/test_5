#include <iostream>

#include "stack.h"

using namespace std;

void Stack::push(int value) {
	elements.push_back(value);
}

void Stack::pop() {
	if (!isEmpty())
		elements.pop_back();
	else cout << "���� ����!\n";
}

int Stack::top() const {
	if (!isEmpty())
		return elements.back();
	else {
		cout << "���� ����. ��� �������� ��������\n";
		return -1;
	}
}

bool Stack::isEmpty() const {
	return elements.empty();
}

void Stack::printStack() const {
	if (!isEmpty()) {
		cout << "�������� �����:";
		for (int element : elements)
			cout << element << " ";
		cout << endl;
	}
	else cout << "���� ����!\n";
}

int Stack::sizeStack() const {
	return elements.size();
}

int Stack::menuStack() {
	Stack stack;
	int select, value;


	while (true) {
		cout << "�������� ����� ��� �����:\n";
		cout << "\t1 - ��������� ������� � ����\n";
		cout << "\t2 - ��������� ������� �� �����\n";
		cout << "\t3 - �������� �������� �������� �����\n";
		cout << "\t4 - ����� �����\n";
		cout << "\t5 - �������� ������ �����\n";
		cout << "\t0 - �����\n";
		cin >> select;
		cout << endl;

		switch (select)
		{
		case 1: {
			cout << "������� �������� ��� ���������� � ����: ";
			cin >> value;
			stack.push(value);
			break;
		}
		case 2: {
			stack.pop();
			break;
		}
		case 3: {
			int topValue = stack.top();
			if (topValue != -1)
				cout << "������� �������: " << topValue << endl;
			break;
		}
		case 4: {
			stack.printStack();
			break;
		}
		case 5: {
			cout << "������ �����: " << stack.sizeStack() << endl;
			break;
		}
		case 0: {
			return 0;
		}
		default:
			cout << "�������� �����!" << endl;
			break;
		}
	}
}
