#pragma once
#include<iostream>
#include<string>
#include<queue>
#include"clsTicket.h"
using namespace std;
class clsQueueLine {
private:
	string _prefix ="";
	int _time_for_each_client = 0;
	int _TotalTicket = 0;
	int _ServedClient = 0;
	int _WaitingClients = 0;
	queue<clsTicket> ClientQueue;
	void _printTicket(clsTicket &ticket) {
		cout << "\n\t\t " << ticket.GetIndexOfTicket();
		cout << "\n\t ________________________\n";
		cout << "\n\t " << ticket.GetDate() << "-"<< ticket.GetTime();
		cout << "\n\t Serve Time In \n\t  " << ticket.GetServerTime() << " Minutes."<<endl;
		cout << "\n\t ________________________\n";
	}

public:
	clsQueueLine(string prefix, short time) {
		 _prefix = prefix;
		 _time_for_each_client = time;
	}
	void IssueTicket() {
		ClientQueue.push(clsTicket(_prefix +to_string(_TotalTicket), _time_for_each_client * _WaitingClients));
		_WaitingClients++;
		_TotalTicket++;
	}
	void ServeNextClient() {
		if (!ClientQueue.empty()) {
			_WaitingClients--;
			_ServedClient++;
			ClientQueue.pop();
		}
	}
	void PrintInfo() {

		cout << "\n\t\t Queue Info";
		cout << "\n\t ________________________\n";
		cout << "\n\t Prefix          = " << _prefix;
		cout << "\n\t Total Tickets   = " << _TotalTicket;
		cout << "\n\t Served Clients  = " << _ServedClient;
		cout << "\n\t Waiting Clients = " << _WaitingClients;
		cout << "\n\t ________________________\n";
	}
	void PrintTicketsLineRTL() {
		cout << endl << "Tickets :  ";
		if (ClientQueue.empty())
			return;
		for (int i = _ServedClient; i <= _TotalTicket; i++)
		{
			cout << _prefix + to_string(i) << "<--";
		}
	}
	void PrintTicketsLineLTR() {
		cout << endl << "Tickets :  ";
		if (ClientQueue.empty())
			return;
		for (int i = _TotalTicket; i >= _ServedClient; i--)
		{
			cout << _prefix + to_string(i) << "-->";
		}
	}
	void PrintAllTickets() {
		cout << "\n\t\t Tickets: ";
		cout << "\n\t ________________________\n";
		queue<clsTicket> copy = ClientQueue;
		while (!copy.empty()) {
			_printTicket(copy.front());
			copy.pop();
		}
	}
};