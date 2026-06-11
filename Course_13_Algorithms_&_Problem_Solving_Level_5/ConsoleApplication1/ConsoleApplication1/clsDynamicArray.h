#pragma once

#include <iostream>

using namespace std;
template <class T>
class clsDynamicArray {
private:
	T* _TableOfElement = NULL;
	int _NumberOfElement = 0;
	int _Min(int a, int b) {
		return (a < b) ? a : b;
	}
public:
	clsDynamicArray(int NumberOfElement = 0)
	{
		_NumberOfElement = NumberOfElement;
		_TableOfElement = new T[NumberOfElement];
	}
	void SetItem(int index, T data) {
		if (index < 0 || index > _NumberOfElement - 1) {
			return;
		}
		_TableOfElement[index] = data;
	}
	bool IsEmpty() {
		return _TableOfElement == NULL ? true : false;
	}
	int Size() {
		return _NumberOfElement;
	}
	void PrintList() {
		if (_TableOfElement == NULL)
			return;
		for (int i = 0; i < _NumberOfElement; i++) {
			cout << " " << _TableOfElement[i];
		}
	}
	void Resize(int NewSize) {
		if (NewSize == _NumberOfElement) {
			return;
		}
		else {
			if (NewSize <= 0)
				NewSize = 0;
			T* NEWTAble = NULL;
			NEWTAble = new T[NewSize];
			int min = _Min(NewSize, _NumberOfElement);
			for (int i = 0; i < min; i++) {
				NEWTAble[i] = _TableOfElement[i];
			}
			delete[] _TableOfElement;
			_TableOfElement = NEWTAble;
			NEWTAble = NULL;
			_NumberOfElement = NewSize;
		}
	}
	T GetItem(int index) {
		if (index < 0 || index > _NumberOfElement - 1) {
			return T{};
		}
		return _TableOfElement[index];
	}
	void Reverse() {
		if (_TableOfElement == NULL) {
			return;
		}
		int start = 0;
		int end = _NumberOfElement - 1;
		T temp = T{};
		while (start < end) {

			temp = _TableOfElement[start];
			_TableOfElement[start] = _TableOfElement[end];
			_TableOfElement[end] = temp;
			end--;
			start++;
		}
	}
	void Clear() {
		//_NumberOfElement = 0;
		//delete[] _TableOfElement;
		//_TableOfElement = NULL;
		//or 
		Resize(0);
	}
	void DeleteItemAt(int index) {
		if (index < 0 || index > _NumberOfElement - 1) {
			return;
		}
		T* NEWTAble = NULL;
		--_NumberOfElement;
		NEWTAble = new T[_NumberOfElement];
		for (int i = 0; i < _NumberOfElement; i++) {
			if (i >= index)
			{
				NEWTAble[i] = _TableOfElement[i + 1];
			}
			else {
				NEWTAble[i] = _TableOfElement[i];
			}
		}
		delete[] _TableOfElement;
		_TableOfElement = NEWTAble;
		NEWTAble = NULL;
	}
	void DeleteFirstItem()
	{
		DeleteItemAt(0);
	}
	void DeleteLastItem()
	{
		DeleteItemAt(_NumberOfElement - 1);
	}
	int Find(T data) {
		if (_TableOfElement == NULL)
			return -1;
		for (int i = 0; i < _NumberOfElement - 1;i++) {
			if (data == _TableOfElement[i]) {
				return i;
			}
		}
		return -1;		
	}
	bool DeleteItem(T data){
		int item = Find(data);
		if (item  == -1)
		{
			return false; 
		}
		else {
			DeleteItemAt(item);
			return true;
		}
	}
	//bool InsertAt(int index , T data) {
	//	if (IsEmpty() || index < 0 || index > _NumberOfElement - 1)
	//		return false; 
	//	_NumberOfElement++;
	//	//befor the index 
	//	T* TempTabel = new T[_NumberOfElement];
	//	for (int i = 0; i < index; i++) {
	//		TempTabel[i] = _TableOfElement[i];
	//	}
	//	//the index :
	//	TempTabel[index] = data;
	//	//the elemenet after :
	//	for (int i = index; i < _NumberOfElement-1; i++) {
	//		TempTabel[i+1] = _TableOfElement[i];
	//	}
	//	//free the ressorces 
	//	delete[] _TableOfElement;
	//	_TableOfElement = TempTabel;
	//	TempTabel = NULL; 
	//	return true; 
	//}
	void InsertAtBeginning(T value)
	{

		InsertAt(0, value);

	}


	bool InsertBefore(int index, T value)
	{
		if (index < 1)
			return InsertAt(0, value);
		else
			return InsertAt(index - 1, value);

	}

	bool InsertAfter(int index, T value)
	{
		if (index >= _NumberOfElement)
			return InsertAt(_NumberOfElement - 1, value);
		else
			return InsertAt(index + 1, value);
	}

	bool InsertAtEnd(T value)
	{
		return InsertAt(_NumberOfElement-1, value);
	}
	~clsDynamicArray(){
		delete[] _TableOfElement; 
	}
};