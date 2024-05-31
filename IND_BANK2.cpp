#include<iostream>
#include<fstream>
#include<vector>
#include<iomanip>
#include<windows.h>
using namespace std;
bool login(string username,string password);
void login_choices(string user);

struct cust_logins
{
    string username,password;
};
class account
{
    private:
        string ac_name ,ac_address,account_type;
        int ac_no,ac_balance,ph_no,ac_deposit;
    public:
        void openaccount();
        // void closeaccount();
        void displayaccount(string user);
        void depositmoney(string user);
        void withdraw_money(string user);
        friend bool login(string username,string password);
};

void account::openaccount()
{
    system("cls");
    account a1;
    string password;
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
    cout<<"enter the password for the A/C"<<endl;
    cin.ignore();
    getline(cin,password);
    system("cls");
    cout<<"Your account is created"<<endl;

    ofstream file_pointer("record.txt",ios::app);
    
    if (file_pointer.fail())
    {
        cout<<"Error opening file";
        EXIT_FAILURE;
    }
    file_pointer<<a1.ac_name<<" "<<a1.ac_address<<" "<<a1.ph_no<<" "<<a1.account_type<<" "<<a1.ac_balance<<"\n";

    file_pointer.close();
    
    ofstream fout("cust_logs.txt",ios::app);
    if (fout.fail())
    {
        cout<<"Error opening file";
        EXIT_FAILURE;
    }
    fout<<a1.ac_name<<" "<<password<<"\n";
    fout.close();
    Sleep(4000);
}
void account::displayaccount(string user)
{
    account a2;
    ifstream file_pointer("record.txt",ios::in);

    if (file_pointer.fail())
    {
        cout<<"Error opening file";
        // EXIT_FAILURE;
        Sleep(8000);
        system("cls");
    }
    
    while (file_pointer>>a2.ac_name>>a2.ac_address>>a2.ph_no>>a2.account_type>>a2.ac_balance)
    {
        if (a2.ac_name==user)
        {
            system("cls");
            cout << "applicant's name: " << a2.ac_name << endl;
            cout << "applicant's address: " << a2.ac_address << endl;
            cout << "applicant's phone no." << a2.ph_no << endl;
            (a2.account_type=="s")?(cout << "applicant's account type: savings"<<endl):(cout << "applicant's account type: current"<<endl);
            cout << "applicant's account balance: " << a2.ac_balance << endl;
        }
    }
    file_pointer.close();
}
void account::depositmoney(string user)
{
    vector <account> AC;
    account a1;
    ifstream fin("record.txt",ios::in);  
    
    if (fin.fail())
    {
        cout<<"Error opening file";
        // EXIT_FAILURE;
        Sleep(8000);
        system("cls");
    }
    
    while (fin>>a1.ac_name>>a1.ac_address>>a1.ph_no>>a1.account_type>>a1.ac_balance)
    {
        AC.push_back(a1);
    }
    fin.close();
    system("cls");
    cout<<"enter the amount to deposit into the account: "<<endl;
    cin>>ac_deposit;
    ofstream fout("record.txt",ios::out);
    for (int i = 0; i < AC.size(); i++)
    {
        if (AC[i].ac_name==user)
        {
            AC[i].ac_balance+=ac_deposit;
            cout<<"amount successfully deposited"<<endl;
            cout<<"current account balance : "<<AC[i].ac_balance<<endl;
        }
        fout<<AC[i].ac_name<<" "<<AC[i].ac_address<<" "<<AC[i].ph_no<<" "<<AC[i].account_type<<" "<<AC[i].ac_balance<<endl;
    }
    fout.close();
    AC.clear();
    Sleep(7000);
    system("cls");
}
void account::withdraw_money(string user)
{
    vector <account> AC;
    account a2;
    ifstream fin("record.txt",ios::in);  
    // string tempname;
    if (fin.fail())
    {
        cout<<"Error opening file";
        // EXIT_FAILURE;
    }
    
    while (fin>>a2.ac_name>>a2.ac_address>>a2.ph_no>>a2.account_type>>a2.ac_balance)
    {
        AC.push_back(a2);
    }
    fin.close();
    system("cls");
    cout<<"enter the amount to withdrawn from the account: "<<endl;
    cin>>ac_deposit;
    ofstream fout("record.txt",ios::out);
    for (int i = 0; i < AC.size(); i++)
    {
        if (AC[i].ac_name==user)
        {
            if(AC[i].ac_balance<ac_deposit)
            {
                cout<<"Not enough balance in account to withdraw money"<<endl;
                EXIT_FAILURE;
                Sleep(5000);
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
    AC.clear();
    fout.close();
    Sleep(7000);
    system("cls");
}
void login_choices(string user)
{  
    account useraccount;
    int log_choice;
    do
    {
    cout<<"\n>1.display account \n >2.deposit money \n >3.withdraw money \n >4.logout\n";
    cout<<"enter choice : ";
    cin>>log_choice;
        switch (log_choice)
        {
        case 1:
            useraccount.displayaccount(user);
            break;
        
        case 2:
            useraccount.depositmoney(user);
            break;

        case 3:
            useraccount.withdraw_money(user);
            break;

        }
    } while (log_choice<4);
}

bool login(string username,string password)
{
    vector<cust_logins> AC;
    cust_logins tempname;

    ifstream fin("cust_logs.txt",ios::in);

    while (fin>>tempname.username>>tempname.password)
    {
        AC.push_back(tempname);
    }
    for (int i = 0; i < AC.size(); i++) 
    {
        if (AC[i].username==username && AC[i].password==password)
        {
            return true;
        }
    }
    AC.clear();
    return false;
}
int main()
{
    int main_choice;
    string username, password;
    account user_account;
    do
    {
        cout <<setfill('-')<<setw(63)<< "***Welcome to the XYZ BANK***"<<setfill('-')<<setw(63);
        cout << "\n >1.Login\n >2.Create A/C\n >3 EXIT\n>>";
        cin >> main_choice;
        switch (main_choice)
        {
        case 1:
            system("cls");
            cout << "enter the user name (fullname as per A/C)>>\n" ;
            cin >> username;
            cout << "enter the password\n>>";
            cin >> password;
            if (login(username, password) == true)
            {
                login_choices(username);
            }
            else if (login(username, password) == false)
            {
                cout << "user does not exists\n";
                Sleep(6000);
            }
            system("cls");
            break;

        case 2:
            user_account.openaccount();
            break;

        }
    } while (main_choice<3);
    return 0;
}