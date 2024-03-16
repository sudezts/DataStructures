#include <iostream>
using namespace std;

class Node { //This part includes necessary headers and defines a Node class.
	int key; //Each node in the doubly linked list has a key,
	string data; //data,
	Node* next; //a pointer to the next node (next),
	Node* prev; // and a pointer to the previous node (prev)

	Node(int key, string data) { //The constructor initializes a node with the provided key and data, setting next and prev pointers to nullptr.
		this->key = key;
		this->data = data;
		this->next = nullptr;
		this->prev = nullptr;
	}
	friend class Phonebook; //declares the Phonebook class as a friend, allowing it to access private members of the Node class.
};

class Phonebook {
private:
	Node* header; //points to the first node
	Node* tail; //points to the last node
	int s; //stores the size of the phonebook

public:
	Phonebook() { //The constructor initializes these pointers to nullptr and sets the size (s) to 0.
		this->header = nullptr;
		this->tail = nullptr;
		s = 0;
	}

	bool empty() { //checks the phonebook is empty or not
		if (header == nullptr) { // if the phonebook is empty by examining whether the header is nullptr. and return true.
			return true;
		}
		else { //otherwise return false. and phonebook is not empty.
			return false;
		}
	}

	Node* find(int key) { //searches for a node with the specified key in the phonebook.
		if (empty()) { //If the phonebook is empty, it returns nullptr.
			return nullptr;
		}
		Node* temp = header;
		while (temp != nullptr and temp->key != key) { //It uses a loop to traverse the list until it finds a node with the matching key or reaches the end.
			temp = temp->next;
		}
		if (temp == nullptr) { //f the node is found, it returns a pointer to that node
			return nullptr;
		}
		else { //otherwise, it returns nullptr.
			return temp;
		}
	}

	Node* find(string data) { //Similar to the previous function, find(string data) searches for a node with the specified data (name) in the phonebook.
		if (empty()) {
			return nullptr;
		}
		Node* temp = header;
		while (temp != nullptr and temp->data != data) {
			temp = temp->next;
		}
		if (temp == nullptr) {
			return nullptr;
		}
		else {
			return temp;
		}
	}



	void search(int key) { // displays information for a contact with the specified key if it exists, otherwise prints "Not Exist!".
		if (find(key) != nullptr) {
			Node* temp = find(key);
			cout << temp->data << " - " << temp->key << endl;
			cout << endl;
		}
		else {
			cout << "Not Exist!" << endl;
			cout << endl;
		}
	}

	void search(string name) { // Similar to the previous function, search(string name) displays information for a contact with the specified name if it exists.
		if (find(name) != nullptr) {
			Node* temp = find(name);
			cout << temp->key << " - " << temp->data << endl;
			cout << endl;
		}
		else {
			cout << "Not Exist!" << endl;
			cout << endl;
		}
	}

	void put(int key, string data) { //adds a new contact to the phonebook.
		Node* newNode = new Node(key, data);
		if (empty()) { //If the phonebook is empty, it sets both the header and tail to the new node.
			header = newNode;
			tail = newNode;
			s++;
			return;
		}
		else {
			//If the key or data already exists, it prints a message indicating the existing relationship.
			if (find(key) != nullptr) {
				Node* t1 = find(key);
				cout << t1->key << " this number belongs " << t1->data << endl;
				return;
			}
			else if (find(data) != nullptr) {
				Node* t2 = find(data);
				cout << t2->data << " have this number :" << t2->key << endl;
				return;
			}
			//Otherwise, it adds the new node to the end of the phonebook
			tail->next = newNode; //updates the tail pointer
			newNode->prev = tail;
			tail = newNode;
			s++; //increments the size
			alphabeticalOrder(); // and then calls alphabeticalOrder to maintain alphabetical order.
		}
	}

