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
	friend class CircularLinkedList;
};

class CircularLinkedList {
private:
	Node* head;
	int size;

public:

	CircularLinkedList() {
		this->head = nullptr;
		size = 0;
	}

	void insertAtBeginning(int data) {
		Node* newNode = new Node(data);
		size++;
		if (head == nullptr) {
			head = newNode;
			newNode->next = head;
		}
		else {
			newNode->next = head;

			Node* temp = head;

			while (temp->next != head) {
				temp = temp->next;
			}
			temp->next = newNode;
			head = newNode;
		}
	}

	void insertAtEnd(int data) {
		Node* newNode = new Node(data);
		if (head == nullptr) {
			head = newNode;
			newNode->next = newNode;
		}
		else {
			Node* temp = head;
			while (temp->next != head) {
				temp = temp->next;
			}
			newNode->next = head;
			temp->next = newNode;
		}
		size++;
	}

	void insertPosition(string location, int position, int data) {
		if (head == nullptr) {
			return;
		}
		Node* newNode = new Node(data);
		Node* temp = head;
		int count = 1;

		while (count != position && temp->next != head) {
			temp = temp->next;
			count++;
		}
		if (position >= 1 and position <= size) {
			if (location == "before" or location == "Before" or location == "BEFORE") {
				if (position == 1) {
					insertAtBeginning(data);
				}
				else {
					Node* prevNode = head;
					while (prevNode->next != temp) {
						prevNode = prevNode->next;
					}
					newNode->next = temp;
					prevNode->next = newNode;
					size++;
				}
			}

			else if (location == "after" or location == "After" or location == "AFTER") {
				if (temp->next == head) {
					insertAtEnd(data);
				}
				else {
					newNode->next = temp->next;
					temp->next = newNode;
					size++;
				}
			}
		}
		else {
			return;
		}
	}

	void removeAtBeginning() {
		if (head == nullptr) {
			return;
		}

		Node* toRemove = head;
		if (toRemove->next == head) {
			delete toRemove;
			head = nullptr;
		}
		else {

			Node* temp = head;

			while (temp->next != head) {
				temp = temp->next;
			}
			head = toRemove->next;
			temp->next = head;
			delete toRemove;
		}
		size--;
	}

	void removeAtEnd() {
		if (head == nullptr) {
			return;
		}
		Node* temp = head;
		if (temp->next == head) {
			delete temp;
			head = nullptr;
		}
		else {
			while (temp->next->next != head) {
				temp = temp->next;
			}
			Node* toRemove = temp->next;
			delete toRemove;
			temp->next = head;

		}
		size--;
	}

	void removePosition(int position) {
		if (head == nullptr) {
			return;
		}
		if (position >= 1 and position <= size) {
			Node* temp = head;
			int count = 1;
			while (count != position and temp->next != head) {
				temp = temp->next;
				count++;
			}
			if (position == 1) {
				removeAtBeginning();
			}
			else if (temp->next == head) {
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
	}

	void search(int data) {
		if (head == nullptr) {
			return;
		}
		Node* temp = head;

		while (temp->data != data and temp->next != head) {
			temp = temp->next;
		}

		if (temp->data == data) {
			cout << data << " is in the list." << endl;
		}

		else {
			cout << data << " is not in the list." << endl;
		}

	}

	void swapList(CircularLinkedList* list) {
		Node* temp = head;
		head = list->head;
		list->head = temp;
	}

	int listsize() {
		cout << "Size: " << size << endl;
		return size;
	}


	void display() {
		if (head == nullptr) {
			return;
		}
		cout << head->data << " ";
		Node* temp = head->next;
		while (temp != head) {
			cout << temp->data << " ";
			temp = temp->next;
		}
		cout << endl;
	}
};

int main() {
	CircularLinkedList list1;

	for (int i = 6; i >= -1; i--) {
		list1.insertAtBeginning(i);
	}

	for (int i = 7; i <= 12; i++) {
		list1.insertAtEnd(i);
	}

	list1.removeAtBeginning();
	list1.removeAtBeginning();
	list1.removeAtEnd();
	list1.removeAtEnd();
	list1.insertPosition("after", 3, 6);
	list1.insertPosition("before", 4, 7);
	list1.removePosition(5);
	list1.removePosition(4);

	cout << "List 1: ";
	list1.display();
	list1.listsize();
	list1.search(11);

	CircularLinkedList list2;

	for (int i = 10; i >= 0; i--) {
		list2.insertAtEnd(i);
	}

	cout << "List 2: ";
	list2.display();

	cout << "~after swap~" << endl;

	list2.swapList(&list1);
	cout << "List 1: ";
	list1.display();
	cout << "List 2: ";
	list2.display();




	return 0;
}
