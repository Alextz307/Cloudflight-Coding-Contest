#include <bits/stdc++.h>
#define int long long
 
using namespace std;
 
ifstream fin("text.in");
ofstream fout("text.out");
 
int32_t main() {
    fin.sync_with_stdio(false);
    fout.sync_with_stdio(false);
    fin.tie(nullptr);
    fout.tie(nullptr);
    int N;
    fin >> N;
    vector < int > a(N + 1);
    for(int i = 1; i <= N; ++i)
        fin >> a[i];
    int M;
    fin >> M;
    fout << M << '\n';
    while(M--) {
        int id, power, st, dr;
        fin >> id >> power >> st >> dr;
        int mn = INT_MAX, ans = -1;
        for(int i = st + 1; i <= dr + 1; ++i)
            if(a[i] < mn) {
                mn = a[i];
                ans = i;
            }
        fout << id << ' ' << ans - 1 << ' ' << power << '\n';
    }
}
 
