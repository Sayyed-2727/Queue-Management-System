#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include "ClsDate.h"
#include <iomanip>
using namespace std;

class clsQueueLine
{
private:

    string _QueuePrefix;
    int _TotalTKTS = 0;
    int _AvgHandlingTimePerCus = 0;

    class clsTicket
    {
    private:
        short _Number = 0;
        string _Prefix;
        string _TicketTime;
        short _WaitingClients = 0;
        short _HandlingTime = 0;
        short _ExpectedServeTime = 0;
        
    public: 
        clsTicket(string Prefix, short Number, short WaitingClients, short AverageServeTime)
        {
            _Number = Number;
            _TicketTime = clsDate::DateToString(clsDate()) + " - " + clsDate::TimeToString(clsDate()) ;
            _Prefix = Prefix;
            _WaitingClients = WaitingClients;
            _HandlingTime = AverageServeTime;
        }
       
        string Prefix()
        {
            return _Prefix;

        }
       
        short Number()
        {
            return _Number;
        }

        string FullNumber()
        {
            return _Prefix + to_string(_Number);
        }

        string TicketTime()
        {
            return _TicketTime;
        }

        short WaitingClients()
        {
            return _WaitingClients;
        }

        short ExpectedServeTime()
        {
            return _HandlingTime * _WaitingClients;
        }

        void Print()
        {
            cout << "\n" << setw(39) << " " << "\t    _______________________";
            cout << "\n" << setw(20) << " " << "\t\t\t\t      " << FullNumber();
            cout << "\n" << setw(40) << " " << "      " << _TicketTime;
            cout << "\n" << setw(30) << " " << "\t\t      Wating Clients = " << _WaitingClients;
            cout << "\n" << setw(35) << " " << "\t    Serve Time In " << ExpectedServeTime() << " Minutes.";
            cout << "\n" << setw(39) << " " << "\t    _______________________\n";
          }
    };
 
public:

    queue <clsTicket> MyQueue;
    queue <clsTicket> TempQueue;
    
    clsQueueLine(string QueuePrefix, int AvgHandlingTime)
    {
        _QueuePrefix = QueuePrefix;
        _AvgHandlingTimePerCus = AvgHandlingTime;
    }

    void IssueTicket()
    {
        _TotalTKTS++;
        clsTicket TKT(_QueuePrefix, _TotalTKTS, WaitingClients(), _AvgHandlingTimePerCus);
        MyQueue.push(TKT);
    }

    string WhosNext()
    {
        if (MyQueue.empty())
        {
            return "No clients left..";
        }
        else
        {
            return MyQueue.front().FullNumber();
        }
    }

    int WaitingClients()
    {
        return MyQueue.size();
    }

    void PrintInfo()
    {
        cout << "\n" << setw(40) << " " << "_________________________________\n"; 
        cout << "\n" << setw(20) << " " << "\t\t\t\t    Queue Info"; 
        cout << "\n" << setw(40) << " " << "_________________________________" << endl; 
        cout << "\n" << setw(35) << " " << "\t    Prefix          = " <<  _QueuePrefix; 
        cout << "\n" << setw(35) << " " << "\t    Total Tickets   = " <<  _TotalTKTS; 
        cout << "\n" << setw(35) << " " << "\t    Served Clients  = " <<  ServedClients(); 
        cout << "\n" << setw(35) << " " << "\t    Waiting Clients = " <<  WaitingClients(); 
        cout << "\n" << setw(40) << " " << "_________________________________" << endl; 
        

    }

    void PrintTicketsLineRTL()
    {
        TempQueue = MyQueue;
        
        cout << "\n\n" << setw(25) << " " << "\tTickets: ";
        while (!TempQueue.empty())
        {
            cout << TempQueue.front().FullNumber() << " <-- ";
            TempQueue.pop();
        }
        
    }
    
    void PrintTicketsLineLTR()
    {
    
        cout << "\n\n" << setw(25) << " " << "\tTickets: ";
        for (int i = _TotalTKTS; i > 0; i--)
        {
            cout << _QueuePrefix << i << " --> ";
        }
    }

    void PrintAllTickets()
    {
       
        cout << " \n\n\n" << setw(50) << " " << "---Tickets---";

        if (MyQueue.empty())
        cout << "\n\n\t\t\t     ---No Tickets---\n";

        //we copy the queue in order not to lose the original
        queue <clsTicket> TempQueueLine= MyQueue;

       
        while (!TempQueueLine.empty())
        {
            TempQueueLine.front().Print();
            TempQueueLine.pop();
        }

    }

    bool ServeNextClient()
    {
        if (MyQueue.empty())
        {
            return false;
        }
        else
        {
            MyQueue.pop();
            return true;
        }
    }

    short ServedClients()
    {
        return _TotalTKTS - WaitingClients();
    }

};