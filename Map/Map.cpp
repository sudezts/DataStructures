#include <iostream>
using namespace std;

class Node {
	int key;
	string data;
	Node* next;
	Node* prev;

	Node(int key, string data) {
		this->key = key;
		this->data = data;
		this->next = nullptr;
		this->prev = nullptr;
	}
	friend class Map;
};

class Map {
private:
	Node* header;
	Node* tail;
	int s;

public:
	Map() {
		this->header = nullptr;
		this->tail = nullptr;
		s = 0;
	}

	bool empty() {
		if (header == nullptr) {
			return true;
		}
		else {
			return false;
		}
	}

	bool check(int key) {
		if (empty()) {
			return false;
		}
		Node* temp = header;
		while (temp != nullptr and temp->key != key) {
			temp = temp->next;
		}
		if (temp == nullptr) {
			return false;
		}
		else {
			return true;
		}
	}

	void find(int key) {
		if (check(key)) {
			Node* temp = header;
			while (temp->key != key) {
				temp = temp->next;
			}
			cout << "[(" << temp->key << "," << temp->data << ")]" << endl;
		}
		else {
			cout << "end" << endl;
		}
	}

	void put(int key, string data) {
		if (check(key)==true) {
			return;
		}
		Node* newNode = new Node(key, data);
		s++;
		if (empty()) {
			header = newNode;
			tail = newNode;
			return;
		}

		tail->next = newNode;
		newNode->prev = tail;
		tail = newNode;
	}

	void erase(int key) {
		if (empty()) {
			return;
		}
		if (!check(key)) {
			return;
		}
		s--;
		Node* temp = header;

		while (temp->key != key) {
			temp = temp->next;
		}

		if (temp == header) {
			header = header->next;
			header->prev = nullptr;
			delete temp;
			return;
		}

		else if (temp == tail) {
			tail = tail->prev;
			tail->next = nullptr;
			delete temp;
			return;
		}

		else {
			temp->prev->next = temp->next;
			temp->next->prev = temp->prev;
			temp->next = nullptr;
			temp->prev = nullptr;
			delete temp;
			return;
		}
	}

	int size() {
		return s;
	}

	void begin() {
		if (empty()) {
			return;
		}
		cout << "[(" << header->key << "," << header->data << ")]" << endl;
	}

	void end() {
		if (empty()) {
			return;
		}
		cout << "[(" << tail->key << "," << tail->data << ")]" << endl;
	}

	void display() {
		if (empty()) {
			return;
		}
		Node* temp = header;
		while (temp != nullptr) {
			cout << "[(" << temp->key << "," << temp->data << ")] ";
			if (temp->next != nullptr) {
				cout << ", ";
			}
			temp = temp->next;
		}

		cout << endl;
	}


};

int main() {
	Map m;

	m.put(5, "A");
	m.put(7, "B");
	m.put(2, "C");
	m.put(8, "D");
	m.put(5, "E");

	m.display();

	m.find(7);

	m.find(6);

	m.erase(2);

	m.display();

	m.erase(3);

	m.display();

	cout << m.size() << endl;

	m.begin();

	m.end();
}
