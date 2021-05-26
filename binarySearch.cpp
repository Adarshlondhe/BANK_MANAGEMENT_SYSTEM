#include <bits/stdc++.h>
using namespace std;


class account
{
public:
	int acc_no;
	char name[50];
	int amount;
	char type;
	char loan_status;
	int loan_amount;

    void create_account(int accno,char n[],int amt,char tp,char l_s,int l_amt){

        acc_no=accno;
        int i=0;
        while(n[i]!='\0'){
            name[i]=n[i];
            i++;
        }
        amount=amt;
        type=tp;
        loan_status=l_s;
        loan_amount=l_amt;
    }

    void report()
    {
        cout<<acc_no<<setw(8)<<" "<<name<<setw(10)<<"  "<<type<<setw(13)<<amount<<setw(12)<<loan_status<<setw(17)<<loan_amount<<endl;
    }

    int retacno(){
        return acc_no;
    }


    void display(){
        cout<<"Account number: "<<acc_no<<endl;
        //cout<<"Name: "<<getline(name)<<endl;
        cout<<"Amount: "<<amount<<endl;
        cout<<"Type: "<<type<<endl;

    }
};

void write_account(int acc_no,char s[],int amt,char tp,char l_s,int l_amt)
{
	account ac;
	ofstream outFile;
	outFile.open("data_insert.dat",ios::binary|ios::app);
	ac.create_account(acc_no,s,amt,tp,l_s,l_amt);
	outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
	outFile.close();
}

void display_all()
{
	account ac;
	ifstream inFile;
	inFile.open("data_insert.dat",ios::binary);
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

bool custom_function(account &a,int b){
        return a.acc_no<b;
    }

int main(){
    account ac;
    vector <account> v;
    ifstream inFile;
    inFile.open("data_insert.dat",ios::binary);
    while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
        v.push_back(ac);
	}
	inFile.close();

    sort(v.begin(),v.end(),[](const account &lhs,const account &rhs){
         return lhs.acc_no<rhs.acc_no;
         });


     auto iter=lower_bound(v.begin(),v.end(),800,custom_function);

    iter->display();


    return 0;
}

