#include <iostream>
#include <fstream>
using namespace std;

class Student {
    int rollno;
    char div;
    string name, address;

    public:
    Student(){
        rollno = 0;
        name = "";
        address = "";
    }

    void input();
    void display();
    int getrollno(){
        return rollno;
    }
};

void Student::input(){
    cout<<"Enter Roll No: ";
    cin>>rollno;
    cout<<"Enter division: ";
    cin>>div;
    cout<<"Enter Name: ";
    cin>>name;
    cout<<"Enter Address: ";
    cin>>address;
}

void Student::display(){
    cout<<"Display Student: "<<endl;
    cout<<"Roll No: "<<rollno<<endl;
    cout<<"Division: "<<div<<endl;
    cout<<"Name: "<<name<<endl;
    cout<<"Address: "<<address<<endl<<endl;
}

class SequentialFile{
    fstream fs;
    Student sobj;

    public:
    void create();
    void add();
    void search();
    void deleteData();
    void print();
};

void SequentialFile::create(){
    char ch = 'y';

    fs.open("student_data.txt", ios::out|ios::binary);
    while(ch == 'y' || ch =='Y'){
        sobj.input();
        fs.write((char*)&sobj, sizeof(sobj));
        cout<<"Do you want to add more data: ";
        cin>>ch;
    }
    fs.close();
}

void SequentialFile::add(){
    fs.open("student_data.txt", ios::app|ios::binary);
    sobj.input();
    fs.write((char*)&sobj, sizeof(sobj));
    cout<<"Data Inserted Successfully"<<endl;
}

void SequentialFile::print(){
    fs.open("student_data.txt",ios::in|ios::binary);
    if(!fs){
        cout<<"No Data Found!!"<<endl;
    }
    else{
        fs.read((char*)&sobj, sizeof(sobj));
        while(!fs.eof()){
            sobj.display();
            fs.read((char*)&sobj, sizeof(sobj));
        }
    }
    fs.close();
}

void SequentialFile::search(){
    int n;
    cout<<"Enter the roll no to search: ";
    cin>>n;
    
    fs.open("student_data.txt", ios::in|ios::binary);
    if(!fs){
        cout<<"No Data Found!!"<<endl;
    }
    else{
        fs.read((char*)&sobj, sizeof(sobj));
        while(!fs.eof()){
            if(n == sobj.getrollno()){
                sobj.display();
                break;
            }
            fs.read((char*)&sobj, sizeof(sobj));
        }
    }
    fs.close();
}

void SequentialFile::deleteData() {
    int rollNumberToDelete;
    cout << "Enter the roll number to delete: ";
    cin >> rollNumberToDelete;

    ifstream fin("student_data.txt", ios::in | ios::binary);
    ofstream tempFile("temp.txt", ios::out | ios::binary);

    bool found = false;
    while (fin.read((char*)&sobj, sizeof(sobj))) {
        if (sobj.getrollno() == rollNumberToDelete) {
            cout << "Record deleted successfully!" << endl;
            found = true;
        } else {
            tempFile.write((char*)&sobj, sizeof(sobj));
        }
    }
    fin.close();
    tempFile.close();

    remove("student_data.txt");
    rename("temp.txt", "student_data.txt");

    if (!found) {
        cout << "Record not found!" << endl;
    }
}


int main(){
    int choice = 0;
    SequentialFile sqfile;

    do{
        cout<<"========== MENU =========="<<endl;
        cout<<"1. Create"<<endl;
        cout<<"2. Append"<<endl;
        cout<<"3. Print"<<endl;
        cout<<"4. Search"<<endl;
        cout<<"=========================="<<endl;
        cout<<"Enter Your Choice: ";
        cin>>choice;

        switch (choice)
        {
        case 1:
            sqfile.create();
            break;
        case 2:
            sqfile.add();
            break;
        case 3:
            sqfile.print();
            break;
        case 4:
            sqfile.search();
            break;
        case 5:
            sqfile.deleteData();
            break;
        default:
            break;
        }
    }while(choice != 7);
}