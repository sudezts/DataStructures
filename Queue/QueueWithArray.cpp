#include <iostream>
using namespace std;

const int MAX_SIZE = 10;

class Queue {
private:
	int arr[MAX_SIZE];
	int front;
	int rear;
	int size;

public:
	Queue() {
		front = -1;
		rear = -1;
		size = 0;
	}

	bool empty() {
		if (front == -1 and rear == -1) {
			return true;
		}
		return false;
	}

	bool full() {
		if (rear == MAX_SIZE - 1) {
			return true;
		}
		return false;
	}

	void enqueue(int value) {
		if (full()) {
			return;
		}
		else {
			if (front == -1)
				front = 0;
				rear++;
				arr[rear] = value;
				size++;
		}
	}

	void dequeue() {
		if (empty()) {
			return;
		}
		else {
			front++;
			size--;
		}
	}

	int getFront() {
		if (empty()) {
			return -1;
		}
		else {
			return arr[front];
		}
	}

	int getRear() {
		if (empty()) {
			return -1;
		}
		else {
			return arr[rear];
		}
	}

	int getSize() {
		return size;
	}

	void displayQueue() {
		if (empty()) {
			return;
		}
		else {
			int i = front;
			while (i <= rear) {
				i++;
				cout << arr[i] << " ";
			}
		}
	}
};

int main() {
	Queue q1;
	q1.enqueue(1);
	q1.enqueue(3);
	q1.enqueue(5);
	q1.enqueue(7);
	q1.enqueue(13);
	q1.dequeue();

	cout << "The first queue is : ";
	q1.displayQueue();

	cout << "The item at front of the queue is " << q1.getFront() << endl;
	cout << "The item at rear of the queue is " << q1.getRear() << endl;

	Queue q2;
	q2.enqueue(2);
	q2.enqueue(4);
	q2.enqueue(8);
	q2.enqueue(16);
	q2.enqueue(32);
	q2.enqueue(64);
	q2.enqueue(128);
	q2.dequeue();
	q2.dequeue();

	cout << "The second queue is : ";
	q2.displayQueue();

	if (!q1.empty() and q2.empty()) {
		cout << "The size of first queue = " << q1.getSize() << endl << "The size of second queue = " << q2.getSize();
	}

	return 0;

}
