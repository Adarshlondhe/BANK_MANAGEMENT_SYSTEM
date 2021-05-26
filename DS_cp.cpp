#include<iostream>
#include<fstream>
#include<iomanip>
using namespace std;

class account
{
	int acc_no;
	char name[50];
	int amount;
	char type;
	char loan_status;
	int loan_amount;
public:
	void create_account();	//function to get data from user
	void show_account();	//function to show data on screen
	void modify();
	void dep(int);	        //function to accept amount and add to balance amount
	void draw(int);	        //function to accept amount and subtract from balance amount
	void loan_set(char,int);
	void revive(int );
	void report();	        //function to show data in tabular format
	int retacno();	        //function to return account number
	int retamount();	    //function to return balance amount
	char rettype();	        //function to return type of account
	char ret_loan_status();
	int ret_loan_amount();
};

void account::create_account()
{
	cout<<"\nEnter The account No. : ";
	cin>>acc_no;
	cout<<"\n\nEnter The Name of The account Holder : ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\nEnter Type of The account (C/S) : ";
	cin>>type;
	type=toupper(type);
	cout<<"\nEnter The Initial amount(>=500 for Saving and >=1000 for current ) : ";
	cin>>amount;
	if((amount<500 && type=='S') || (amount<1000 && type=='C')){
        cout<<"Insufficient Balance"<<endl;
	}
	cout<<"\n\n\nAccount Created..";
	loan_status='N';
	loan_amount=0;
}

void account::show_account()
{
	cout<<"\nAccount No. : "<<acc_no;
	cout<<"\nAccount Holder Name : ";
	cout<<name;
	cout<<"\nType of Account : "<<type;
	cout<<"\nBalance amount : "<<amount;
	cout<<"\nLoan Status: "<<loan_status;
	cout<<"\nLoan amount: "<<loan_amount;
}

void account::modify()
{
	cout<<"\nAccount No. : "<<acc_no;
	cout<<"\nModify Account Holder Name : ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\nModify Type of Account : ";
	cin>>type;
	type=toupper(type);
}

void account::loan_set(char status,int amt){

    loan_status=status;
    loan_amount=amt;
}

void account::revive(int val){
    loan_amount=loan_amount-val;
    if(loan_amount<=0){
        loan_amount=0;
    }
    if(loan_amount<=0){
        loan_status='N';
    }
}

void account::dep(int x)
{
	amount+=x;
}

void account::draw(int x)
{
	amount-=x;
}

void account::report()
{
	cout<<acc_no<<setw(8)<<" "<<name<<setw(10)<<"  "<<type<<setw(13)<<amount<<setw(12)<<loan_status<<setw(17)<<loan_amount<<endl;
}

int account::retacno()
{
	return acc_no;
}

int account::retamount()
{
	return amount;
}

char account::rettype()
{
	return type;
}

char account::ret_loan_status(){

    return loan_status;
}

int account::ret_loan_amount(){

    return loan_amount;
}

void write_account();	            //function to write record in binary file
void display_sp(int);	            //function to display account details given by user
void modify_account(int);	        //function to modify record of file
void delete_account(int);	        //function to delete record of file
void display_all();		            //function to display all account details
void amount_withdraw(int, int);     // function to deposit/withdraw amount for given account
void loan();                        //function to take loan on particular account
void loan_installment();            //function to take installment for loan.

int main()
{
	int ch;
	int num;
	do
	{
		system("cls");
		cout<<"\n\n******************** BANK MANAGEMENT SYSTEM ******************** ";
		cout<<"\n\n\n\tMAIN MENU";
		cout<<"\n\n\t01. NEW ACCOUNT";
		cout<<"\n\n\t02. DEPOSIT AMOUNT";
		cout<<"\n\n\t03. WITHDRAW AMOUNT";
		cout<<"\n\n\t04. BALANCE ENQUIRY";
		cout<<"\n\n\t05. ALL ACCOUNT HOLDER LIST";
		cout<<"\n\n\t06. CLOSE AN ACCOUNT";
		cout<<"\n\n\t07. MODIFY AN ACCOUNT";
		cout<<"\n\n\t08. TAKE A LOAN";
		cout<<"\n\n\t09. LOAN INSTALLMENT";
        cout<<"\n\n\t10. EXIT";
		cout<<"\n\n\tSelect Your Option (1-10): ";
		cin>>ch;
		system("cls");
		switch(ch)
		{
		case 1:
			write_account();
			break;
		case 2:
			cout<<"\n\n\tEnter The account No. : ";
			cin>>num;
			amount_withdraw(num, 1);
			break;
		case 3:
			cout<<"\n\n\tEnter The account No. : ";
			cin>>num;
			amount_withdraw(num, 2);
			break;
		case 4:
			cout<<"\n\n\tEnter The account No. : ";
			cin>>num;
			display_sp(num);
			break;
		case 5:
			display_all();
			break;
        case 6:
			cout<<"\n\n\tEnter The account No. : ";
			cin>>num;
			delete_account(num);
			break;
        case 7:
			cout<<"\n\n\tEnter The account No. : ";
			cin>>num;
			modify_account(num);
			break;
        case 8:
            loan();
            break;
		 case 9:
			loan_installment();
			break;
         case 10:
            cout<<"\n\n\tThanks for using bank management system";
			break;
		 default :cout<<"\a";
		}
		cin.ignore();
		cin.get();
    }while(ch!=10);
	return 0;
}


