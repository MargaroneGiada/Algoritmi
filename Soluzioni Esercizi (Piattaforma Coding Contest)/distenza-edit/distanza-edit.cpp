#include<iostream>
#include<fstream>

using namespace std;

int min(int a, int b, int c){
    int min = a;
    if(min > b){
        min = b;
    }
    if(min > c){
        min = c;
    }
    return min;
}

int lcs(string A, int n, string B, int m){
    int **M = new int*[m + 1];
    for(int i = 0; i <= m; i++){
        M[i] = new int [n + 1];        
    }
    for(int i = 0; i <= m; i++){
        M[i][0] = i;        
    }
    for(int i = 1; i <= n; i++){
        M[0][i] = i;
    }
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            if(A[i-1] == B[j-1])
            {
                M[j][i] = M[j - 1][i - 1];
            }else{
                M[j][i] = min(M[j-1][i-1], M[j-1][i], M[j][i-1])+1; //notare +1 alla fine
            }
        }
    }
    int r = M[m][n];

    return r;
}

int main(){
    ifstream in; in.open("input.txt");
    ofstream out; out.open("output.txt");

    int n=0, m=0;
    string A="", B="";
    for(int i = 0; i < 100; i++){
        in >> n >> m >> A >> B;
        out << lcs(A, n, B, m) << endl;
    }

    in.close();
    out.close();
}