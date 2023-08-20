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
    for(int i = 1; i <= N; ++i) {
        fin >> a[i];
        a[i] += a[i - 1];
    }
    int M;
    fin >> M;
    fout << M << '\n';
    while(M--) {
        int id, lg;
        fin >> id >> lg;
        fout << id << ' ';
        int mn = INT_MAX, ans = 1;
        for(int i = 1; i <= N; ++i) {
            int j = i + lg - 1;
            if(j > N)
                break;
            int sum = a[j] - a[i - 1];
            if(sum < mn) {
                ans = i;
                mn = sum;
            }
        }
        fout << ans - 1 << '\n';
    }
}
 
