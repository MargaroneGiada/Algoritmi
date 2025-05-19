#include<iostream>
#include<fstream>
#include<climits>

using namespace std;

template<class T>
class Node{
    public:
        T value;
        int w;
        bool toCheck;  

        Node(){
            w = INT_MAX;
            toCheck = true;
        }

        Node(T k){
            value = k;
            w = INT_MAX;
            toCheck = true;
        }
};

template<class T>
class Graph{
    public:
        Node<T> *node;
        int **M;
        int n, c;

        Graph(int n){
            this->n = n;
            c = 0;
            M = new int*[n];
            for(int i = 0; i < n; i++){
                M[i] = new int[n];
                for(int j = 0; j < n; j++){
                    M[i][j]=INT_MAX;
                }
                M[i][i]=0;
            }
            node = new Node<T>[n];
        }

        int search(T k){
            for(int i = 0; i < c; i++){
                if(node[i].value == k){
                    return i;
                }
            }
            return -1;
        }

        void insertNode(T k){
            Node<T> n(k);
            node[c++] = n; 
        }

        void insertEdge(T u, T v, int w){
            int s = search(u);
            int d = search(v);
            if(s != -1 && d !=-1)    
                M[s][d] = w;
        }

        void relax(int s, int d, int w){
            if(node[s].w + w < node[d].w ){
                node[d].w = node[s].w + w;
            }
        }

        int findMin(){
            int min;
            for(int i = 0; i < c; i++){
                if(node[i].toCheck){
                    min = i;
                    break;
                }
            }
            for(int i=0; i < c; i++){
                if(node[i].toCheck && node[i].w < node[min].w)
                    min = i;
            }
            return min;
        }

        int dijkstra(T u, T v){
            int s = search(u);
            int d = search(v);
            node[s].w = 0;
            for(int i = 0; i < c; i++){
                int min = this->findMin();
                for(int j = 0; j < n; j++){
                    if(M[min][j] != INT_MAX){
                        relax(min, j, M[min][j]);
                    }
                }
                node[min].toCheck = false;
            }
            return node[d].w;
        }
};

int main(){
    ifstream in;
    in.open("input.txt");
    ofstream out;
    out.open("output.txt");

    for(int i = 0; i<100; i++){
        string type;
        int numVertici, numArchi;

        in >> numVertici >> numArchi >> type;
        if(type == "int"){
            Graph<int> graph(numVertici);

            for(int i=0; i<numVertici; i++){
                int key;
                in >> key;
                graph.insertNode(key);
            }
            char temp;
            int sorg, dest, peso;
            for(int i=0; i<numArchi; i++){
                in >> temp;
                in >> sorg >> dest >> peso;
                in >> temp;
                graph.insertEdge(sorg, dest, peso);
            }
            in >> sorg >> dest;
            int res = graph.dijkstra(sorg, dest);
            if(res == INT_MAX)
                out<<"inf."<<endl;
            else
                out<<res<<endl;
        }
        if(type == "double"){
            Graph<double> graph(numVertici);

            for(int i=0; i<numVertici; i++){
                double key;
                in >> key;
                graph.insertNode(key);
            }
            char temp;
            double sorg, dest;
            int peso;
            for(int i=0; i<numArchi; i++){
                in >> temp;
                in >> sorg >> dest >> peso;
                in >> temp;
                graph.insertEdge(sorg, dest, peso);
            }
            in >> sorg >> dest;
            int res = graph.dijkstra(sorg, dest);
            if(res == INT_MAX)
                out<<"inf."<<endl;
            else
                out<<res<<endl;
        }
    }

    in.close();
    out.close();
}
