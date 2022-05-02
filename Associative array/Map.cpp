#include <iostream>
#include "DoubleLinkedList.h"
#include "Color.cpp"

using namespace std;

template<typename keyType, typename valueType>

class Map {
private:
	class Node {
	public:
		Color color;					// Black and Red from Color.cpp
		keyType key;					// node's key value
		valueType value;				// node's pair for key
		Node* left;						// pointer to left child
		Node* right;					// pointer to right child
		Node* parent;					// pointer to the parent

		Node(keyType key, valueType value, Node* parent, Color color, Node* left = NULL, Node* right = NULL) {  
			this->key = key;
			this->value = value;
			this->parent = parent;
			this->color = color;
			this->left = left;
			this->right = right;
		}
	};

	Node* root;		// pointer to the root
	Node* nil;		// pointer to the nill

	void leftRotate(Node* x) {		// left rotate
		Node* y = x->right;
		x->right = y->left;
		if (y->left != nil)
			y->left->parent = x;
		y->parent = x->parent;
		if (x->parent == nullptr)
			this->root = y;
		else
			if (x == x->parent->left)
				x->parent->left = y;
			else
				x->parent->right = y;
		y->left = x;
		x->parent = y;
	}

	void rightRotate(Node* x) {		// right rotate
		Node* y = x->left;
		x->left = y->right;
		if (y->right != nil)
			y->right->parent = x;
		y->parent = x->parent;
		if (x->parent == nullptr)
			this->root = y;
		else
			if (x == x->parent->right)
				x->parent->right = y;
			else
				x->parent->left = y;
		y->right = x;
		x->parent = y;
	}

	void printNode(Node* currNode) {
		if (currNode != nil) {
			if (currNode->right != nullptr && currNode->right != nil)
				printNode(currNode->right);
			if (currNode->left != nullptr && currNode->left != nil)
				printNode(currNode->left);
			cout << currNode->key << " : " << currNode->value << endl;
		}
	}

	void replacement(Node* oldNode, Node* newNode) {
		if (oldNode->parent == nullptr)
			root = newNode;
		else
			if (oldNode == oldNode->parent->left)
				oldNode->parent->left = newNode;
			else
				oldNode->parent->right = newNode;

		newNode->parent = oldNode->parent;
	}

	void deleteNode(Node* currNode) {
		if (currNode != nil) {
			if (currNode->right != nullptr && currNode->right != nil)
				deleteNode(currNode->right);
			if (currNode->left != nullptr && currNode->left != nil)
				deleteNode(currNode->left);
			delete currNode;
		}
	}

	void getListOfValues(Node* elem, DLinkedList<valueType> *values) {
		if (elem != nil) {
			getListOfValues(elem->left, values);
			values->push_back(elem->value);
			getListOfValues(elem->right, values);
		}
	}

	void getListOfKeys(Node* elem, DLinkedList<keyType> *keys) {
		if (elem != nil) {
			getListOfKeys(elem->left, keys);
			keys->push_back(elem->key);
			getListOfKeys(elem->right, keys);
		}
	}

public:
	Map() {
		nil = new Node(NULL, NULL, NULL, Black);
		root = nil;
	};
	~Map() {
		this->root == nil;
		/*deleteNode(this->root);
		delete nil;*/
	};

	void insert(keyType key, valueType value) {
		Node* newNode = new Node(key, value, NULL, Red, nil, nil);
		if (this->root == nil) {
			root = newNode;
			newNode->color = Black;
			return;
		}
		else {
			Node* newNodeParent = nullptr;
			Node* currNode = this->root;

			while (currNode != nil) {
				newNodeParent = currNode;
				if (newNode->key < currNode->key) {
					currNode = currNode->left;
				}
				else {
					currNode = currNode->right;
				}
			}
			newNode->parent = newNodeParent;
			if (newNode->key < newNodeParent->key)
				newNodeParent->left = newNode;
			else
				newNodeParent->right = newNode;
		}
		if (newNode->parent->parent == nullptr)
			return;

		Node* uncle;
		while (newNode->parent->color == Red) {
			bool isAtRight = newNode->parent->parent->right == newNode->parent;

			uncle = isAtRight ? (newNode->parent->parent->left) : (newNode->parent->parent->right);

			if (uncle->color == Red) {
				uncle->color = Black;
				newNode->parent->color = Black;
				newNode->parent->parent->color = Red;
				newNode = newNode->parent->parent;
			}
			else {
				if (newNode == (isAtRight ? (newNode->parent->left) : (newNode->parent->right))) {
					newNode = newNode->parent;
					isAtRight ? rightRotate(newNode) : leftRotate(newNode);
				}
				newNode->parent->color = Black;
				newNode->parent->parent->color = Red;
				isAtRight ? leftRotate(newNode->parent->parent) : rightRotate(newNode->parent->parent);
			}

			if (newNode == root) {
				break;
			}
		}
		root->color = Black;
	};
	void clear() {
		deleteNode(this->root);
		this->root = nil;
	};
	void print() {
		if (this->root == nil)
			throw invalid_argument("Map is empty");
		else
			printNode(this->root);
	};

