#pragma once
#include<iostream>  
#include<string>
#include<queue>
#include <ctime>
using namespace std;
class clsTicket {
private:
	string _IndexOfTicket = "";
	int _ServerTime = 0;
	string _Date; 
	string _Time; 
public:
	clsTicket(string NumberOfTicket, int ServerTime /*int WaitingClients */) {
		_IndexOfTicket = NumberOfTicket;
		_ServerTime = ServerTime;

		time_t _TimeOfPrintTicket = time(0);
		tm timeInfo;                                       
		localtime_s(&timeInfo, &_TimeOfPrintTicket);
		 _Date = to_string(timeInfo.tm_mday) +"/" + to_string(timeInfo.tm_mon + 1) + "/" + to_string(timeInfo.tm_year + 1900);
		 _Time = to_string(timeInfo.tm_hour) +":" + to_string(timeInfo.tm_min) + ":" + to_string(timeInfo.tm_sec);
	}
	string GetIndexOfTicket() {
		return _IndexOfTicket; 
	}
	string GetDate() {

		return _Date;
	}
	string GetTime() {

		return _Time;
	}
	int GetServerTime() {

		return _ServerTime;
	}
	void SetServerTime(int ServerTime) {
		_ServerTime = ServerTime;
	}
};