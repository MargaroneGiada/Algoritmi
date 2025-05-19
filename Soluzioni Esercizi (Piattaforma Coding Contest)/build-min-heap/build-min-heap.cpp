#include<iostream>
#include<cmath>
#include<fstream>

using namespace std;

template<class T>
class Heap{
    private:
        int arraysize;
        int heapsize;
        T *A;

        int left(int i){return i << 1;}
        int right(int i){return (i << 1) | 1;}
        int parent(int i){return i >> 1;}

        void heapify(int i){
            int l = left(i);
            int r = right(i);
            int min = i;
            if(l < heapsize && A[l]<A[min]){
                min=l;
            }
            if(r < heapsize && A[r]<A[min]){
                min=r;
            }
            if(min != i){
                T temp = A[i];
                A[i]=A[min];
                A[min] = temp;
                heapify(min);
            }
        }

        public:
            Heap(int size){
                heapsize = 1;
                arraysize = size + 1;
                A = new T[arraysize];
            }

            void insert(T k){
                if(heapsize <= arraysize){
                    A[heapsize] = k;
                    heapsize++;
                }
            }

            void builminheap(){
                for(int i = floor(heapsize/2); i >= 1; i--){
                    heapify(i);
                }
            }

            void print(ofstream &out){
                for(int i = 1; i<heapsize; i++){
                    out << A[i] << " ";
                }
                out << endl;
            }
};

int main(){
    ifstream in;
    in.open("input.txt");
    ofstream out;
    out.open("output.txt");
    string t = "";
    int N = 0;
    for (int i = 0; i < 100; i++)
    {
        in >> t;
        if (t == "char")
        {
            in >> N;
            Heap<char> *h = new Heap<char>(N);
            char x = ' ';
            for (int i = 0; i < N; i++)
            {
                in >> x;
                h->insert(x);
            }
            h->builminheap();
            h->print(out);
        }else if (t == "int")
        {
            in >> N;
            Heap<int> *h = new Heap<int>(N);
            int x = 0;
            for (int i = 0; i < N; i++)
            {
                in >> x;
                h->insert(x);
            }
            h->builminheap();
            h->print(out);
        }else if (t == "bool")
        {
            in >> N;
            Heap<bool> *h = new Heap<bool>(N);
            bool x;
            for (int i = 0; i < N; i++)
            {
                in >> x;
                h->insert(x);
            }
            h->builminheap();
            h->print(out);
        }
        else
        {
            in >> N;
            Heap<double> *h = new Heap<double>(N);
            double x = 0;
            for (int i = 0; i < N; i++)
            {
                in >> x;
                h->insert(x);
            }
            h->builminheap();
            h->print(out);
        }
    }
    in.close();
    out.close();
    return 0;
}