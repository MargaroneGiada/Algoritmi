#include<iostream>
#include<fstream>

using namespace std;

class Terna{
    public:
        double a, b, c;

        Terna(){}

        Terna(double a, double b, double c){
            this->a = a;
            this->b = b;
            this->c = c;
        }
};

bool operator<(Terna t1, Terna t2){
    if(t1.a > t2.a){return true;}
    return true;
}

ofstream& operator<<(ofstream &out, Terna t){
    out << "(" << t.a << " " << t.b << " " << t.c << ")";
    return out;
}

ostream& operator<<(ostream &out, Terna t){
    out << "(" << t.a << " " << t.b << " " << t.c << ")";
    return out;
}

void CountingSort(Terna* A, int size, ofstream &out){
    //passiamo ad intero
    for(int i = 0; i < size; i++){
        A[i].a *= 10;
    }

    //find min and max;
    double max = A[0].a;
    double min = A[0].a;
    for(int i = 1; i < size; i++){
        if(A[i].a > max){
            max = A[i].a;
        }else if(A[i].a < min){
            min = A[i].a;
        }
    }
    cout << "found max and min " << max << " " << min << endl;

    int gap = max - min + 1;

    int C[gap];
    for(int i = 0; i < gap; i++){
        C[i] = 0;
    }
    for(int i = 0; i < size; i++){
        C[(int)(A[i].a - min)]++;
    }
    for(int i = 1; i < gap; i++){
        C[i] = C[i] + C[i-1];
    }

    cout << "C initialized " << endl;

    Terna B[size];
    for(int i = size - 1; i >= 0; i--){
        B[C[(int)(A[i].a - min)] - 1] = A[i];
        C[(int)(A[i].a - min)]--;
    }

    cout << "fatto" << endl;
    for(int i = 0; i < size; i++){
        B[i].a /= 10;
    }   

    for(int i = 0; i < gap; i++){
        out << C[i] << " ";
    } 
    for(int i = 0; i < size; i++){
        out << B[i] << " ";
    }  
    out << endl;
}


int main()
{
    ifstream in;
    in.open("input.txt");
    ofstream o;
    o.open("output.txt");
    int size;
    char x;
    double a, b, c;
    while (!in.eof())
    {
        in >> size;
        cout << size ;
        Terna A[size];
        for(int i = 0; i < size; i++){
            in >> x >> a >> b >> c >> x;
            A[i].a = a;
            A[i].b = b;
            A[i].c = c;
            cout << A[i] << endl;;
        }
        cout << "ok" << endl;
        CountingSort(A, size, o);
    }
}