#include <iostream>
using namespace std;

class Graph
{
    int v;
    int** adjMatrix;

public:
    Graph()
    {
        v = 0;
        adjMatrix = NULL;
    }

    Graph(int ver)
    {
        v = ver;
        adjMatrix = new int*[v];
        for (int i = 0; i < ver; i++)
        {
            adjMatrix[i] = new int[v];
            for (int j = 0; j < ver; j++)
            {
                adjMatrix[i][j] = 0;
            }

        }
    }

    void setV(int ver)
    {
        v = ver;
        adjMatrix = new int *[v];
        for (int i = 0; i < ver; i++)
        {
            adjMatrix[i] = new int[v];
            for (int j = 0; j < ver; j++)
            {
                adjMatrix[i][j] = 0;
            }
        }
    }

    void addEdge();
    void print();
    void prims_mst();
};

void Graph::addEdge()
{
    int source, dest, wt;
    cout << "Enter Source: ";
    cin >> source;
    cout << "Enter Destination: ";
    cin >> dest;
    cout << "Enter Weight: ";
    cin >> wt;

    while (true)
    {
        try
        {
            if (source < 0 || source >= v || dest < 0 || dest >= v)
            {
                throw 1;
            }
            adjMatrix[source][dest] = wt;
            adjMatrix[dest][source] = wt;
            return;
        }
        catch (int error)
        {
            cout << "# Error : Vertex out of range" << endl;
            return;
        }
    }
}

void Graph::print()
{
    cout << "   \t";
    for (int i = 0; i < v; ++i)
    {
        cout << i << "| \t";
    }
    cout << endl;
    for (int i = 0; i < v; ++i)
    {
        cout << i << "| \t";
        for (int j = 0; j < v; ++j)
        {
            cout << adjMatrix[i][j] << "  \t";
        }
        cout << endl;
    }
}

int min_key(int V, int* key, bool* mstSet){
    int min = 10000;
    int minIndex = 0;

    for (int v=0; v<V; ++v){
        if (mstSet[v] == false && key[v] < min){
            min = key[v];
            minIndex = v;
        }
    }
    return minIndex;
}
void print_mst(int V, int* parent, int** weights){
    cout << "\nEdge \tWeight\n";
    int miniCost = 0;
    for (int i=1; i<V; ++i){
        cout << parent[i] << " - " << i << "\t" << weights[i][parent[i]] << endl;
        miniCost += weights[i][parent[i]];
    }

    cout<<"The Minimum Cost is: "<< miniCost<<endl;
}
void Graph::prims_mst(){
    int parent[v], key[v];
    bool mst[v];
    for(int i=0; i<v; ++i){
        key[i] = 10000;       
        mst[i] = false;      
    }

    key[0] = 0;
    parent[0] = -1;

    for(int i = 0;i < v; i++){
        int mini = min_key(v, key, mst);
        mst[mini] = true;
            for(int j = 0; j<v; j++){
                if(mst[j]==false && adjMatrix[mini][j] > 0 && adjMatrix[mini][j] < key[j]){
                    parent[j] = mini;
                    key[j] = adjMatrix[mini][j];
                }
            }
    }
    print_mst(v,parent,adjMatrix);
}



int main()
{
    int choice = 0;
    Graph g;

    do
    {
        cout << "========== MENU ==========" << endl;
        cout << "1.Add Vertices" << endl;
        cout << "2.Enter Data" << endl;
        cout << "3.Read Data" << endl;
        cout << "4.Prims" << endl;
        cout << "7.Exit" << endl;
        cout << "==========================" << endl;
        cout << "Enter Your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            int v;
            cout << "Enter No of Vertices: ";
            cin >> v;
            g.setV(v);
            break;
        case 2:
            g.addEdge();
            break;
        case 3:
            g.print();
            break;
        case 4:
            g.prims_mst();
            break;
        default:
            break;
        }
    } while (choice != 7);

    return 0;
}