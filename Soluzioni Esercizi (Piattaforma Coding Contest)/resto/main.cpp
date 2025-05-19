#include<iostream>
#include<fstream>
#include<math.h>

using namespace std;

#define INF 200000;

int findMin(int a, int b)
{
    if (a <= b)
        return a;
    else
        return b;
}

int findMinCoins(int coins[], int sum, int size)
{
    int **arr = new int *[size + 1];
    for (int i = 0; i < size + 1; i++)
        arr[i] = new int[sum + 1];

    for (int i = 0; i < size + 1; i++)
        arr[i][0] = 0;

    for (int j = 1; j < sum + 1; j++)
        arr[0][j] = INF;

/*
Dynamic Programming Filling:
The nested loops iterate over each cell of the 2D array, filling it based on the dynamic programming recurrence relation.
if (coins[i - 1] > j) arr[i][j] = arr[i - 1][j];: If the current coin is greater than the current sum, then we can't use 
it, so the value is the same as the value without using the coin.
else arr[i][j] = findMin(1 + arr[i][j - coins[i - 1]], arr[i - 1][j]);: Otherwise, we consider either using the current 
coin (1 + arr[i][j - coins[i - 1]]) or not using it (arr[i - 1][j]), and we choose the minimum of the two.
*/
    for (int i = 1; i < size + 1; i++)
    {
        for (int j = 1; j < sum + 1; j++)
        {
            if (coins[i - 1] > j)
                arr[i][j] = arr[i - 1][j];
            else
                arr[i][j] = findMin(1 + arr[i][j - coins[i - 1]], arr[i - 1][j]);
        }
    }

    int answer = arr[size][sum];

    for (int i = 0; i < size + 1; i++)
        delete[] arr[i];
    delete[] arr;

    return answer;
}




int main(){
    fstream in; in.open("input.txt", fstream::in);
    fstream out; out.open("output.txt", fstream::out);

    int res, n;
    while(!in.eof()){
        in >> res >> n;
        int tagli[n];
        for(int i = 0; i < n; i++){
            in >> tagli[i];
        }
        out << findMinCoins(tagli, res, n) << endl;
    }
}