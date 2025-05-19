#include<iostream> 
#include<fstream>
#include<climits>

using namespace std;

template<class T>
class Node{
    public: 
        int peso;

        Node(){
            peso = INT_MAX;
        }

};

template<class T>
class Graph{
    public:
        int **edge;
        int *vertex;
        int n, c;

        Graph(int n){
            this->n=n;
            c = 0;
            edge = new int*[n];
            vertex = new int[n];
            for(int i = 0; i < n; i++){
                edge[i] = new int[n];
                vertex[i] = INT_MAX;
                for(int j = 0; j<n; j++){
                    edge[i][j] = INT_MAX;
                }
            }
        }


        void insertEdge(int u, int v, int p){
            if(v!=-1 && u!=-1){
                edge[u][v]=p;
            }
        }

        void relax(int s, int d, int peso){
            if(vertex[s] != INT_MAX){    
                int tmp = vertex[s]+peso;
                if(tmp < vertex[d]){
                    vertex[d] = tmp;
                }
            }
        }

        bool bellman_ford(int s, int k){
            vertex[s] = 0;
            for(int x = 0; x < k; x++){
                for(int i = 0; i<n; i++){
                    for(int j = 0; j<n; j++){
                        if(edge[i][j] != INT_MAX)
                            relax(i, j, edge[i][j]);
                    }      
                }
            }
            return true;
        }

        int peso(int d){
            return vertex[d];
        }
};

int main(){
    ifstream in; in.open("input.txt");
    ofstream out; out.open("output.txt");
    
    for(int A = 0; A<100; A++){
        int N=0, M=0, k=0;
        in >> N >> M >> k;
  
        Graph<int> g(N);
        int s, d;
        int w;
        char x;
        for(int i = 0; i<M; i++){
            in >> x >> s >> d >> w >> x;
            g.insertEdge(s, d, w);
        }
        in >> s >> d;
        if(g.bellman_ford(s, k)){
            if(g.peso(d) == INT_MAX){
                out << "inf." << endl;
            }else{
                out << g.peso(d) << endl;
            }
        }
    }

    in.close();
    out.close();
}