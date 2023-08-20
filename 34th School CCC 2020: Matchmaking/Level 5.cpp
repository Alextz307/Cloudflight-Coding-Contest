#include <bits/stdc++.h>
#define ABS(x) ((x) >= 0 ? (x) : -(x))
#define int long long
 
using namespace std;
 
ifstream fin("text.in");
ofstream fout("text.out");
 
bool fcmp(const pair < int , int >& a, const pair < int , int >& b) {
    return a.second > b.second || (a.second == b.second && a.first < b.first);
}
 
long double my_pow(long double a, long double b) {
    if(b < 0)
        return 1.0 / pow(a, ABS(b));
    return pow(a, b);
}
 
int32_t main() {
    fin.sync_with_stdio(false);
    fout.sync_with_stdio(false);
    fin.tie(nullptr);
    fout.tie(nullptr);
    int N, P, tp;
    fin >> N >> P >> tp;
    vector < int > freq(P, 1000);
    for(int itr = 0; itr < N; ++itr) {
        vector < pair < int , int > > team[2];
        vector < int > sum(2);
        for(int i = 0; i < 2; ++i)
            for(int j = 0; j < tp; ++j) {
                int id, score;
                fin >> id >> score;
                team[i].emplace_back(id, score);
                sum[i] += score;
            }
        vector < long double > S(2);
        S[0] = 1;
        S[1] = 0;
        if(sum[1] > sum[0])
            swap(S[0], S[1]);
        vector < long double > add(P);
        for(int i = 0; i < 2; ++i)
            for(int j = 0; j < tp; ++j) {
                int ID = team[i][j].first;
                long double dif = 0;
                int inamic = i ^ 1;
                for(auto x : team[inamic])
                    dif += freq[x.first];
                for(auto x : team[i])
                    dif -= freq[x.first];
                long double E = (long double)1.0 / ((long double)1.0 + my_pow(10.0, dif / 400.0));
                add[ID] += (long double)32.0 * (S[i] - E);
            }
        for(int i = 0; i < P; ++i)
            freq[i] += add[i];
    }
    vector < pair < int , int > > sol;
    for(int i = 0; i < P; ++i)
        sol.emplace_back(i, freq[i]);
    sort(sol.begin(), sol.end(), fcmp);
    for(auto x : sol)
        fout << x.first << ' ' << x.second << '\n';
}
 
