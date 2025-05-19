#include<iostream>
#include<fstream>

using namespace std;

template <class T>
class vertice{
    public: 
        T key;
        int peso;
        bool toCheck;

        vertice(T k){
            this->key = k;
            peso = INT_MAX;
            toCheck = true;
        }
};

template<class T>
class Grafo{
    public:
        int **archi;
        vertice<T> **vertici;
        int numVertici;
        int counter;

        Grafo(int num){
            numVertici = num;
            counter = 0;

            vertici = new vertice<T>*[numVertici];
            archi = new int*[numVertici];

            for(int i=0; i<numVertici; i++)
            archi[i] = new int[numVertici];

                for(int i=0; i<numVertici; i++)
                    for(int j=0; j<numVertici; j++)
                        archi[i][j] = INT_MAX;
        }

        int ricerca(T key){
            for(int i = 0; i < counter; i++){
                if(vertici[i]->key == key)
                    return i;
            }
            return -1;
        }

        //ritorna l'indice del primo vertice da controllare che ha peso minimo
        int getMin(){
            int min;
            for(int i = 0; i < counter; i++){
                if(vertici[i]->toCheck){
                    min = i;
                    break;
                }
            }
            for(int i = 0; i < counter; i++){
                if(vertici[i]->toCheck && vertici[i]->peso < vertici[min]->peso){
                    min = i;
                }
            }
            return min;
        }

        void relax(int s, int d, int peso){
            int tempPeso = vertici[s]->peso + peso;
            if(tempPeso < vertici[d]->peso)
                vertici[d]->peso = tempPeso;
        }

        void insertVertice(T key){
            vertice<T> *elem = new vertice<T>(key);
            vertici[counter++] = elem;
        }

        void insertArco(T x, T y, int peso){
            int s = ricerca(x);
            int d = ricerca(y);

            if(s != -1 && d != -1)
                archi[s][d] = peso;
        }

        int dijkstra(T s, T d){
            int source = ricerca(s);
            int dest = ricerca(d);
            int checked = 0;

            vertici[source]->peso = 0;
            while(checked < counter){
                int min = getMin();
                for(int i = 0; i < numVertici; i++){
                    if(archi[min][i] != INT_MAX){
                        relax(min, i, archi[min][i]);
                    }
                }
                vertici[min]->toCheck = false;
                checked++;
            }

            return vertici[dest]->peso;
        }
};

int main(){
    ifstream in("input.txt");
    ofstream out("output.txt");

    string type;
    int numVertici, numArchi;
    while(!in.eof()){
        in >> numVertici >> numArchi >> type;

        if(type == "int"){
            Grafo<int> g(numVertici);

            for(int i = 0; i < numVertici; i++){
                int key;
                in >> key;
                g.insertVertice(key);
            }

            char x;
            int s, d, w;
            for(int i = 0; i < numArchi; i++){
                in >> x >> s >> d >> w >> x;
                g.insertArco(s, d, w);
            }
            in >> s >> d;
            int ris = g.dijkstra(s, d);
            if(ris == INT_MAX)
                out << "inf." << endl;
            else
                out << ris << endl;
        }else if(type == "double"){
            Grafo<double> g(numVertici);

            for(int i = 0; i < numVertici; i++){
                double key;
                in >> key;
                g.insertVertice(key);
            }

            char x;
            double s, d;
            int w;
            for(int i = 0; i < numArchi; i++){
                in >> x >> s >> d >> w >> x;
                g.insertArco(s, d, w);
            }
            in >> s >> d;
            int ris = g.dijkstra(s, d);
            if(ris == INT_MAX)
                out << "inf." << endl;
            else
                out << ris << endl;
        }
    }
}