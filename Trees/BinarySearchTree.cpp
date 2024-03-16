
#include <iostream>
using namespace std;

class Node {
public:
	int data;
	Node* next;
	Node* prev;

	Node(int data) {
		this->data = data;
		this->next = nullptr;
		this->prev = nullptr;
	}
	friend class BinarySearchTree;
	friend class Queue;
	friend class Stack;
};

class Queue {
private:
	class QueueNode {
	public:
		Node* data;
		QueueNode* next;
	};

	QueueNode* front;
	QueueNode* rear;
public:
	Queue() {
		front = nullptr;
		rear = nullptr;
	}

	void enqueue(Node* node) {
		QueueNode* newNode = new QueueNode;
		newNode->data = node;
		newNode->next = nullptr;

		if (rear == nullptr) {
			front = newNode;
			rear = newNode;
		}
		else {
			rear->next = newNode;
			rear = newNode;
		}
	}

	Node* dequeue() {
		if (front == nullptr) {
			return NULL;
		}

		QueueNode* temp = front;
		Node* data = temp->data;

		front = front->next;
		if (front == nullptr) {
			rear = nullptr;
		}

		delete temp;
		return data;
	}

	bool isEmpty() {
		if (front == nullptr) {
			return true;
		}
		else {
			return false;
		}
	}
};

class Stack {
private:
	class StackNode {
	public:
		Node* data;
		StackNode* next;
	};

	StackNode* top;
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
	void push(Node* node) {
		StackNode* newNode = new StackNode;
		newNode->data = node;
		newNode->next = top;
		top = newNode;
		size++;
	}

	Node* pop() {
		if (top == nullptr) {
			return NULL;
		}
		else {
			StackNode* temp = top;
			Node* data = temp->data;
			top = temp->next;
			delete temp;
			size--;
			return data;
		}
	}

	Node* peek() {
		return top->data;
	}

	int getSize() {
		return size;
	}
};

class BinarySearchTree {
public:
	Node* root;
	int nSize;
public:
	BinarySearchTree() {
		this->root = nullptr;
		nSize = 0;
	}
	friend class Queue;
	friend class Stack;

	bool isEmpty() {
		if (root == nullptr)
			return true;
		else
			return false;
	}

	bool isLeafNode(Node* node) {
		if (node->next == nullptr and node->prev == nullptr) {
			return true;
		}
		else {
			return false;
		}
	}

	bool isParentNode(Node* node) {
		if (!isLeafNode(node))
			return true;
		else
			return false;
	}

	Node* findParent(Node* node) {
		if (node == root) {
			return NULL;
		}
		Node* tmp = NULL;
		Node* temp = root;
		while (temp != node) {
			if (temp->data < node->data) {
				tmp = temp;
				temp = temp->next;
			}
			else if (temp->data > node->data) {
				tmp = temp;
				temp = temp->prev;
			}
		}

		return tmp;
	}

	Node* findLeftChild(Node* node) {
		if (isParentNode(node) == true and node->prev != nullptr) {
			return node->prev;
		}
		else {
			return NULL;
		}
	}

	Node* findRightChild(Node* node) {
		if (isParentNode(node) == true and node->next != nullptr) {
			return node->next;
		}
		else {
			return NULL;
		}
	}

	Node* findNode(Node* node) {
		if (node == root) {
			return root;
		}
		else {
			Node* temp = root;
			while (temp != node and temp != nullptr) {
				if (node->data < temp->data) {
					temp = temp->prev;
				}
				else if (node->data > temp->data) {
					temp = temp->next;
				}
			}
			if (temp == nullptr) {
				return NULL;
			}
			else {
				return temp;
			}

		}
	}

