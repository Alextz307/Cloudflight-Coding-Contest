#include <bits/stdc++.h>
 
using namespace std;
 
ifstream fin("text.in");
ofstream fout("text.out");
 
bool fcmp(const pair < int , int >& a, const pair < int , int >& b) {
    return a.second > b.second || (a.second == b.second && a.first < b.first);
}
 
int main() {
    fin.sync_with_stdio(false);
    fout.sync_with_stdio(false);
    fin.tie(nullptr);
    fout.tie(nullptr);
    int N, P;
    fin >> N >> P;
    vector < int > freq(P);
    for(int itr = 0; itr < N; ++itr) {
        int id1, score1, id2, score2;
        fin >> id1 >> score1 >> id2 >> score2;
        if(score1 > score2)
            ++freq[id1];
        else
            ++freq[id2];
    }
    vector < pair < int , int > > sol;
    for(int i = 0; i < P; ++i)
        sol.emplace_back(i, freq[i]);
    sort(sol.begin(), sol.end(), fcmp);
    for(auto x : sol)
        fout << x.first << ' ' << x.second << '\n';
}
 
