#include <iostream>
using namespace std;

class Node {
private: //attributes
	int data;
	Node* next;

	Node(int data) { //constructor

		this->data = data; // value in the node
		this->next = nullptr; // a pointer to reach for the next node
	}
	friend class Queue;
	friend class Stack;
};

//Queue Class
class Queue { // provide queue class access
private:
	Node* front; // pointer to the front of the queue
	Node* rear; // pointer to the rear of the queue
	int size; // a variable for size of the queue
public:
	Queue() { // empty queue constructor
		this->front = nullptr; // initially front is null
		this->rear = nullptr; // initially rear is null
		size = 0; // initially size is 0
	}
	bool isEmpty() { // to check queue is empty or not
		if (front == nullptr) { // if front is null then queue is empty
			return true;
		}
		else { // if front is not null then queue is not empty
			return false;
		}
	}
	void enqueue(int data) { // to add a new node to queue
		Node* newNode = new Node(data); // create a new node
		if (front == nullptr)// if queue is empty, new node is will front and rear.
		{
			front = newNode;// front will be new node
			rear = newNode;// rear will be new node
			size++; // increase size of the queue, because we added new node to the queue
			return;
		}

		Node* temp = front; // to navigate between boxes
		while (temp->next != nullptr) // move over the nodes in the list
		{
			temp = temp->next;
		}
		temp->next = newNode; // connect rear with new node
		newNode->next = nullptr; // new node point null
		rear = newNode; // our new rear will be new node
		size++; //increase size of the queue, because we added new node to the queue
	}

	void dequeue() { // to delete a node to queue
		if (front == nullptr) { // if queue is empty, we can't delete anything.
			return;
		}
		Node* temp = front; // for save the front.
		front = front->next; // skip over old front
		delete temp; // delete old front
		size--; // decrease size of the queue, because we deleted a node to the queue

	}

	int getFront() { // to display current front
		if (front == nullptr) { // if queue is empty. queue have no front
			return -1;
		}
		else { // if queue is not empty. queue have a front.
			return front->data;
		}
	}

	int getRear() { // to display current rear
		if (rear == nullptr) { // if queue is empty. queue have no rear
			return -1;
		}
		else { // if queue is not empty. queue have a rear.
			return rear->data;
		}
	}

	int getSize() { // to display current size
		return size;
	}

	void displayQueue() { //  to display datas
		if (front == nullptr) { // if queue is empty, we don't have anything for display.
			return;
		}
		Node* temp = front; // for navigate between nodes
		while (temp != nullptr) // move over the nodes in the queue
		{
			cout << temp->data << " "; //to print the data of the node pointed by temp to the screen
			temp = temp->next;
		}
		cout << endl;
	}
};

//Stack Class
class Stack { // provide stack class access
private:
	Node* top; // pointer to the top of the queue
	int size; // a variable for size of the queue

public:
	Stack() { // empty stack constructor
		this->top = nullptr; // initially top is null
		size = 0; // initially size is 0
	}
	bool isEmpty() { // to check stack is empty or not
		if (top == nullptr) { // if top is null then stack is empty
			return true;
		}
		else { // if top is not null then stack is not empty
			return false;
		}
	}
	void push(int data) { // to add a new node to stack
		Node* newNode = new Node(data); // create a new node
		newNode->next = top; // connect new node with stack
		top = newNode; //our new top will be new node
		size++; //increase size of the stack, because we added new node to the stack
	}

	void pop() {
		if (top == nullptr) { // if stack is empty, we can't delete anything.
			return;
		}
		else {
			Node* temp = top; // for save the top.
			top = temp->next; // skip over old top
			delete temp; // delete old top
			size--; // decrease size of the stack, because we deleted a node to the stack
		}
	}

	int getTop() { // to display current top
		if (top == nullptr) { // if stack is empty. queue have no top
			return -1;
		}
		else {  // if stack is not empty. queue have top
			return top->data;
		}
	}

	int getSize() { // to display current size
		return size;
	}

	void displayStack() { //  to display datas
		if (top == nullptr) { // if stack is empty, we don't have anything for display.
			return;
		}
		Node* temp = top; // for navigate between nodes
		while (temp != nullptr) { // move over the nodes in the stack
			cout << temp->data << " "; //to print the data of the node pointed by temp to the screen
			temp = temp->next;
		}
		cout << endl;
	}
};


void swap(Stack& stack, Queue& queue) { // to swap a stack and a queue
	if (stack.isEmpty() and queue.isEmpty()) { // if stack and queue are empty in same time
		return;
	}
	Queue* temp1 = new Queue(); // to save queue's datas
	Queue* tempQueue = new Queue(); // to queue's datas move over tempStack
	Stack* temp2 = new Stack(); // to queue is top be stack's top
	Stack* temp3 = new Stack(); // to save stack's datas
	Stack* tempStack = new Stack(); // to save queue's datas for temp time

	*tempQueue = queue; // to tempQueue be same with queue
	while (!tempQueue->isEmpty()) { // to pass the tempQueue's data onto the tempStack
		tempStack->push(tempQueue->getFront()); // to add front node of tempQueue to tempStack
		tempQueue->dequeue(); // to delete the current front so that the next node becomes the new front
	}

	while (!tempStack->isEmpty()) { // to queue's front be stack's top
		temp2->push(tempStack->getTop()); // to add top of tempStack to temp2
		tempStack->pop(); // to delete the current top so that the next node becomes the new top
	}
	*temp3 = stack; // to temp3 be same with stack
	stack = *temp2; // to stack be same with queue
	*temp2 = *temp3; // to temp2 be same with stack

	while (!temp2->isEmpty()) { // to pass the temp2's data onto the temp1
		temp1->enqueue(temp2->getTop()); // to add top node of temp2 to temp1
		temp2->pop(); // to delete the current top so that the next node becomes the new top
	}

	queue = *temp1; // to queue be same with stack
}

int main() {
	Queue q; //create a queue by named q
	Stack s; //cerate a stack by named s
	q.enqueue(1);// add 1 in queue this will be front
	q.enqueue(2);// add 2 after 1
	q.enqueue(3);// add 3 after 2
	q.enqueue(4);// add 4 after 3
	q.enqueue(5);// add 5 after 4 this will be rear

	cout << "Stack: ";
	s.displayStack(); // display current stack in output

	cout << endl;

	cout << "Queue: ";
	q.displayQueue(); //display current queue in output

	swap(s, q); // change stack and queue

	cout << "Stack: ";
	s.displayStack(); // display elements our new sttack

	cout << "Queue: ";
	q.displayQueue(); //display elements our new queue

	return 0;
}