	int maxDepth() {
		if (root == nullptr) {
			return 0;
		}
		int depth = 0;
		Stack* s1 = new Stack();
		Stack* s2 = new Stack();
		Node* r = root;
		s1->push(r);
		while (!s1->isEmpty()) {
			r = s1->peek();
			if (!s2->isEmpty() && r == s2->peek()) {
				if (s2->getSize() > depth)
					depth = s2->getSize();
				s2->pop();
				s1->pop();
			}
			else {
				s2->push(r);
				if (r->next != nullptr)
					s1->push(r->next);
				if (r->prev != nullptr)
					s1->push(r->prev);
			}
		}

		return depth;
	}

	int nodeHeight(Node* node) {
		if (node == root) {
			return 0;
		}
		else {
			Node* check = findNode(node);
			if (check != NULL) {
				Node* temp = root;
				int h = 0;
				while (temp != node) {
					if (node->data < temp->data) {
						temp = temp->prev;
						h++;
					}
					else if (node->data > temp->data) {
						temp = temp->next;
						h++;
					}
				}
				return h;
			}
			else {
				return -1;
			}
		}
	}

	int nodeSize() {
		return nSize;
	}

	int childNumber(Node* node) {
		if (isLeafNode(node)) {
			return 0;
		}
		else if (node->next != nullptr and node->prev != nullptr) {
			return 2;
		}
		else {
			return 1;
		}
	}


	void insert(int value) {
		Node* newNode = new Node(value);
		nSize++;
		if (isEmpty()) {
			root = newNode;
			return;
		}
		else {
			Node* temp = root;
			Node* tmp = nullptr;
			while (temp != nullptr) {
				if (temp->data > value) {
					tmp = temp;
					temp = temp->prev;
				}
				else if (temp->data < value) {
					tmp = temp;
					temp = temp->next;
				}
				else {
					return;
				}
			}
			if (tmp->data > value) {
				tmp->prev = newNode;
				newNode->next = nullptr;
				newNode->prev = nullptr;
			}
			else if (tmp->data < value) {
				tmp->next = newNode;
				newNode->next = nullptr;
				newNode->prev = nullptr;
			}
			else {
				return;
			}
		}
	}

	void removeRoot() {
		nSize--;
		if (isLeafNode(root)) {
			delete root;
			return;
		}
		Node* temp = root;
		Node* deletedNode = root;
		if (childNumber(root) == 1) {
			if (root->next != nullptr) {
				root = root->next;
				delete temp;
			}
			else {
				root = root->prev;
				delete temp;
			}
			return;
		}
		else if (childNumber(root) == 2) {
			Node* left = root;
			left = left->next;
			if (left->prev == nullptr) {
				left->prev = root->prev;
				root = left;
				delete deletedNode;
				return;
			}
			while (left->prev != nullptr) {
				left = left->prev;
			}
			Node* parent = findParent(left);
			parent->prev = left->next;
			left->prev = root->prev;
			left->next = root->next;
			root = left;
			delete deletedNode;

		}
	}

	void remove(int value) {
		if (isEmpty()) {
			return;
		}
		if (root->data == value) {
			removeRoot();
			return;
		}
		nSize--;
		Node* deletedNode = root;
		while (!isLeafNode(deletedNode) and deletedNode->data != value) {
			if (deletedNode->data > value) {
				deletedNode = deletedNode->prev;
			}
			else if (deletedNode->data < value) {
				deletedNode = deletedNode->next;
			}
			else {
				return;
			}
		}
		Node* parent = findParent(deletedNode);

		if (isLeafNode(deletedNode)) {
			if (parent->data < deletedNode->data) {
				parent->next = nullptr;
			}
			else if (parent->data > deletedNode->data) {
				parent->prev = nullptr;
			}
			else {
				return;
			}
			delete deletedNode;
		}
		else {
			Node* left = deletedNode;
			if (childNumber(deletedNode) == 1) {
				if (parent->data < left->data) {
					if (left->next != nullptr) {
						parent->next = left->next;
					}
					else if (left->prev != nullptr) {
						parent->next = left->prev;
					}
					else {
						return;
					}
					delete left;
				}
				else if (parent->data > left->data) {
					if (left->next != nullptr) {
						parent->prev = left->next;
					}
					else if (left->prev != nullptr) {
						parent->prev = left->prev;
					}
					else {
						return;
					}
					delete left;
				}
			}
			else if (childNumber(deletedNode) == 2) {
				left = left->next;
				while (left->prev != nullptr) {
					left = left->prev;
				}
				Node* lparent = findParent(left);
				int s = deletedNode->data;
				deletedNode->data = left->data;
				left->data = s;

				if (isLeafNode(left)) {
					if (deletedNode->next == left) {
						lparent->next = nullptr;
					}
					else {
						lparent->prev = nullptr;
					}
					delete left;
				}
				else if (childNumber(left) == 1) {
					lparent->prev = left->next;
					left->next = nullptr;
					delete left;
				}
				else {
					return;
				}

			}
			else {
				return;
			}
		}

	}
};

