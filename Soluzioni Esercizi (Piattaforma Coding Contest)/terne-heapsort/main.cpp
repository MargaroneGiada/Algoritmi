#include<iostream>
#include<fstream>

using namespace std;

template<class T>
class Terna{
    public:
    T a, b, c;

    Terna(){}

    Terna(int a, int b, int c){
        this->a = a;
        this->b = b;
        this->c = c;
    }
};

template<class T>
bool operator>(Terna<T> t1, Terna<T> t2){
    if(t1.a > t2.a){return true;}
    if(t1.a == t2.a && t1.b > t2.b){return true;}
    if(t1.a == t2.a && t1.b == t2.b && t1.c > t2.c){return true;}
    return false;
}

template<class T>
ofstream& operator<<(ofstream& out, Terna<T> t){
    out << "(" << t.a << " " << t.b << " " << t.c << ")";
    return out;
}

template<class T>
ostream& operator<<(ostream& out, Terna<T> t){
    out << "(" << t.a << " " << t.b << " " << t.c << ")";
    return out;
}

template<class T>
class Heap{
    public:
        int heapsize;
        T* heap;
        int heapifytimes;

        Heap(int size, T* array){
            heapifytimes = 0;
            this->heapsize = size;
            this->heap = array;
            heap--;
        }

        int left(int i) {return i << 1;}
        int right(int i) {return (i << 1) | 1;}
        int parent(int i) {return i >> 1;}

        void swap(int a, int b){
            T tmp = heap[a];
            heap[a]= heap[b];
            heap[b] = tmp;
        }

        void heapify(int i){
            heapifytimes++;
            int l = left(i);
            int r = right(i);
            int max = i;

            if (l <= heapsize && heap[l] > heap[max]){
                max = l;
            }

            if (r <= heapsize && heap[r] > heap[max]){
                max = r;
            }

            if (max != i){
                swap(max, i);
                heapify(max);
            }
        }

        void buildMaxHeap(){
            for(int i = (heapsize >> 1); i >= 1 ; i--){
                heapify(i);
            }
        }

        void heapsort(){
            buildMaxHeap();
            int tmp = heapsize;
            for(int i = heapsize; i>=2; i--){
                swap(1, i);
                heapsize--;
                heapify(1);
            }
            heapsize = tmp;
        }

        void print(ofstream &o){
            
            o << heapifytimes << " ";
            for(int i = 1; i < heapsize+1; i++){
                o << heap[i] << " ";
            }
            o << endl;
        }
};

template<class T>
void perform(int size, ifstream &in, ofstream &out){
    char x;
    T a, b, c;

    Terna<T> array[size];
    for(int i = 0; i < size; i++){
        in >> x >> a >> b >> c >> x;
        array[i].a=a;
        array[i].b=b;
        array[i].c=c;
        cout << array[i] << endl;
    }
    Heap<Terna<T>> h(size, array);
    h.heapsort();
    h.print(out);

}

int main(){

    ifstream in;
    in.open("input.txt", fstream::in);
    ofstream out;
    out.open("output.txt", fstream::out);

    string type;
    int size;
    while(!in.eof()){
        in >> type >> size;
        cout << type << " " << size << endl;
        if(type == "int"){
            cout << "type int" << endl;
            perform<int>(size, in, out);
        }
        else if(type == "bool"){
            cout << "type bool" << endl;
            perform<bool>(size, in, out);
        }
        else if(type == "char"){
            perform<char>(size, in, out);
        }
        else if(type == "double"){
            perform<double>(size, in, out);
        }
    }

    in.close();
    out.close();
}
