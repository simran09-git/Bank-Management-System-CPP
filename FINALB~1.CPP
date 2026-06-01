#include <iostream.h>
#include <conio.h>
#include <time.h>
#include <string.h>
#include <fstream.h>

class Bank
{
public:
    char accNo[20];
    char name[50];
    float balance;

    struct Transaction
    {
	float amount;
	int day, month, year;
	int hour, min, sec;
    };

    Transaction trans[10];
    int count;

    // ---------- ACCOUNT ----------
    void openAccount()
    {
	do
	{
	    cout << "\nEnter Account Number: ";
	    cin >> accNo;
	} while(strlen(accNo)<9 || strlen(accNo)>18);

	cout << "Enter Name: ";
	cin >> name;

	balance = 5000;
	count = 0;
	saveToFile();
    }

    // ---------- FILE SAVE ----------
    void saveToFile()
    {
	ofstream fout("bank.dat", ios::binary);
	fout.write((char*)this, sizeof(*this));
	fout.close();
    }

    void loadFromFile()
    {
	ifstream fin("bank.dat", ios::binary);
	if(fin)
	    fin.read((char*)this, sizeof(*this));
	fin.close();
    }

    // ---------- HISTORY SAVE ----------
    void saveHistory(char type, float amt,char method[10])
    {
	ofstream fout("history.txt", ios::app);

	time_t t = time(0);
	tm *now = localtime(&t);

	if(type=='D')
	    fout<<"Deposit   ";
	else
	    fout<<"Withdraw  ";

	fout<<method<<" ";
	fout<<amt<<"  "
	    <<now->tm_mday<<"/"
	    <<now->tm_mon+1<<"/"
	    <<now->tm_year+1900<<"  "
	    <<now->tm_hour<<":"
	    <<now->tm_min<<":"
	    <<now->tm_sec<<endl;

	fout.close();
    }

    // ---------- OPERATIONS ----------
    void deposit()
    {
	int type;
	float amt;
	char method[10];
	cout<<"\n 1.Cash Deposite:";
	cout<<"\n 2. Cheque Deposite:";
	cout<<"\n Choose Deposite Type:";
	cin>>type;

	cout<<"\nEnter deposit amount: ";
	cin>>amt;

	if(type==1)
	  {
	  strcpy(method,"cash");
	    balance += amt;
	  //  cout<<"\n Cash Deposite Successful";
	  }
	else if(type==2)
	  {
	    strcpy(method,"cheqye");
	    balance+=amt;
	   // cout<<"\n Cheque Deposite Successful";
	  }
	else
	  {
	     cout<<"\n Invalid Choice:";
	     return;
	  }
	saveToFile();
	saveHistory('D',amt,method);
    }

    void withdraw()
    {
	float amt;
	char method[10];
	strcpy(method,"cash");
	cout<<"\nEnter withdraw amount: ";
	cin>>amt;

	if(amt>balance)
	{
	    cout<<"Not enough balance";
	    return;
	}

	balance -= amt;
	saveToFile();
	saveHistory('W',amt,method);

	cout<<"Withdraw successful";
    }

    void showAccount()
    {
	cout<<"\nAccount Number: "<<accNo;
	cout<<"\nName          : "<<name;
	cout<<"\nBalance       : "<<balance;
    }

    void showFileHistory()
    {
	ifstream fin("history.txt");
	char ch;
	cout<<"\n\n---- TRANSACTION HISTORY ----\n";

	while(fin.get(ch))
	    cout<<ch;

	fin.close();
    }
};

// ---------- MAIN ----------
void main()
{
    clrscr();
    Bank b;
    int ch;

    b.loadFromFile();

    if(strlen(b.accNo)==0)
	b.openAccount();

    do
    {
	cout<<"\n\n1. Deposit";
	cout<<"\n2. Withdraw";
	cout<<"\n3. Show Account";
	cout<<"\n4. Transaction History";
	cout<<"\n5. Exit";
	cout<<"\nEnter choice: ";
	cin>>ch;

	switch(ch)
	{
	    case 1: b.deposit(); break;
	    case 2: b.withdraw(); break;
	    case 3: b.showAccount(); break;
	    case 4: b.showFileHistory(); break;
	    case 5: cout<<"Exit"; break;
	    default: cout<<"Wrong choice";
	}

    } while(ch!=5);

    getch();
}