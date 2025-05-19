#include<iostream>
#include<fstream>
#include<typeinfo>

using namespace std;

int findMin(int* A, int dim){
    int min = A[0];
    for(int i = 0; i < dim; i++){
        if(A[i] < min){
            min = A[i];
        }
    }
    return min;
}


int findMax(int* A, int dim){
    int max = A[0];
    for(int i = 0; i < dim; i++){
        if(A[i] > max){
            max = A[i];
        }
    }
    return max;
}

template<class T>
void countingsort(T* A, int dim, ofstream &out){
    int X[dim];
    T B[dim];

    for(int i = 0; i < dim; i++){
        if(typeid(T) == typeid(double)){
            X[i] = (int)((A[i]*101)/10);
            cout << X[i] << " - " << A[i]*100 << endl;
        }
        else
            X[i] = (A[i]);
    }
    int min = findMin(X, dim);
    int max = findMax(X, dim);
    int k = max-min+1;
    int C[k];
    for(int i = 0; i<k; i++){
        C[i] = 0;
    }
    for(int i = 0; i < dim; i++){
        C[X[i] - min]++;
    }
    for(int i = 1; i < k; i++){
        C[i] += C[i-1];
    }
    for(int i = dim-1; i>=0; i--){
        B[C[X[i] - min]-1] = A[i];
        C[X[i]-min]--;
    } 
    for(int i = 0; i < k; i++){
        out << C[i] << " ";
    }
    for(int i = 0; i < dim; i++){
        out << B[i] << " ";
    }
    out << endl;
}

int main(){
    ifstream in;
    ofstream out;
    in.open("input.txt");
    out.open("output.txt");

    int dim;
    string type;
    while(!in.eof()){
        in >> type >> dim;
        if(type == "char"){
            char n;
            char A[dim];
            for(int i = 0; i < dim; i++){
                in >> n;
                A[i] = n;
            }
            countingsort<char>(A, dim, out);
        }else if(type == "double"){
            double n;
            double A[dim];
            for(int i = 0; i < dim; i++){
                in >> n;
                A[i] = n;
            }
            countingsort<double>(A, dim, out);
        }else{
            int n;
            int A[dim];
            for(int i = 0; i < dim; i++){
                in >> n;
                A[i] = n;
            }
            countingsort<int>(A, dim, out);
        }
        
    }

    in.close();
    out.close();
}