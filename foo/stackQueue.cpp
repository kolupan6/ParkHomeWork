#include <iostream>

class stack {
private:

	int* base;
	int* next_item;
	int base_size;
	int stack_size;

	void copy(int*, int*, int);
	void resize(int);
	void init(int);

public:

	stack() {
		base = nullptr;
		next_item = nullptr;
		base_size = 0;
		stack_size = 0;
	}

	~stack() {
		delete[] base;

		base = nullptr;
		next_item = nullptr;
		base_size = 0;
		stack_size = 0;
	}

	void Push(int);
	int Pop();

	int size() const;
	bool is_empty() const;
	int top() const;
};

void stack::copy(int* from, int* to, int count) {
	int* fPtr = from;
	int* tPtr = to;

	for (int i = 0; i < count; ++i) {
		tPtr[i] = fPtr[i];
	}
}

void stack::resize(int new_size) {//реализаци динамического выделения памяти
	int* new_base = new int[new_size];
	 
	copy(base, new_base, new_size < stack_size ? new_size : stack_size);

	delete[] base;
	base = new_base;
	base_size = new_size;
}

void stack::init(int size) {
	int diff = base_size - size;

	if (diff <= 0) {
		resize(size * 8);
		next_item = base + size;
	}
	else {
		next_item += size - stack_size;
	}

	stack_size = size;
}

void stack::Push(int item) {
	init(stack_size + 1);
	*(next_item - 1) = item;
}

int stack::Pop() {
	if (stack_size == 0) {
		return -1;
	}

	int result = *(next_item - 1);
	init(stack_size - 1);

	return result;
}

int stack::size() const {
	return stack_size;
}

bool stack::is_empty() const {
	return stack_size == 0;
}

int stack::top() const {
	return *(next_item - 1);
}

class queue {
private:

	stack pop_stack;
	stack push_stack;

public:

	void Push(int);
	int Pop();
};

void queue::Push(int item) {
	push_stack.Push(item);
}

int queue::Pop() {
	if (pop_stack.is_empty()) {
		int size = push_stack.size();
		for (int i = 0; i < size; ++i) {
			pop_stack.Push(push_stack.Pop());
		}
	}

	int result = pop_stack.Pop();
	return result;
}

int main() {
	queue queue;

	int n = 0;
	std::cin >> n;

	for (int i = 0; i < n; ++i) {
		int command = 0;
		int value = 0;
		std::cin >> command >> value;

		switch (command) {
		case 2:
			if (queue.Pop() != value) {
				std::cout << "NO" << std::endl;
				return 0;
			}
			break;

		case 3:
			queue.Push(value);
			break;
		}
	}
	std::cout << "YES" << std::endl;
	return 0;
}