void write_account()
{
	account ac;
    ofstream outFile;
	outFile.open("account.dat",ios::binary|ios::app);
	ac.create_account();
	outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
	outFile.close();
}


void display_sp(int n)
{
	account ac;
	bool flag=false;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\nBALANCE DETAILS\n";
    	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if(ac.retacno()==n)
		{
			ac.show_account();
			flag=true;
		}
	}
    inFile.close();
	if(flag==false)
		cout<<"\n\nAccount number does not exist";
}


void display_all()
{
	account ac;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\n\n\t\tACCOUNT HOLDER LIST\n\n";
	cout<<"=============================================================================\n";
	cout<<"A/c no.     "<<"NAME          "<<"Type     "<<"Balance"<<"     Loan Status"<<"      Loan Amount"<<endl;
	cout<<"=============================================================================\n";
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		ac.report();
	}
	inFile.close();
}

void amount_withdraw(int n, int option)
{
	int amt;
	bool found=false;
	account ac;
	fstream File;
    File.open("account.dat", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));
		if(ac.retacno()==n)
		{
			ac.show_account();
			if(option==1)
			{
				cout<<"\n\n\tTO DEPOSITE AMOUNT ";
				cout<<"\n\nEnter The amount to be deposited: ";
				cin>>amt;
				ac.dep(amt);
			}
		    if(option==2)
			{
				cout<<"\n\n\tTO WITHDRAW AMOUNT ";
				cout<<"\n\nEnter The amount to be withdraw: ";
				cin>>amt;
				int bal=ac.retamount()-amt;
				if((bal<500 && ac.rettype()=='S') || (bal<1000 && ac.rettype()=='C'))
					cout<<"Insufficient balance"<<endl;
				else
					ac.draw(amt);
		      }
			int pos=(-1)*static_cast<int>(sizeof(ac));
			cout<<pos<<endl;
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(account));
			cout<<"\n\n\t Record Updated";
			found=true;
	       }
         }
    File.close();
	if(found==false)
		cout<<"\n\n Record Not Found ";
}

void modify_account(int n)
{
	bool found=false;
	account ac;
	fstream File;
    File.open("account.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));
		if(ac.retacno()==n)
		{
			ac.show_account();
			cout<<"\n\nEnter The New Details of account"<<endl;
			ac.modify();
			int pos=(-1)*static_cast<int>(sizeof(account));
			File.seekp(pos,ios::cur);
		    File.write(reinterpret_cast<char *> (&ac), sizeof(account));
		    cout<<"\n\n\t Record Updated";
		    found=true;
		  }
	}
	File.close();
	if(found==false)
		cout<<"\n\n Record Not Found ";
}

void delete_account(int n)
{
	account ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	outFile.open("Temp.dat",ios::binary);
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if(ac.retacno()!=n)
		{
			outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
		}
	}
    inFile.close();
	outFile.close();
	remove("account.dat");
	rename("Temp.dat","account.dat");
	cout<<"\n\n\tRecord Deleted ..";
}

void loan(){
    int num;
    cout<<"================================\n";
    cout<<"Our rate of interest is 5% p.a"<<endl;
    cout<<"================================\n";
    cout<<"Enter your account no: ";
    cin>>num;

    int loan_amt,year;
    char loan_s;
    bool found=false;
	account ac;
	fstream File;
    File.open("account.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));
		if(ac.retacno()==num)
		{
			ac.show_account();
			cout<<"\n\nEnter The amount value you want to take: ";
			cin>>loan_amt;
			cout<<"for how many years you want to take: ";
			cin>>year;
			loan_s='Y';
			ac.loan_set(loan_s,(loan_amt+((loan_amt*5/100)*year)));
			int pos=(-1)*static_cast<int>(sizeof(account));
			File.seekp(pos,ios::cur);
		    File.write(reinterpret_cast<char *> (&ac), sizeof(account));
		    cout<<"\n\n\t Loan taken succesfully"<<endl;
		    found=true;
		  }
	}
	File.close();
	if(found==false)
		cout<<"\n\n Record Not Found ";
}

void loan_installment(){
    int num;
    cout<<"Enter your account no: ";
    cin>>num;

    int val;
    char loan_s;
    bool found=false;
	account ac;
	fstream File;
    File.open("account.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));
		if(ac.retacno()==num)
		{
			ac.show_account();
			cout<<"\n\nEnter amount: ";
			cin>>val;
			ac.revive(val);

			int pos=(-1)*static_cast<int>(sizeof(account));
			File.seekp(pos,ios::cur);
		    File.write(reinterpret_cast<char *> (&ac), sizeof(account));
		    cout<<"\n\n\t Installment made successfully"<<endl;
		    found=true;
		  }
	}
	File.close();
	if(found==false)
		cout<<"\n\n Record Not Found ";
}
