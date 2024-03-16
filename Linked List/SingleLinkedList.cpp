#include <iostream>
#include <string>
using namespace std;

class Node {
private:
	int data;
	Node* next;

	Node(int data) {

		this->data = data;
		this->next = nullptr;
	}
	friend class LinkedList;
};

class LinkedList {
private:
	Node* head;
	int size;

public:

	LinkedList() {
		this->head = nullptr;
		size = 0;
	}

	void insertAtBeginning(int data) {
		Node* newNode = new Node(data);
		newNode->next = head;
		head = newNode;
		size++;
	}

	void insertAtEnd(int data) {
		Node* newNode = new Node(data);
		size++;
		if (head == nullptr) {
			head = newNode;
			return;
		}
		
		Node* temp = head;
		while (temp->next != nullptr) {
			temp = temp->next;
		}
		temp->next = newNode;
		newNode->next = nullptr;
	}

	void insertPosition(int position, int data) {
		Node* newNode = new Node(data);
		if (head == nullptr) {
			return;
		}
		int count = 1;
		Node* temp = head;
		while (count != position-1 and temp->next != nullptr) {
			temp = temp->next;
			count++;
		}
		if (position <= size and position >= 1) {
			if (position == 1) {
				insertAtBeginning(data);
			}
			else {
				newNode->next = temp->next;
				temp->next = newNode;
				size++;
			}
		}
		else {
			insertAtEnd(data);
		}

	}

	void removeAtBeginning() {
		if (head == nullptr) {
			return;
		}

		Node* temp = head;
		head = temp->next;
		delete temp;
		size--;
	}

	void removeAtEnd() {
		if (head == nullptr) {
			return;
		}

		Node* temp = head;
		while (temp->next->next != nullptr) {
			temp = temp->next;
		}
		Node* toRemove = temp->next;
		delete toRemove;
		temp->next = nullptr;
		size--;
	}

	void removePosition(int position) {
		if (head == nullptr) {
			return;
		}
		int count = 1;
		Node* temp = head;

		while (count != position and temp->next != nullptr) {
			temp = temp->next;
			count++;
		}
		if (position >= 1 and position <= size) {
			if (position == 1) {
				removeAtBeginning();
			}
			else if (temp->next==nullptr) {
				removeAtEnd();
			}
			else {
				Node* prevNode = head;
				while (prevNode->next != temp) {
					prevNode = prevNode->next;
				}
				prevNode->next = temp->next;
				delete temp;
				size--;
			}
		}

		else {
			return;
		}

	}

	int listsize() {
		cout << size << endl;
		return size;
	}

	void search(int data) {
		if (head == nullptr) {
			return;
		}

		Node* temp = head;
		while (temp->data != data && temp->next!=nullptr) {
			temp = temp->next;
		}

		if (temp->data == data) {
			cout << data << " is in the list." << endl;
		}
		else {
			cout << data << " is not in the list." << endl;
		}
	}

	void swaplist(LinkedList* list) {
		Node* temp = head;
		head = list->head;
		list->head = temp;
	}

	void display() {
		if (head == nullptr) {
			return;
		}

		Node* temp = head;
		while (temp != nullptr) {
			cout << temp->data << " ";
			temp = temp->next;
		}
		cout << endl;
	}
};

int main() {
	LinkedList list1;

	for (int i = 6; i >= -1; i--) {
		list1.insertAtBeginning(i);
	}
	for (int i = 7; i <= 12; i++) {
		list1.insertAtEnd(i);
	}

	list1.insertPosition("Before", 1, -2);
	list1.insertPosition("After", 15, 13);
	list1.insertPosition("after", 6, 7);
	list1.insertPosition("before", 7, 6);

	list1.display();
	list1.listsize();

	list1.removeAtBeginning();
	list1.removeAtBeginning();
	list1.removeAtEnd();
	list1.removeAtEnd();
	list1.removePosition(6);
	list1.removePosition(5);
	list1.removePosition(1);
	list1.removePosition(11);
	
	cout << "List 1: ";
	list1.display();
	list1.listsize();

	LinkedList list2;

	for (int i = 1; i <= 10; i++) {
		list2.insertAtBeginning(i);
	}

	cout << "list 2: ";
	list2.display();

	list2.swaplist(&list1);

	cout << "List 1: ";
	list1.display();

	cout << "List 2: ";
	list2.display();

	return 0;
}
