#include<iostream>
#include<fstream>

using namespace std;

class Activity{
    public:
        int s, f, t;

        Activity(){}

        Activity(int s, int f){
            this->s = s;
            this->f = f;
            t = f - s;
        }
};

void ordina(Activity* A, int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n-1; j++){
            if(A[j].f > A[j+1].f){
                Activity tmp = A[j];
                A[j] = A[j+1];
                A[j+1] = tmp;
            }
        }
    }
}

int last(Activity *A, int index){
    int k = index;
    for(int i = index-1; i>=0; i--){
        if(A[i].f <= A[k].s){
            return i;
        }
    }
    return -1;
}

int act(Activity* A, int n){
    ordina(A, n);
    int tot[n];
    tot[0] = A[0].t;

    for(int i = 1; i < n; i++){
        int tmp = A[i].t;
        int l = last(A, i);
        if(l!=-1){
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

    int S, F;
    int n;
    char x;
    for(int k = 0; k<100; k++){
        in >> n;
        Activity A[n];
        
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