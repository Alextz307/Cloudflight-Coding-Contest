#include <bits/stdc++.h>
#define ABS(x) ((x) >= 0 ? (x) : -(x))
 
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
 
int main() {
    fin.sync_with_stdio(false);
    fout.sync_with_stdio(false);
    fin.tie(nullptr);
    fout.tie(nullptr);
    int N, P;
    fin >> N >> P;
    vector < int > freq(P, 1000);
    for(int itr = 0; itr < N; ++itr) {
        int id1, score1, id2, score2;
        fin >> id1 >> score1 >> id2 >> score2;
        long double difA = freq[id2] - freq[id1];
        long double difB = freq[id1] - freq[id2];
        long double EA = (long double)1.0 / ((long double)1.0 + my_pow(10.0, difA / 400.0));
        long double EB = (long double)1.0 / ((long double)1.0 + my_pow(10.0, difB / 400.0));
        long double SA = 1, SB = 0;
        if(score2 > score1)
            swap(SA, SB);
        freq[id1] += (long double)32.0 * (SA - EA);
        freq[id2] += (long double)32.0 * (SB - EB);
    }
    vector < pair < int , int > > sol;
    for(int i = 0; i < P; ++i)
        sol.emplace_back(i, freq[i]);
    sort(sol.begin(), sol.end(), fcmp);
    for(auto x : sol)
        fout << x.first << ' ' << x.second << '\n';
}
 
