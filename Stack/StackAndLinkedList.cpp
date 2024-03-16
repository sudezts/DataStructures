#include <iostream>
using namespace std;

class Node {
private:
	int data;
	Node* next;

	Node(int data) {
		this->data = data;
		this->next = nullptr;
	}

	friend class Stack;
};

class Stack {
private:
	Node* top;
	int size;

public:
	Stack() {
		this->top = nullptr;
		size = 0;
	}

	bool isEmpty() {
		if (top == nullptr) {
			return true;
		}
		else {
			return false;
		}
	}

	void push(int value) {
		Node* newNode = new Node(value);
		newNode->next = top;
		top = newNode;
		size++;
	}

	void pop() {
		if (top == nullptr) {
			return;
		}

		Node* temp = top;
		top = temp->next;
		delete temp;
		size--;
	}

	int getTop() {
		if (top == nullptr) {
			return -1;
		}
		else {
			return top->data;
		}
	}

	int getSize() {
		return size;
	}

	void displayStack() {
		if (top == nullptr) {
			return;
		}
		Node* temp = top;
		while (temp != nullptr) {
			cout << temp->data << " ";
			temp = temp->next;
		}
		cout << endl;
	}

	void swapStack(Stack* stack) {
		if (stack->isEmpty() or isEmpty()) {
			return;
		}
		Node* temp = top;
		top = stack->top;
		stack->top = temp;
	}

	void reverse() {
		Node* tmp = top;
		Stack* temp = new Stack();

		while (tmp != NULL) {
			temp->push(tmp->data);
			tmp = tmp->next;
		}
		top = temp->top;
		temp->top = tmp;
	}
};




int main() {
	Stack st1;
	st1.push(1);
	st1.push(3);
	st1.push(5);
	st1.push(7);
	st1.push(13);
	st1.pop();

	cout << "The first stack is : ";
	st1.displayStack();

	if (st1.getTop() == -1) {
		cout << "EMPTY!"<<endl;
	}
	else {
		cout << "The item on the top of the stack is " << st1.getTop() << endl;
	}

	Stack st2;
	st2.push(2);
	st2.push(4);
	st2.push(8);
	st2.push(16);
	st2.push(32);
	st2.push(64);
	st2.push(128);
	st2.pop();
	st2.pop();

	cout << "The second stack is : ";
	st2.displayStack();

	if (st2.getTop() == -1) {
		cout << "EMPTY!" << endl;
	}
	else {
		cout << "The item on the top of the stack is " << st2.getTop() << endl;
	}

	cout << "The size of first queue = " << st1.getSize() << endl;
	cout << "The size of second queue = " << st2.getSize() << endl;

	
	st1.swapStack(&st2);
	st1.displayStack();

	st1.reverse();
	st1.displayStack();
	
	st2.reverse();
	st2.displayStack();

}
*/

/*

#include <iostream>
#include <stack>
using namespace std;

int main() {
	stack<int>s1;
	int i;
	for (i = 1; i < 10; i++) {
		s1.push(i);
	}

	while (!s1.empty()) {
		cout << s1.top() << " ";
		s1.pop();
	}
}

