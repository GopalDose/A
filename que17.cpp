#include <bits/stdc++.h>
using namespace std;

class Graph{
    int vertices;
    map<string, vector<string>> vc;

    public:
    Graph(int v){
        vertices = v;
    }

    void addEdge(){
        string source, destination;
        cout<<"Enter city 1: ";
        cin>>source;
        cout<<"Enter city 2: ";
        cin>>destination;

        vc[source].push_back(destination);
        vc[destination].push_back(source);

        cout<<"The Edege Inserted Successfully ...." <<endl;
    }

    void printAdj(){
        for(auto it : vc){
            cout << "The Adjacency list for "<< it.first << "--->";
            for(auto nei : it.second){
                cout<< nei << " ";
            }
            cout<<endl;
        }
    }

    void BFS(string start){
        map<string,bool> visit;
        queue<string> s;
        visit[start] = true;
        s.push(start);

        while(!s.empty()){
            string curr = s.front();
            s.pop();
            cout<< curr <<" ";
            for( auto neigh : vc[curr]){
                if(!visit[neigh] && vc.find(neigh) != vc.end()){
                    visit[neigh] = true;
                    s.push(neigh);
                }
            }
        }
    }

    void DFS(string start){
        map<string,bool> visit;
        stack<string> s;
        visit[start] = true;
        s.push(start);

        while(!s.empty()){
            string curr = s.top();
            s.pop();
            cout<< curr <<" ";
            for( auto neigh : vc[curr]){
                if(!visit[neigh] && vc.find(neigh) != vc.end()){
                    visit[neigh] = true;
                    s.push(neigh);
                }
            }
        }
    }
};

int main(){
    int ver;
    cout<<"Enter No of Vertices: ";
    cin>> ver;

    Graph g(ver);
    string src;
    int choice = 0;

    do{
        cout<<"========== MENU =========="<<endl;
        cout<<"1. Add Edge"<<endl;
        cout<<"2. Print Adjacency List"<<endl;
        cout<<"3. DFS"<<endl;
        cout<<"4. BFS"<<endl;
        cout<<"7. exit"<<endl;
        cout<<"========================="<<endl;
        cout<<"Enter Your Choice: ";
        cin>> choice;

        switch (choice)
        {
        case 1:
            g.addEdge();
            break;
        case 2:
            g.printAdj();
            break;
        case 3:
            cout<<"Enter The Starting: ";
            cin>>src;
            g.DFS(src);
            cout<<endl;
            break;
        case 4:
            cout<<"Enter The Starting: ";
            cin>>src;
            g.BFS(src);
            cout<<endl;
            break;
        default:
            break;
        }
    }while(choice != 7);
}