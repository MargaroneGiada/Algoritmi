#include<iostream>
#include<fstream>

using namespace std; 

class Hash{
    public:
        int dim;
        int *table;

        Hash(int n){
            dim = n;
            table = new int[dim];
            for(int i = 0; i < dim; i++){
                table[i] = 0;
            }
        }

        void insert(int k){
            table[k % dim]++;
        }

        void print(ofstream &out){
            for(int i = 0; i < dim; i++){
                out << table[i] << " ";
            }
            out << endl;
        }
};

int main(){
    ifstream in; in.open("input.txt");
    ofstream out; out.open("output.txt");

    string type;
    int dim, n;
    for(int i = 0; i<100; i++){
        in >> type >> dim >> n;
        Hash h(dim);
        for(int i = 0; i<n; i++){
            if(type == "char"){
                char c;
                in >> c;
                h.insert((int)c);
            }else{
                double d;
                in >> d;
                h.insert((int)d);
            }
        }
        h.print(out);
    }
}