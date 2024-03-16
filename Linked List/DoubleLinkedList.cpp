#include <iostream>
#include <string>
using namespace std;

class Node {
private:
	int data;
	Node* next;
	Node* prev;

	Node(int data) {

		this->data = data;
		this->next = nullptr;
		this->prev = nullptr;
	}
	friend class LinkedList;
};

class LinkedList {
private:
	Node* head;

public:

	LinkedList() {
		this->head = nullptr;
	}

	void insertAtBeginning(int data) {
		Node* newNode = new Node(data);

		if (head == nullptr) {
			head = newNode;
			return;
		}

		newNode->next = head;
		head->prev = newNode;
		newNode->prev = nullptr;
		head = newNode;
	}

	void insterAtEnd(int data) {
		Node* newNode = new Node(data);
		if (head == nullptr) {
			head = newNode;
			return;
		}

		Node* temp = head;
		while (temp->next != nullptr) {
			temp = temp->next;
		}

		newNode->prev = temp;
		temp->next = newNode;
		newNode->next = nullptr;
	}

	void insertSpecific(string location, int key, int data) {
		Node* newNode = new Node(data);
		if (head == nullptr) {
			head = newNode;
			return;
		}
		Node* temp = head;
		while (temp->next != nullptr and temp->data != key) {
			temp = temp->next;
		}
		if (location == "after" or location == "After" or location == "AFTER") {
			if (temp->next == nullptr) {
				insterAtEnd(data);
			}
			else {
				newNode->prev = temp;
				newNode->next = temp->next;
				temp->next->prev = newNode;
				temp->next = newNode;
			}
		}
		else if (location == "before" or location == "Before" or location == "BEFORE") {
			if (temp==head) {
				insertAtBeginning(data);
			}
			else {
				newNode->next = temp;
				newNode->prev = temp->prev;
				temp->prev->next = newNode;
				temp->prev = newNode;
			}
		}




	}

	void insertPosition(string location, int position, int data) {
		Node* newNode = new Node(data);
		if (head == nullptr) {
			head == newNode;
			return;
		}
		int count = 1;
		Node* temp1 = head;
		Node* temp2 = head;
		int listMaxPosition = 1;
		while (temp1->next != nullptr) {
			listMaxPosition++;
			temp1 = temp1->next;
		}


		if (position <= listMaxPosition) {
			while (count != position && temp2->next != nullptr) {
				temp2 = temp2->next;
				count++;
			}
			if (location == "Before" or location == "BEFORE" or location == "before") {
				if (position == 1) {
					insertAtBeginning(data);
				}
				else {
					newNode->next = temp2;
					newNode->prev = temp2->prev;
					temp2->prev->next = newNode;
					temp2->prev = newNode;
				}
			}
			if (location == "After" or location == "AFTER" or location == "after") {
				if (position == listMaxPosition) {
					insterAtEnd(data);
				}
				else {
					newNode->prev = temp2;
					newNode->next = temp2->next;
					temp2->next->prev = newNode;
					temp2->next = newNode;
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
		Node* temp = head;
		head = temp->next;
		delete temp;
		head->prev = nullptr;
	}

	void removeAtEnd() {
		if (head == nullptr) {
			return;
		}
		Node* temp = head;

		while (temp->next->next != nullptr) {
			temp = temp->next;
		}
		delete temp->next;
		temp->next = nullptr;
	}

	void removeSpecific(int key) {
		if (head == nullptr) {
			cout << "Given node is not found in the list";
			return;
		}

		Node* temp = head;

		while (temp->next != nullptr and temp->data != key) {
			temp = temp->next;
		}
		if (temp->data == key) {
			if (temp == head) {
				removeAtBeginning();
			}
			else if (temp->next == nullptr)
			{
				removeAtEnd();
			}
			else {
				temp->prev->next = temp->next;
				temp->next->prev = temp->prev;
				delete temp;
			}
		}


	}

	void removePosition(int position) {
		if (head == nullptr) {
			return;
		}
		if (position == 1) {
			removeAtBeginning();
		}
		else {
			Node* tempP = head;
			Node* temp = head;
			int count = 1;
			int listMaxPosition = 1;

			while (tempP->next != nullptr) {
				tempP = tempP->next;
				listMaxPosition++;
			}

			while (count != position and temp->next != nullptr) {
				temp = temp->next;
				count++;
			}
			if (count <= listMaxPosition) {
				if (count == listMaxPosition) {
					removeAtEnd();
				}
				else {
					temp->prev->next = temp->next;
					temp->next->prev = temp->prev;
					delete temp;
				}
			}
			else {
				return;
			}
		}

	}

	void size() {
		if (head == nullptr) {
			cout << "Size: 0";
			return;
		}

		Node* temp = head;
		int count = 0;

		while (temp != nullptr) {
			count++;
			temp = temp->next;
		}

		cout << "Size: " << count << endl;

	}

	void search(int key) {
		if (head == nullptr) {
			cout << "This list is a empty list.";
			return;
		}
		Node* temp = head;
		while (temp->next != nullptr and temp->data != key) {
			temp = temp->next;
		}
		if (temp->data == key) {
			cout << key << " is in the list." << endl;
		}
		else {
			cout << key << " is not in the list." << endl;
		}
	}

	void printList() {
	    if (head == nullptr) {
			return;
		}
		Node* temp = head;
		while (temp != nullptr)
		{
			cout << temp->data << " ";
			temp = temp->next;
		}
		cout << endl;
	}
};

int main() {
	LinkedList list;

	list.insertAtBeginning(7);
	list.insertSpecific("After", 7, 3);
	list.insertPosition("After", 2, 12);
	list.insterAtEnd(4);
	list.insertSpecific("BEFORE", 3, 1);
	list.insertPosition("after", 2, 5);

	list.printList();
	list.size();
	list.search(3);


	return 0;
}
