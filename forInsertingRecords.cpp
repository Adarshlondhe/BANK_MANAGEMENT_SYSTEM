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


int main(){

    //CODE TO INSERT RECORDS INTO THE FILE
    int j,k=1,t,z=34;
    char name[50]={'a'};
    int amt=500;
    char type='S',loan_sta='N';
    int loan_amt=0;
    for(int i=40;i<1040;i++){
        for(t=0;t<50;t++){
            name[t]='\0';
        }
        name[0]='a';
        j=i,k=1;
        while(j!=0){
            name[k]=((j%10)+48);
            k++;
            j=j/10;
        }
        amt=amt+i;
        write_account(i,name,amt,type,loan_sta,loan_amt);
    }
    display_all();
    return 0;
}
