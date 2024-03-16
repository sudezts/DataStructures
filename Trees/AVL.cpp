
#include <iostream>
using namespace std;

class Node {
public:
	int data;
	Node* next;
	Node* prev;
	int height;

	Node(int data) {
		this->data = data;
		this->next = nullptr;
		this->prev = nullptr;
		this->height = 1;
	}
	friend class AVLTree;
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

class AVLTree {
public:
	Node* root;
	int nSize;
public:
	AVLTree() {
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

	int maxDepth(Node* r) {
		if (r == nullptr) {
			return 0;
		}
		int depth = 0;
		Stack* wq = new Stack();
		Stack* path = new Stack();

		wq->push(r);
		while (!wq->isEmpty()) {
			r = wq->peek();
			if (!path->isEmpty() && r == path->peek()) {
				if (path->getSize() > depth)
					depth = path->getSize();
				path->pop();
				wq->pop();
			}
			else {
				path->push(r);
				if (r->next != nullptr)
					wq->push(r->next);
				if (r->prev!= nullptr)
					wq->push(r->prev);
			}
		}

		return depth;
	}

	bool isBalance() {

		int lheight = maxDepth(root->prev);
		int rheight = maxDepth(root->next);
		int range;
		if (lheight >= rheight) {
			range = lheight - rheight;
		}
		else {
			range = rheight - lheight;
		}
		if (range == 0 or range == 1) {
			return true;
		}
		else {
			return false;
		}
	}

	void rotateLeft() {
		Node* left = root->prev;

		if (maxDepth(left->prev) > maxDepth(left->next)) {
			if (left->prev != nullptr) {
				root->prev = left->next;
			}
			else {
				root->prev = nullptr;
			}
			left->next = root;
			root = left;
		}
		else if(maxDepth(left->prev) < maxDepth(left->next)) {
			Node* temp = left->next;
			root->prev = temp;
			if (temp->prev != nullptr) {
				left->next = temp->prev;
			}
			else {
				left->next = nullptr;
			}
			temp->prev = left;
			if (temp->next != nullptr) {
				root->prev = temp->next;
			}
			else {
				root->prev = nullptr;
			}
			temp->next = root;
			root = temp;
		}
	}

	void rotateRight() {
		Node* right = root->next;

		if (maxDepth(right->next) > maxDepth(right->prev)) {
			root->next = right->prev;
			right->prev = root;
			root = right;
		}
		else if (maxDepth(right->next) < maxDepth(right->prev)) {
			Node* temp = right->prev;
			root->next = temp;
			if (temp->next != nullptr) {
				right->prev = temp->next;
			}
			else {
				right->prev = nullptr;
			}
			temp->next = right;
			if (temp->prev != nullptr) {
				root->next = temp->prev;
			}
			else {
				root->next = nullptr;
			}
			temp->prev = root;
			root = temp;
		}
	}

	void rebalance() {
		if (isBalance()) {
			return;
		}
		while (!isBalance()) {
			int lheight = maxDepth(root->prev);
			int rheight = maxDepth(root->next);
			if (lheight > rheight) {
				rotateLeft();
			}
			else if (lheight < rheight) {
				rotateRight();
			}
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
			rebalance();
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
			rebalance();
			return;
		}
		else if (childNumber(root) == 2) {
			Node* left = root;
			left = left->next;
			if (left->prev == nullptr) {
				left->prev = root->prev;
				root = left;
				delete deletedNode;
				rebalance();
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
			rebalance();
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
			rebalance();
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
					rebalance();
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
					rebalance();
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
					rebalance();
				}
				else if (childNumber(left) == 1) {
					lparent->prev = left->next;
					left->next = nullptr;
					delete left;
					rebalance();
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

void levelOrder(AVLTree* tree) {
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

void inOrder(AVLTree* tree)
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
	cout << endl;
}

void preOrder(AVLTree* tree)
{
	if (tree->isEmpty()) {
		return;
	}

	Stack s;
	s.push(tree->root);

	while (!s.isEmpty()) {
		Node* temp=s.peek();
		cout << temp->data << " ";
		s.pop();

		if (temp->next)
			s.push(temp->next);
		if (temp->prev)
			s.push(temp->prev);
	}
	cout << endl;
}

void postOrder(AVLTree* tree)
{
	if (tree->isEmpty()) {
		return;
	}

	Stack s1,s2;
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


int main() {
	AVLTree tree;

	tree.insert(44);
	tree.insert(78);
	tree.insert(17);
	tree.insert(88);
	tree.insert(50);
	tree.insert(32);
	tree.insert(62);
	tree.insert(48);
	tree.insert(47);
	tree.insert(49);
	tree.insert(31);
	tree.insert(33);
	tree.insert(46);

	levelOrder(&tree);

	tree.remove(47);

	levelOrder(&tree);
	inOrder(&tree);
	preOrder(&tree);
	postOrder(&tree);

	return 0;

}
