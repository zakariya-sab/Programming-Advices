#pragma once
using namespace std; 
template <class T>
class clsDblLinkedList {
private:
	int _NumberOfNodes = 0;
public:
	class Node {
	public:
		T Data;
		Node* next;
		Node* prev;
	};
	Node* head = NULL;
	void InsertAtBeginning(T data) {

		_NumberOfNodes++;
		if (head == NULL) {
			head = new Node;
			head->Data = data;
			head->next = NULL;
			head->prev = NULL;
		}
		else {
			Node* temp = new Node;
			temp->Data = data;
			head->prev = temp;
			temp->next = head;
			temp->prev = NULL;
			head = temp;
		}
	}
	void PrintList() {
		if (IsEmpty())
			return;
		Node* temp = head;
		while (temp != NULL && temp->next != NULL) {
			cout << temp->Data;
			cout << " ";
			temp = temp->next;
		};
		if (temp != NULL)
		{
			cout << temp->Data << endl;
		}
	}
	Node* Find(T data) {
		if (IsEmpty())
			return NULL;
		if (head == NULL) {
			return NULL;
		}
		Node* temp = head;
		while (temp != NULL && temp->next != NULL) {
			if (temp->Data == data) {
				return temp;
			}
			else {
				temp = temp->next;
			}
		};
		if (temp != NULL)
		{
			if (temp->Data == data) {
				return temp;
			}
			else {
				temp = temp->next;
			}
		}
		return NULL;
	}
	void InsertAfter(Node* N1, T data) {
		if (N1 == NULL) return;
		Node* temp = Find(N1->Data);
		if (N1 != temp) {
			cout << "error";
			return;
		}
		_NumberOfNodes++;
		temp = new Node;
		temp->Data = data;
		//the node is the end node : 
		if (N1->next != NULL) {
			temp->prev = N1;
			temp->next = N1->next;
			N1->next->prev = temp;
			N1->next = temp;
		}//not the end node 
		else {
			temp->prev = N1;
			temp->next = NULL;
			N1->next = temp;
		}
	}
	void InsertAtEnd(T data) {
		if (head == NULL) {
			InsertAtBeginning(data);
		}
		else {
			Node* NewNode = new Node;
			Node* temp = head;
			while (temp->next != NULL) {
				temp = temp->next;
			}
			InsertAfter(temp, data);
		}
	}
	void DeleteFirstNode() {
		if (IsEmpty())
			return;
		if (head == NULL)
		{
			return;
		}
		else if (head->next == NULL) {
			_NumberOfNodes--;
			delete head;
			head = NULL;
		}
		else {
			_NumberOfNodes--;
			Node* temp = head;
			head = head->next;
			head->prev = NULL;
			delete temp;
		}
	}
	void DeleteLastNode() {
		if (IsEmpty())
			return;
		if (head == NULL)
		{
			return;
		}
		else if (head->next == NULL) {
			DeleteFirstNode();
		}
		else {
			Node* temp = head;
			while (temp->next != NULL) {
				temp = temp->next;
			}
			temp->prev->next = NULL;
			delete temp;
			_NumberOfNodes--;
		}
	}
	void DeleteNode(Node* DeletedNode) {
		if (IsEmpty())
			return;
		if (head == NULL || DeletedNode == NULL || Find(DeletedNode->Data) == NULL) {
			return;
		}

		else if (DeletedNode != head && DeletedNode->next != NULL) {
			_NumberOfNodes--;
			DeletedNode->prev->next = DeletedNode->next;
			DeletedNode->next->prev = DeletedNode->prev;
			delete DeletedNode;
		}
		else if (DeletedNode->next == NULL)
		{
			_NumberOfNodes--;
			DeletedNode->prev->next = NULL;
			delete DeletedNode;
		}
		else {
			DeleteFirstNode();
		}
	}
	int Size() {
		return _NumberOfNodes;
	}
	bool IsEmpty() {
		if (_NumberOfNodes == 0) {
			return true;
		}
		else {
			return false;
		}
	}
	void Clear() {
		/*if (IsEmpty())
			return;
		Node *temp = head;
		_NumberOfNodes = 0;
		while (temp!= NULL) {
			head = head->next;
			delete temp;
			temp = head;
		}
		temp = NULL;
		head = NULL;
	*/
	//better solution: 
		while (_NumberOfNodes > 0) {
			DeleteFirstNode();
		}
	}
	void Reverse() {
		if (head == NULL || IsEmpty())return; 
		else {
			/*Node* Prev = NULL;
			Node* Current = head;
			Node* Next = head->next;
			while (Current != NULL) {
				Current->next = Prev;
				Current->prev= Next;
				Prev = Current;
				Current = Next;
				if (Next == NULL) { Next = NULL; }
				else {
					Next = Next->next;
				}
			}
			head = Prev; */
			Node* Current = head;
			Node* Temp = NULL; 
			while (Current != NULL) { 
				Temp = Current->prev;
				Current->prev = Current->next;
				Current->next = Temp;
				Current = Current->prev; 
			}
			head = Temp->prev;



		}
	}
	Node* GetNode(int IndexOfNode ) {
		if (IndexOfNode < 0 || IndexOfNode > _NumberOfNodes -1 ) { return NULL; }
		else {
			Node* temp = head; 
			while (temp != NULL && IndexOfNode > 0) {
				IndexOfNode--; 
				temp = temp->next; 
			}
			return temp; 
		}
	}
	T GetItem(int indexOfNode) {
		Node* N = NULL; 
		N = GetNode(indexOfNode);
		if (N != NULL) {
			return N->Data;
		}
		else {
			cout << "\nthe list has not the item \n ";
			exit(-1);
		}
	}
	bool UpdateItem(int IndexOfNode, int NewValueOfNode) {
		Node* N = NULL; 
		N = GetNode(IndexOfNode); 
		if (N != NULL) {
			N->Data = NewValueOfNode;
			return true; 
		}
		else {
			return false;
		}
	}
	void InsertAfter(int IndexOfNode, int ValueOfNewNode) {
		/*Node* N = GetNode(IndexOfNode);
		if (N != NULL) {
			_NumberOfNodes++;
			Node* NewNode = new Node;
			NewNode->Data = ValueOfNewNode;
			NewNode->next = N->next;
			NewNode->prev = N;
			N->next->prev = NewNode;
			N->next = NewNode;
		}
		else {
			return; 
		}*/
		InsertAfter(GetNode(IndexOfNode), ValueOfNewNode);

	}
};
