//solution super 
#pragma once

#include <iostream>
#include <String>
#include <stack>
using namespace std;


class clsMyString {
private: 
	stack<string>  _UndoStack;
	stack<string>  _RedoStack;
	string _value;

public: 
	clsMyString() {
		_value = "";
	}

	//work only with MSVC compiler not GCC 
	__declspec(property(get = GetValue, put = SetValue)) string Value;


	void SetValue(string NewValue ) {
		_UndoStack.push(_value);
		_value = NewValue;
	}
	
	string GetValue() {
		return _value;
	}
	
	void Undo() {
		if(!_UndoStack.empty()){
			_RedoStack.push(_value);
			_value = _UndoStack.top();
			_UndoStack.pop();
		}
	}
	void Redo() {
		if (!_RedoStack.empty()) {
			SetValue(_RedoStack.top());
			_RedoStack.pop();
		}
	}



};