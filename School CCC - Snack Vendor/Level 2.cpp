#include <bits/stdc++.h>
 
using namespace std;
 
ifstream fin("text.in");
ofstream fout("text.out");
 
int main() {
    int price, N;
    fin >> price >> N;
    vector < int > a(N);
    int sum = 0;
    for(int& x : a) {
        fin >> x;
        sum += x;
    }
    if(price > sum)
        fout << "MISSING " << price - sum;
    else {
        int ans = sum - price;
        fout << "CHANGE ";
        vector < int > sol(8), coins{1, 2, 5, 10, 20, 50, 100, 200};
        for(int i = 7; i >= 0; --i) {
            int cnt = ans / coins[i];
            ans -= cnt * coins[i];
            sol[i] = cnt;
        }
        for(int x : sol)
            fout << x << ' ';
    }
}
 