	DLinkedList <keyType> getKeys() {
		DLinkedList<keyType>* keys = new DLinkedList<keyType>;
		getListOfKeys(root, keys);
		return *keys;
	}

	DLinkedList <valueType> getValues() {
		DLinkedList<valueType>* values = new DLinkedList<valueType>;
		getListOfValues(root, values);
		return *values;
	}

	Node* findByKey(keyType key) {
		Node* findNode = nullptr;
		Node* currNode = this->root;

		while (currNode != nil) {
			if (currNode->key == key) {
				findNode = currNode;
				break;
			}
			if (currNode->key > key)
				currNode = currNode->left;
			else
				currNode = currNode->right;
		}
		if (findNode == nullptr){
			throw invalid_argument("Key not found");
		}
		else
		{
			return findNode;
		}
	}

	void removeNode(keyType key) {
		Node* nodeToBeDeleted = findByKey(key);
		
		Node* x = nullptr;
		Node* y = nullptr;

		int originalColor = nodeToBeDeleted->color;

		y = nodeToBeDeleted;

		if (nodeToBeDeleted->left == nil) {
			x = nodeToBeDeleted->right;
			replacement(nodeToBeDeleted, nodeToBeDeleted->right);
		}
		else
			if (nodeToBeDeleted->right == nil) {
				x = nodeToBeDeleted->left;
				replacement(nodeToBeDeleted, nodeToBeDeleted->left);
			}
			else {
				y = nodeToBeDeleted->right;

				while (y->left != nil) {
					y = y->left;
				}

				originalColor = y->color;
				x = y->right;

				if (y->parent == nodeToBeDeleted)
					x->parent = y;
				else {
					replacement(y, y->right);
					y->right = nodeToBeDeleted->right;
					y->right->parent = y;
				}

				replacement(nodeToBeDeleted, y);
				y->left = nodeToBeDeleted->left;
				y->left->parent = y;
				y->color = nodeToBeDeleted->color;
			}

		delete nodeToBeDeleted;

		if (originalColor == Black) {
			Node* brother;
			while (x != root && x->color == Black) {
				if (x == x->parent->left) {
					brother = x->parent->right;

					if (brother->color == Red) {
						brother->color = Black;
						x->parent->color = Red;
						leftRotate(x->parent);
						brother = x->parent->right;
					}

					if (brother->left->color == Black && brother->right->color == Black) {
						brother->color = Red;
						x = x->parent;
					}
					else {
						if (brother->right->color == Black) {
							brother->left->color = Black;
							brother->color = Red;
							rightRotate(brother);
							brother = x->parent->right;
						}
						brother->color = x->parent->color;
						x->parent->color = Black;
						brother->right->color = Black;
						leftRotate(x->parent);
						x = root;
					}
				}
				else {
					brother = x->parent->left;
					if (brother->color == Red) {
						brother->color = Black;
						x->parent->color = Red;
						rightRotate(x->parent);
						brother = x->parent->left;
					}
					if (brother->right->color == Black && brother->right->color == Black) {
						brother->color = Red;
						x = x->parent;
					}
					else {
						if (brother->left->color == Black) {
							brother->right->color = Black;
							brother->color = Red;
							leftRotate(brother);
							brother = x->parent->left;
						}
						brother->color = x->parent->color;
						x->parent->color = Black;
						brother->left->color = Black;
						rightRotate(x->parent);
						x = root;
					}
				}
			}
			x->color = Black;
		}
		
	}
};
