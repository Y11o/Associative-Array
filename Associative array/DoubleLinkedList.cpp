#include <iostream>

using namespace std;

template <typename T>
class DLinkedList {
private:
	class Node {
	public:
		Node* pNext;
		Node* pPrev;
		T data;
		Node(T data, Node* pNext = nullptr, Node* pPrev = nullptr) {
			this->data = data;
			this->pNext = pNext;
			this->pPrev = pPrev;
		}
	};
	size_t size;
	Node* head;
	Node* tail;
public:
    DLinkedList(T data) {
        Node* newNode = new Node(data);
        head = tail = newNode;
        size = 1;
    };
    DLinkedList() {
        head = tail = nullptr;
        size = 0;
    };
    ~DLinkedList() {
        head == nullptr;
    };

    void push_back(T data) {
        Node* newNode = new Node(data);
        if (isEmpty()) {
            head = tail = newNode;
        }
        else {
            newNode->pPrev = tail;
            tail->pNext = newNode;
            tail = newNode;
        }
        size++;
    };
    void push_front(T data) {
        Node* newNode = new Node(data);
        if (isEmpty()) {
            head = tail = newNode;
        }
        else {
            newNode->pNext = head;
            head->pPrev = newNode;
            head = newNode;
        }
        size++;
    };
    void pop_back() {
        if (!isEmpty()) {
            if (get_size() == 1) {
                delete head;
                head = tail = nullptr;
                size--;
            }
            if (get_size() > 1) {
                Node* currNode = tail->pPrev;
                delete tail;
                tail = currNode;
                tail->pNext = nullptr;
                size--;
            }
        }
        else throw invalid_argument("Invalid index");
    };
    void pop_front() {
        if (!isEmpty()) {
            if (get_size() == 1) {
                delete head;
                head = tail = nullptr;
                size--;
            }

            else if (get_size() > 1) {
                Node* currNode = head->pNext;
                delete head;
                head = currNode;
                head->pPrev = nullptr;
                size--;
            }
        }
        else throw invalid_argument("Invalid index");
    };
    size_t get_size() {
        if (size >= 0)
            return size;
        else throw invalid_argument("Empty List");
    };
    void clear() {
        while (size != 0) {
        pop_front();
    }
    };
    bool isEmpty() { return get_size() == 0; };
    void push_back(DLinkedList& list) {
        Node* newNode = list.head;
        for (int i = 0; i < (int)list.get_size(); i++) {
            this->push_back(newNode->data);
            newNode = newNode->pNext;
        }
    };
    T at(size_t index) {
        if ((index >= 0) && (index < size)) {
            int currIndex = 0;
            Node* curr = this->head;
            while (curr != nullptr) {
                if (currIndex == index) {
                    return curr->data;
                }
                curr = curr->pNext;
                currIndex++;
            }
        }
        else
        {
            throw invalid_argument("Out of List range, index must be in range 0 <= index < size");
        }
    };
    void insert(T data, size_t index) {
        if ((index >= 0) && (index <= size)) {
            if (index == 0)
            {
                push_front(data);
            }
            else {
                Node* nodeToInsert = new Node(data, nullptr, nullptr);
                Node* prevNode = this->head;
                for (int i = 0; i < index - 1; i++)
                {
                    prevNode = prevNode->pNext;
                }
                prevNode->pNext->pPrev = nodeToInsert;
                nodeToInsert->pNext = prevNode->pNext;
                prevNode->pNext = nodeToInsert;
                nodeToInsert->pPrev = prevNode;
                size++;
            }
        }
        else
        {
            throw invalid_argument("Out of List range, index must be in range 0 <= index <= size");
        }
    };
    friend std::ostream& operator<< (std::ostream& out, DLinkedList& list) {
        size_t listSize = list.get_size();
        for (size_t i = 0; i < listSize; i++) {
            cout << list.at(i) << endl;
        }
        return out;
    }
};


