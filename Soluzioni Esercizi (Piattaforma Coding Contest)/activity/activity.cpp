#include<iostream>
#include<fstream>

using namespace std;

class Activity{
    public:
        int s, f, t;

        Activity(int x, int y){
            s = x; 
            f = y;
            t = f-s;
        }

        Activity(){
        }
};

void ordina(Activity *A, int n){
    for(int i=0; i<n; i++){
        for(int j=0; j<n-1; j++) {
            if(A[j].f>A[j+1].f){
                Activity tmp = A[j];
                A[j] = A[j+1];
                A[j+1] = tmp;
            }
        }
        
    }
}

int lastActivity(Activity *A, int i){
    int k = i;
    for(int j = i-1; j>=0; j--){
        if(A[j].f <= A[k].s){
            return j;
        }
    }
    return -1;
}


int act(Activity *A, int n){
    ordina(A, n);
    int tot[n];
    tot[0] = A[0].t;

    for(int i = 1; i<n; i++){
        int tmp = A[i].t;
        int l = lastActivity(A, i);
        if(l != -1){
            tmp += tot[l];
        }
        tot[i] = max(tmp, tot[i-1]);
    }
    return tot[n-1];
}

int main(){
    ifstream in;
    ofstream out;
    in.open("input.txt");
    out.open("output.txt");

    for(int k = 0; k<100; k++){
        int S, F;
        int n;
        in >> n;
        Activity A[n];
        char x;

        for(int i = 0; i<n; i++){
            in >> x >> S >> F >> x;
            Activity a(S, F);
            A[i] = a;
        }

        out << act(A, n) << endl;
    }

    in.close();
    out.close();
}