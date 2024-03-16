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
	friend class Queue;
};

class Queue {
private:
	Node* front;
	Node* rear;
	int size;
public:
	Queue () {
		this->front = nullptr;
		this->rear = nullptr;
		size = 0;
	}

	bool isEmpty() {
		if (front == nullptr) {
			return true;
		}
		else {
			return false;
		}
	}

	void enqueue(int value) {
		Node* newNode = new Node(value);
		size++;
		if (front == nullptr)
		{
			front = newNode;
			rear = newNode;
			return;
		}

		Node* temp = front;
		while (temp->next != nullptr)
		{
			temp = temp->next;
		}
		temp->next = newNode;
		newNode->next = nullptr;
		rear = newNode;
		
	}

	void dequeue() {
		if (front == nullptr) {
			return;
		}
		Node* temp = front;
		front = front->next;
		delete temp;
		size--;

	}

	int getFront() {
		if (front == NULL) {
			return -1;
		}
		else {
			return front->data;
		}
	}

	int getRear() {
		if (rear == NULL) {
			return -1;
		}
		else {
			return rear->data;
		}
	}

	void swapQueue(Queue* queue) {
		Node* temp = front;
		front = queue->front;
		queue->front = temp;
	}

	int getSize() {
		return size;
	}

	void displayQueue() {
		if (front==nullptr) {
			return;
		}
		Node* temp = front;
		while (temp != nullptr)
		{
			cout << temp->data << " ";
			temp = temp->next;
		}
		cout << endl;
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

	
	if (q1.getFront() == -1) {
		cout << "EMPTY" << endl;
	}
	else {
		cout << "The item at front of the queue is " << q1.getFront() << endl;
	}
	if (q1.getRear() == -1) {
		cout << "EMPTY" << endl;
	}
	else {
		cout << "The item at rear of the queue is " << q1.getRear() << endl;
	}

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
	
	cout << "The size of first queue = " << q1.getSize() << endl << "The size of second queue = " << q2.getSize();

	return 0;
}
