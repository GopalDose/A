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
        string src, dest;
        cout<<"Enter 1st: ";
        cin>> src;
        cout<<"Enter 2nd: ";
        cin>>dest;

        vc[src].push_back(dest);
        vc[dest].push_back(src);
        cout<<"The Edge is added successfully"<<endl;
    }

    void printGraph(){
        for(auto it : vc){
            cout<<"The Adjacency list for "<< it.first <<" => ";
            int degree = 0;
            for(auto neig : it.second){
                cout<<neig<<" ";
                degree++;
            }
            cout<<" Degree: "<<degree;
        cout<<endl;
        }
    }

    void BFS(string start){
        map<string, bool> visit;
        queue<string> q;
        q.push(start);
        visit[start] = true;

        while(!q.empty()){
            string curr = q.front();
            q.pop();

            cout<<curr<<" ";
            for(auto it : vc[curr]){
                if(!visit[it] && vc.find(it) != vc.end()){
                    visit[it] = true;
                    q.push(it);
                }
            }
        }
    }

    void DFS(string start){
        map<string, bool> visit;
        stack<string> s;
        s.push(start);
        visit[start] = true;

        while(!s.empty()){
            string curr = s.top();
            s.pop();

            cout<<curr<<" ";
            for(auto it : vc[curr]){
                if(!visit[it] && vc.find(it) != vc.end()){
                    visit[it] = true;
                    s.push(it);
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
            g.printGraph();
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