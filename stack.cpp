#include <iostream>

#include "stack.h"

using namespace std;

void Stack::push(int value) {
	elements.push_back(value);
}

void Stack::pop() {
	if (!isEmpty())
		elements.pop_back();
	else cout << "Стек пуст!\n";
}

int Stack::top() const {
	if (!isEmpty())
		return elements.back();
	else {
		cout << "Стек пуст. Нет верхнего элемента\n";
		return -1;
	}
}

bool Stack::isEmpty() const {
	return elements.empty();
}

void Stack::printStack() const {
	if (!isEmpty()) {
		cout << "Элементы стека:";
		for (int element : elements)
			cout << element << " ";
		cout << endl;
	}
	else cout << "Стек пуст!\n";
}

int Stack::sizeStack() const {
	return elements.size();
}

int Stack::menuStack() {
	Stack stack;
	int select, value;


	while (true) {
		cout << "Выберите опцию для стека:\n";
		cout << "\t1 - Поместите элемент в стэк\n";
		cout << "\t2 - Извлеките элемент из стека\n";
		cout << "\t3 - Просмотр верхнего элемента стека\n";
		cout << "\t4 - Вывод стэка\n";
		cout << "\t5 - Получите размер стека\n";
		cout << "\t0 - Выход\n";
		cin >> select;
		cout << endl;

		switch (select)
		{
		case 1: {
			cout << "Введите значение для добавления в стек: ";
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
				cout << "Верхний элемент: " << topValue << endl;
			break;
		}
		case 4: {
			stack.printStack();
			break;
		}
		case 5: {
			cout << "Размер стэка: " << stack.sizeStack() << endl;
			break;
		}
		case 0: {
			return 0;
		}
		default:
			cout << "Неверный выбор!" << endl;
			break;
		}
	}
}
