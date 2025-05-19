#include<iostream>
#include<fstream>

using namespace std;

template<class T>
class Heap{
    private:
        int arraysize, heapsize;
        T* A;
        int heapifytimes;

        void heapify(int i){
            heapifytimes++;
            int l = i << 1;
            int r = (i << 1) | 1;
            int min = i;
            if(l <= heapsize && A[l]<A[min]){
                min = l;
            }
            if(r <= heapsize && A[r]<A[min]){
                min = r;
            }
            if(min != i){
                T temp = A[i];
                A[i] = A[min];
                A[min] = temp;
                heapify(min);
            }
        }
    
    public:
        Heap(int size){
            arraysize = size+1;
            heapsize = 0;
            A  = new T[arraysize];
            heapifytimes = 0;
        }

        void heapsort(){
            BuildMinHeap();
            int hsize = heapsize;
            for(int i = hsize; i >= 2; i--){
                T temp = A[1];
                A[1] = A[i];
                A[i] = temp;
                heapsize--;
                heapify(1);
            }
            heapsize = hsize;
        }
    
        void BuildMinHeap()
        {
            for (int i = (heapsize >> 1); i >= 1; i--)
                heapify(i);
        }

        void insert(T k){
            if (heapsize + 1 >= arraysize)
                return;
            A[++heapsize] = k;
        }

        void printHeapsort(fstream &out){
            this->heapsort();
            out << heapifytimes << " ";
            for(int i = 1; i < heapsize + 1; i++){
                out << A[i] << " "; 
            }
            out << endl;
        }
};

int main(){
    fstream in, out;
    in.open("input.txt", fstream::in);
    out.open("output.txt", fstream::out);

    int size; 
    string type;
    for(int i = 0; i < 100; i++){
        in >> type >> size;
        if(type == "char"){
            Heap<char> *h = new Heap<char>(size);
            char c = ' ';
            for(int j = 0; j<size; j++){
                in >> c;
                h->insert(c);
            }
            h->printHeapsort(out);
        }else{
            Heap<double> *h = new Heap<double>(size);
            double c;
            for(int j = 0; j<size; j++){
                in >> c;
                h->insert(c);
            }
            h->printHeapsort(out);
        }
    }
}
