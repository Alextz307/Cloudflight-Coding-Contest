#include <bits/stdc++.h>
 
using namespace std;
 
ifstream fin("text.in");
ofstream fout("text.out");
 
int main() {
    fin.sync_with_stdio(false);
    fout.sync_with_stdio(false);
    fin.tie(nullptr);
    fout.tie(nullptr);
    int N;
    fin >> N;
    vector < int > a(N);
    int mn = INT_MAX, ans = -1;
    for(int i = 0; i < N; ++i) {
        fin >> a[i];
        if(a[i] < mn) {
            mn = a[i];
            ans = i;
        }
    }
    fout << ans;
}
 
