#include <iostream>
#include <fstream>
using namespace std;

class Hash
{
    int addr;

public:
    friend class DirectFile;
};

class DirectFile
{
    int empId;
    string name;
    int salary;
    Hash ht[10]; 

public:
    DirectFile()
    {
        for (int i = 0; i < 10; i++)
        {
            ht[i].addr = -1;
        }
    }

    void adddata()
    {
        int num = 0;
        cout << "Enter No of records to Save in file: ";
        cin >> num;
        ofstream fout("Records.txt", ios::out);
        for (int i = 0; i < num; i++)
        {
            cout << "Enter Emp ID: ";
            cin >> empId;
            cout << "Enter Emp Name: ";
            cin >> name;
            cout << "Enter Emp Salary: ";
            cin >> salary;

            int loc = fout.tellp();
            int index = empId % 10;
            ht[index].addr = loc;
            fout << empId<<" "<< name << " "<< salary << endl;
            cout << "Data Saved Successfully....." << endl;
        }
        fout.close();
    }

    void displaydata()
    {
        char buffer[40];
        fstream fin("Records.txt", ios::in);
        fin.seekg(0, ios::beg);
        while (!fin.eof())
        {
            fin.getline(buffer, 40);
            cout << buffer << endl;
        }

        fin.close();
    }

    void search(){
        int em;
        cout<<"Enter Emp ID to search: ";
        cin>>em;

        int index = em%10;
        int loc = ht[index].addr;

        fstream fin("Records.txt", ios::in);
        char buffer[40];
        fin.seekg(loc, ios::beg);
        fin.getline(buffer, 40);
        cout<<buffer<<endl;
    }
};

int main(){
    int choice = 0;
    DirectFile df;

    do{
        cout<<"========== MENU =========="<<endl;
        cout<<"1.Write In file"<<endl;
        cout<<"2.Read from file"<<endl;
        cout<<"3.Search In file"<<endl;
        cout<<"=========================="<<endl;
        cout<<"Enter Your choice: ";
        cin>>choice;

        switch (choice) 
        {
        case 1:
            df.adddata();
            break;
        case 2:
            df.displaydata();
            break;
        case 3:
            df.search();
            break;
        default:
            break;
        }
    }while(choice != 7);
}