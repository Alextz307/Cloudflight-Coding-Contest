#include <bits/stdc++.h>
#define int long long
 
using namespace std;
 
ifstream fin("text.in");
ofstream fout("text.out");
 
struct task {
    int id, power, st, dr;
 
    bool operator < (const task& A) const {
        return this -> power < A.power;
    }
};
 
int32_t main() {
    fin.sync_with_stdio(false);
    fout.sync_with_stdio(false);
    fin.tie(nullptr);
    fout.tie(nullptr);
    int mx_pow, mx_bill;
    fin >> mx_pow >> mx_bill;
    int N;
    fin >> N;
    vector < int > a(N + 1);
    for(int i = 1; i <= N; ++i)
        fin >> a[i];
    int M;
    fin >> M;
    fout << M << '\n';
    vector < task > t(M + 1);
    for(int i = 1; i <= M; ++i)
        fin >> t[i].id >> t[i].power >> t[i].st >> t[i].dr;
    sort(t.begin() + 1, t.end());
    vector < int > sol[M + 1], used(N + 1);
    for(int i = 1; i <= M; ++i) {
        int id = t[i].id, power = t[i].power, st = t[i].st, dr = t[i].dr;
        ++st, ++dr;
        int cat = power / mx_pow;
        int rest = power - cat * mx_pow;
        vector < pair < int , int > > v;
        for(int j = st; j <= dr; ++j)
            v.emplace_back(a[j], j);
        sort(v.begin(), v.end());
        vector < bool > ok(N + 1);
        for(int j = 0; j < (int)v.size() && cat > 0; ++j)
            if(used[v[j].second] == 0) {
                sol[id].emplace_back(v[j].second - 1);
                sol[id].emplace_back(mx_pow);
                used[v[j].second] = mx_pow;
                --cat;
                ok[v[j].second] = true;
            }
        if(rest > 0)
            for(int j = 0; j < (int)v.size(); ++j)
                if(used[v[j].second] + rest <= mx_pow && !ok[v[j].second]) {
                    sol[id].emplace_back(v[j].second - 1);
                    sol[id].emplace_back(rest);
                    used[v[j].second] += rest;
                    break;
                }
    }
    for(int i = 1; i <= M; ++i) {
        fout << i << ' ';
        for(int x : sol[i])
            fout << x << ' ';
        fout << '\n';
    }
}
 
