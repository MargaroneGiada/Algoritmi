#include<iostream>
#include<fstream>

using namespace std;

#define R 1
#define B 0

template<class T>
class Nodo{
    public:
        T elemento;
        Nodo<T>* padre;
        Nodo<T>* dx;
        Nodo<T>* sx;
        bool colore;

        Nodo(T x){
            elemento = x;
            padre = NULL;
            dx = NULL;
            sx = NULL;
            colore = R;
        }

        Nodo(){}
        
};

template<class T>
class RBTree{
    public:
        Nodo<T>* radice;

        RBTree(){radice = NULL;}

        void Trapianta(Nodo<T>* x, Nodo<T>* y){
            if(x->padre == NULL){
                radice = y;
            }
            else if(x->padre->dx = x){
                x->padre->dx = y;
            }else{
                x->padre->sx = y;
            }

            if(y != NULL){
                y->padre = x->padre;
            }
        }

        void rLeft(Nodo<T>* x){
            if(x != NULL){
                Nodo<T>* y = x->dx;
                if( y != NULL){
                    x->dx = y->sx;
                    if(x->dx !=NULL){
                        x->dx->padre = x;
                    }

                    Trapianta(x, y);

                    x->padre = y;
                    y->sx = x;
                }
            }

        }

        void rRight(Nodo<T>* x){
            if(x != NULL){
                Nodo<T>* y = x->sx;
                if( y != NULL){
                    x->sx = y->dx;
                    if(x->sx !=NULL){
                        x->sx->padre = x;
                    }

                    Trapianta(x, y);

                    x->padre = y;
                    y->dx = x;
                }
            }

        } 

        void Insert(T x){
            Nodo<T>* nuovo = new Nodo<T>(x);

            Nodo<T>* iter = radice;
            Nodo<T>* tmp = NULL;

            while(iter != NULL){
                tmp = iter;

                if(x > iter->elemento){
                    iter = iter->dx;
                }else{
                    iter = iter->sx;
                }
            }

            nuovo->padre = tmp;

            if(tmp == NULL){
                radice = nuovo;
            }else if( x > tmp->elemento){
                tmp->dx = nuovo;
            }else{
                tmp->sx = nuovo;
            }

            InsertFixUp(nuovo);
        }

        void InsertFixUp(Nodo<T>* z){
            if(z->padre != NULL && z->padre->colore == B){
                return;
            }
            if(z == radice){
                z->colore = B;
                return;
            }

            Nodo<T>* padre = z->padre;
            Nodo<T>* nonno = padre->padre;
            Nodo<T>* zio = nonno->dx;
            if(nonno->dx == padre){
                zio = nonno->sx;
            }

            if(zio != NULL && zio->colore == R){
                zio->colore = R;
                padre->colore = R;
                nonno->colore = B;
                InsertFixUp(nonno);
                return;
            }

            if(padre == nonno->sx){
                if(padre->dx == z){
                    rLeft(padre);
                    padre = z;
                    z = padre->sx;
                }

                rRight(nonno);
                padre->colore = B;
                nonno->colore = R;
                return;
            }else{
                if(padre->sx == z){
                    rRight(padre);
                    padre = z;
                    z = padre->dx;
                }

                rLeft(nonno);
                padre->colore = B;
                nonno->colore = R;
                return;
            }
        }

        int Altezza(Nodo<T>* n){
            if(n == NULL){
                return 0;
            }
            int s = Altezza(n->sx);
            int d = Altezza(n->dx);

            return 1 + max(s,d);
        }

        int getAltezza(){return Altezza(radice);}
        
};

int main(){
    ifstream in("input->txt");
    ofstream out("output->txt");

    for(int i = 0; i<100; i++){
        string type;
        in >> type;
        int n; 
        in >> n;

        if(type == "int" || type == "bool"){
            RBTree<int> *t = new RBTree<int>();

            for(int j = 0; j<n; j++){
                int tmp; in >> tmp;
                t->Insert(tmp);
            }

            out << t->getAltezza() << endl;
        }else if(type == "char"){
            RBTree<char> *t = new RBTree<char>();

            for(int j = 0; j<n; j++){
                char tmp; in >> tmp;
                t->Insert(tmp);
            }

            out << t->getAltezza() << endl;
        }else{
            RBTree<double> *t = new RBTree<double>();

            for(int j = 0; j<n; j++){
                double tmp; in >> tmp;
                t->Insert(tmp);
            }

            out << t->getAltezza() << endl;
        }
    }
}