	void erase(int key) { // removes a contact from the phonebook based on the provided key.
		//If the phonebook is empty or the key is not found, it returns without doing anything.
		if (empty()) {
			return;
		}
		if (find(key) == nullptr) {
			return;
		}
		//Oterwise,
		else {
			s--;
			Node* temp = find(key); //firstly we shoul check where is our number
			//If the node to be removed is the header or tail, it adjusts the pointers accordingly.
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

			else { //Otherwise, it adjusts pointers of neighboring nodes and deletes the node.
				temp->prev->next = temp->next;
				temp->next->prev = temp->prev;
				temp->next = nullptr;
				temp->prev = nullptr;
				delete temp;
				return;
			}
		}
	}

	void update(string name, int newNumber) { // updates the phone number for a contact with the specified name.
		//If the phonebook is empty or the name is not found, it returns without doing anything.
		if (empty()) {
			return;
		}

		if (find(name) == nullptr) {
			return;
		}
		//Otherwise,
		else {
			Node* temp = find(name); // find the number in the map
			temp->key = newNumber; //it updates the key (phone number) for the found contact.
			return;
		}
	}

	void contactList(string first, string last) { //displays the contact list between two specified names.
		//If the phonebook is empty or at least one of names are not found, it returns without doing anything.
		if (empty()) {
			return;
		}

		if (find(first) == nullptr or find(last) == nullptr) {
			return;
		}
		//Otherwise,
		else {
			Node* frst = find(first); //find first name
			Node* lst = find(last); //find second name

			Node* temp = frst->next;
			cout << "~" << "Contact List Between " << first << " and " << last << "~" << endl;

			while (temp != lst) { //this loop prints the contact list between the specified names.
				cout << temp->data << " - " << temp->key << endl;
				temp = temp->next;
			}
			cout << endl;
		}
	}

	int size() { //returns the size of the phonebook.
		return s;
	}

	void display() { // prints the entire phonebook.
		if (empty()) { //If the phonebook is empty, it returns without doing anything.
			return;
		}
		//Otherwise, it traverses the list and prints each contact's data and key.
		Node* temp = header;
		while (temp != nullptr) {
			cout << temp->data << "," << temp->key << endl;

			temp = temp->next;
		}

		cout << endl;
	}

	void alphabeticalOrder() {
		if (empty()) { // If the phonebook is empty, it returns without doing anything.
			return;
		}
		Node* current = header; //Initializes a pointer current to the header, which represents the current node being compared.
		Node* index = nullptr; //Initializes a pointer index to nullptr, which will be used to iterate through the remaining nodes to compare with the current node.
		//Declares temporary variables to hold the data and key of nodes during the swapping process.
		string tempData;
		int tempKey;

		while (current != nullptr) { //iterates through each node in the linked list.
			index = current->next;

			while (index != nullptr) { // iterates through the remaining nodes in the list to compare with the current node.
				if (current->data > index->data) {//Checks if the name (data) of the current node is lexicographically greater than the name of the next node (index). If true, it means that the names are out of order.
					tempData = current->data; //Stores the name of the current node.
					tempKey = current->key; //Stores the key of the current node.
					current->data = index->data; //Swaps the name of the current node with the name of the next node.
					current->key = index->key; //Swaps the key of the current node with the key of the next node.
					index->data = tempData; // Restores the name of the next node with the stored name of the current node.
					index->key = tempKey; // Restores the key of the next node with the stored key of the current node.
				}
				index = index->next;
			}
			current = current->next; //After the inner loop, the outer loop moves to the next node in the linked list
		}
	}

};

int main() {
	Phonebook m;

	m.put(5484635, "Burak");
	m.put(735485, "Durhan");
	m.put(244441, "EX");
	m.put(818396, "Aleyna");
	m.put(554744, "Emre");
	m.put(124, "Babam");
	m.put(55147, "Bg");
	m.put(74854, "Dilan");
	m.put(2336, "Cemre");
	m.put(81541, "Ahmet");
	m.put(5424, "Ela");
	m.put(12441, "Annem");

	m.display();

	m.search(74854);

	m.search(486548);

	m.erase(244441);

	m.display();

	m.erase(3);

	m.display();

	m.update("Aleyna", 296953452);

	m.display();

	m.contactList("Aleyna", "Dilan");

	cout << m.size() << endl;
}
