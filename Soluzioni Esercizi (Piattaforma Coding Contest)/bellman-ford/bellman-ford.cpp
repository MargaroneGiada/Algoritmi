#include<iostream> 
#include<fstream>
#include<climits>

using namespace std;

template<class T>
class Node{
    public: 
        int peso;
        T k;

        Node(T key){
            this->k = key;
            peso = INT_MAX;
        }

};

template<class T>
class Graph{
    public:
        int **edge;
        Node<T> **vertex;
        int n, c;

        Graph(int n){
            this->n=n;
            c = 0;
            edge = new int*[n];
            vertex = new Node<T>*[n];
            for(int i = 0; i < n; i++){
                edge[i] = new int[n];
                for(int j = 0; j<n; j++){
                    edge[i][j] = INT_MAX;
                }
            }
        }

        int search(T k){
            for(int i = 0; i < n; i++){
                if(vertex[i]->k == k){
                    return i;
                }
            }
            return -1;
        }

        void insertEdge(T u, T v, int p){
            int s = search(u);
            int d = search(v);
            if(s!=-1 && d!=-1){
                edge[s][d]=p;
            }
        }

        void insertVertex(T k){
            vertex[c++] = new Node<T>(k);
        }

        void relax(int s, int d, int peso){
            if(vertex[s]->peso != INT_MAX){    
                int tmp = vertex[s]->peso+peso;
                if(tmp < vertex[d]->peso){
                    vertex[d]->peso = tmp;
                }
            }
        }

        bool bellman_ford(T source){
            int s = search(source);
            vertex[s]->peso = 0;
            for(int x = 0; x < n-1; x++){
                for(int i = 0; i<n; i++){
                    for(int j = 0; j<n; j++){
                        if(edge[i][j] != INT_MAX)
                            relax(i, j, edge[i][j]);
                    }      
                }
            }
            for(int i = 0; i<n; i++){
                for(int j = 0; j<n; j++){
                    if(edge[i][j] != INT_MAX && vertex[j]->peso != INT_MAX && vertex[i]->peso != INT_MAX){
                        if(vertex[j]->peso > vertex[i]->peso + edge[i][j]){
                            return false;
                        }
                    }
                }
            }
            return true;
        }

        int peso(T d){
            return vertex[search(d)]->peso;
        }
};

int main(){
    ifstream in; in.open("input.txt");
    ofstream out; out.open("output.txt");
    
    for(int k = 0; k<100; k++){
        int N=0, M=0;
        string type;
        in >> N >> M >> type;
        if(type == "int"){
            int c;
            Graph<int> g(N);
            for(int i = 0; i<N; i++){
                in >> c;
                g.insertVertex(c);
            }
            int s, d;
            int w;
            char x;
            for(int i = 0; i<M; i++){
                in >> x >> s >> d >> w >> x;
                g.insertEdge(s, d, w);
            }
            in >> s >> d;
            if(g.bellman_ford(s)){
                if(g.peso(d) == INT_MAX){
                    out << "inf." << endl;
                }else{
                    out << g.peso(d) << endl;
                }
            }else{
                out << "undef." << endl;
            }
        }else{
            double c;
            Graph<double> g(N);
            for(int i = 0; i<N; i++){
                in >> c;
                g.insertVertex(c);
            }
            double s, d;
            int w;
            char x;
            for(int i = 0; i<M; i++){
                in >> x >> s >> d >> w >> x;
                g.insertEdge(s, d, w);
            }
            in >> s >> d;
            if(g.bellman_ford(s)){
                if(g.peso(d) == INT_MAX){
                    out << "inf." << endl;
                }else{
                    out << g.peso(d) << endl;
                }
            }else{
                out << "undef." << endl;
            }
        }
        cout << N << " " << M << " " << type << endl;
    }

    in.close();
    out.close();
}