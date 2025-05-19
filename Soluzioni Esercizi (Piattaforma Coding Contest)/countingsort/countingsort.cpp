#include<iostream>
#include<fstream>

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

void countingsort(int* A, int dim, ofstream &out){
    int min = findMin(A, dim);
    int max = findMax(A, dim);
    int k = max-min+1;
    int B[dim];
    int C[k];

    for(int i = 0; i<k; i++){
        C[i] = 0;
    }
    for(int i = 0; i < dim; i++){
        C[A[i] - min]++;
    }
    for(int i = 1; i < k; i++){
        C[i] += C[i-1];
    }
    for(int i = dim-1; i>=0; i--){
        B[C[A[i] - min]-1] = A[i];
        C[A[i]-min]--;
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
    int n;
    while(!in.eof()){
        in >> dim;
        int A[dim];
        for(int i = 0; i < dim; i++){
            in >> n;
            A[i] = n;
        }
        countingsort(A, dim, out);
    }

    in.close();
    out.close();
}