void levelOrder(BinarySearchTree* tree) {
	if (tree->isEmpty()) {
		return;
	}
	Node* root = tree->root;
	Queue q;
	q.enqueue(root);

	while (!q.isEmpty()) {
		Node* temp = q.dequeue();
		cout << temp->data << " ";
		if (temp->prev) {
			q.enqueue(temp->prev);
		}
		if (temp->next) {
			q.enqueue(temp->next);
		}
	}
	cout << endl;
}

void inOrder(BinarySearchTree* tree)
{
	if (tree->isEmpty()) {
		return;
	}
	Stack s;
	Node* temp = tree->root;

	while (temp != NULL || !s.isEmpty()) {

		while (temp != NULL) {

			s.push(temp);
			temp = temp->prev;
		}

		temp = s.peek();
		s.pop();

		cout << temp->data << " ";
		temp = temp->next;
	}
}

void preOrder(BinarySearchTree* tree)
{
	if (tree->isEmpty()) {
		return;
	}

	Stack s;
	s.push(tree->root);

	while (!s.isEmpty()) {
		Node* temp = s.peek();
		cout << temp->data << " ";
		s.pop();

		if (temp->next)
			s.push(temp->next);
		if (temp->prev)
			s.push(temp->prev);
	}
	cout << endl;
}

void postOrder(BinarySearchTree* tree)
{
	if (tree->isEmpty()) {
		return;
	}

	Stack s1, s2;
	s1.push(tree->root);

	Node* temp;

	while (!s1.isEmpty()) {
		temp = s1.peek();
		s1.pop();
		s2.push(temp);

		if (temp->prev)
			s1.push(temp->prev);
		if (temp->next)
			s1.push(temp->next);
	}

	while (!s2.isEmpty()) {
		temp = s2.peek();
		s2.pop();
		cout << temp->data << " ";
	}
	cout << endl;
}

void reverseLevelOrder(BinarySearchTree* tree) {
	if (tree->isEmpty()) {
		return;
	}
	Node* root = tree->root;
	Queue q;
	Stack s;
	q.enqueue(root);
	Node* temp;
	while (!q.isEmpty()) {
		temp = q.dequeue();
		s.push(temp);
		if (temp->next) {
			q.enqueue(temp->next);
		}
		if (temp->prev) {
			q.enqueue(temp->prev);
		}
	}
	while (!s.isEmpty()) {
		temp = s.peek();
		s.pop();
		cout << temp->data << " ";
	}
	cout << endl;
}


int main() {
	BinarySearchTree tree;

	tree.insert(12);
	tree.insert(5);
	tree.insert(15);
	tree.insert(2);
	tree.insert(9);
	tree.insert(20);
	tree.insert(7);
	tree.insert(10);
	tree.insert(17);
	tree.insert(30);
	tree.insert(50);
	tree.insert(25);

	levelOrder(&tree);

	tree.remove(12);

	levelOrder(&tree);

	reverseLevelOrder(&tree);

	cout << tree.maxDepth();

	return 0;

}
