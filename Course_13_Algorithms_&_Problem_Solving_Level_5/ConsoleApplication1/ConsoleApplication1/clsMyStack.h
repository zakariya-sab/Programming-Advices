#pragma once

#include <iostream>
#include "clsDblLinkedList.h"


using namespace std;
template <class T>
class clsMyStack {
private:
	clsDblLinkedList<T> _MyStack; 
public: 
	void push(T data) {
		_MyStack.InseartAtend();
	}
};