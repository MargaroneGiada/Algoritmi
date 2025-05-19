#include<iostream>
#include<fstream>
#include <typeinfo>

using namespace std;

template<class T>
class Coppia{
    public:
        T i, j;
        Coppia(){}
        Coppia(T x, T y){
            i = x;
            j = y;
        }
 
};

template<class T>
bool operator>(Coppia<T> c1, Coppia<T> c2){
    if(c1.i > c2.i){return true;}
    else if(c1.i == c2.i && c1.j > c2.j){return true;}
    return false;
}  

template <typename T>
ofstream &operator<<(ofstream &o, Coppia<T> c)
{
    o << "(" << c.i << " " << c.j << ")";
    return o;
}


template <typename T>
T cast(string val)
{
    if (typeid(T) == typeid(int) || typeid(T) == typeid(bool))
    {
        return stoi(val);
    }
    else if (typeid(T) == typeid(char))
    {
        return val[0];
    }
    else if (typeid(T) == typeid(double))
    {
        return stod(val);
    }
    return 0;
}

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
            int max = i;
            if(l <= heapsize && A[l]>A[max]){
                max = l;
            }
            if(r <= heapsize && A[r]>A[max]){
                max = r;
            }
            if(max != i){
                T temp = A[i];
                A[i] = A[max];
                A[max] = temp;
                heapify(max);
            }
        }
    
    public:
        Heap(T* arr, int size){
            arraysize = size;
            heapsize = size;
            A = arr;
            A--;
            heapifytimes = 0;
            cout << "created" << endl;
        }

        void heapsort(){
            BuildMaxHeap();
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
    
        void BuildMaxHeap()
        {
            for (int i = (heapsize >> 1); i >= 1; i--)
                heapify(i);
        }

        void insert(T k){
            if (heapsize + 1 >= arraysize)
                return;
            A[++heapsize] = k;
        }

        void printHeapsort(ofstream &out){
            this->heapsort();
            out << heapifytimes << " ";
            for(int i = 1; i < heapsize + 1; i++){
                out << A[i] << " "; 
            }
            out << endl;
        }
};

template<class T>
void do_it(ifstream &in, ofstream &o){
    int n;
    in >> n;
    cout << n << endl;
    char ch;
    T x, y;
    Coppia<T> arr[n];
    for(int i = 0; i<n; i++){
        in >> ch;
        in >> x ;        
        in >> y ;        
        in >> ch;        
        arr[i].i = x;
        arr[i].j = y;
    }
    Heap<Coppia<T>> h(arr, n);
    h.printHeapsort(o);
}

int main(){
    ifstream in;
    ofstream out;
    in.open("input.txt");
    out.open("output.txt");

    int size; 
    string type;
    for(int i = 0; i < 100; i++){
        in >> type;
        if(type == "char"){
            cout << "qui" << endl;
            do_it<char>(in, out);
        }else{
            cout << "qui" << endl;
            do_it<double>(in, out);
        }
    }

    in.close();
    out.close();
}
