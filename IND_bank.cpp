#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

class account
{
    private:
        string ac_name ,ac_address,account_type;
        int ac_no,ac_balance,ph_no,ac_deposit;
    public:
        void open_account();

        void display_account();
        void deposit_money();
        void withdraw_money();
};

void account::open_account()
{
    account a1;

    cout<<"enter applicant's name"<<endl;
    cin.ignore();
    getline(cin,a1.ac_name);
    cout<<"enter the applicant's address"<<endl;
    cin.ignore();
    getline(cin,a1.ac_address);
    cout<<"enter applicant's phone no "<<endl;
    cin>>a1.ph_no;
    cout<<"enter the type of account of to create\n savings(s)\tcurrent(c)"<<endl;
    cin>>a1.account_type;
    cout<<"Enter the amount to deposit into the account"<<endl;
    cin>>a1.ac_balance;
    cout<<"Your account is created"<<endl;

    ofstream file_pointer("record.txt",ios::app);
    
    if (file_pointer.fail())
    {
        cout<<"Error opening file";
        EXIT_FAILURE;
    }
    file_pointer<<a1.ac_name<<" "<<a1.ac_address<<" "<<a1.ph_no<<" "<<a1.account_type<<" "<<a1.ac_balance<<"\n";

    file_pointer.close();
}
void account::display_account()
{
    account a2;
    ifstream file_pointer("record.txt",ios::in);

    if (file_pointer.fail())
    {
        cout<<"Error opening file";
        EXIT_FAILURE;
    }
    
    while (file_pointer>>a2.ac_name>>a2.ac_address>>a2.ph_no>>a2.account_type>>a2.ac_balance)
    {

        cout<<"applicant's name: "<<a2.ac_name<<endl;
        cout<<"applicant's address: "<<a2.ac_address<<endl;
        cout<<"applicant's phone no."<<a2.ph_no<<endl;
        cout<<"applicant's account type: "<<a2.account_type<<endl;
        cout<<"applicant's account balance: "<<a2.ac_balance<<endl;
    }
    file_pointer.close();
}
void account::deposit_money()
{
    vector <account> AC;
    account a1;
    ifstream fin("record.txt",ios::in);  
    string tempname;
    if (fin.fail())
    {
        cout<<"Error opening file";
        EXIT_FAILURE;
    }
    
    while (fin>>a1.ac_name>>a1.ac_address>>a1.ph_no>>a1.account_type>>a1.ac_balance)
    {
        AC.push_back(a1);
    }
    fin.close();

    cout<<"enter the account name";
    cin>>tempname;
    cout<<"enter the amount to deposit into the account: "<<endl;
    cin>>ac_deposit;
    ofstream fout("record.txt",ios::out);
    for (int i = 0; i < AC.size(); i++)
    {
        if (AC[i].ac_name==tempname)
        {
            AC[i].ac_balance+=ac_deposit;
            cout<<"amount successfully withdrawn"<<endl;
            cout<<"current account balance : "<<AC[i].ac_balance<<endl;
        }
        fout<<AC[i].ac_name<<" "<<AC[i].ac_address<<" "<<AC[i].ph_no<<" "<<AC[i].account_type<<" "<<AC[i].ac_balance<<endl;
    }
    fout.close();
}
void account::withdraw_money()
{
    vector <account> AC;
    account a2;
    ifstream fin("record.txt",ios::in);  
    string tempname;
    if (fin.fail())
    {
        cout<<"Error opening file";
        EXIT_FAILURE;
    }
    
    while (fin>>a2.ac_name>>a2.ac_address>>a2.ph_no>>a2.account_type>>a2.ac_balance)
    {
        AC.push_back(a2);
    }
    fin.close();

    cout<<"enter the account name";
    cin>>tempname;
    cout<<"enter the amount to withdrawn into the account: "<<endl;
    cin>>ac_deposit;
    ofstream fout("record.txt",ios::out);
    for (int i = 0; i < AC.size(); i++)
    {
        if (AC[i].ac_name==tempname)
        {
            if(AC[i].ac_balance<ac_deposit)
            {
                cout<<"Not enough balance in account to withdraw money"<<endl;
                EXIT_FAILURE;
            }
            else
            {
                AC[i].ac_balance-=ac_deposit;
                cout<<"amount successfully withdrawn"<<endl;
                cout<<"current account balance : "<<AC[i].ac_balance<<endl;
            }
        }
        fout<<AC[i].ac_name<<" "<<AC[i].ac_address<<" "<<AC[i].ph_no<<" "<<AC[i].account_type<<" "<<AC[i].ac_balance<<endl;
    }
    fout.close();
}

int main()
{
    account a1;
    int choice;
    do
    {
        cout<<"\n 1.create account \n 2.display account \n 3.deposit money \n 4.withdraw money \n 5.EXIT\n";
        cout<<"enter choice :";
        cin>>choice;
        switch (choice)
        {
        case 1:
            a1.open_account();
            break;
        
        case 2:
            a1.display_account();
            break;
        
        case 3:
            a1.deposit_money();
            break;

        case 4:
            a1.withdraw_money();
            break;
        }
    }while (choice<5 &&choice>0);
    return 0;
}