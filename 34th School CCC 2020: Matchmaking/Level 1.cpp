#include <bits/stdc++.h>
 
using namespace std;
 
ifstream fin("text.in");
ofstream fout("text.out");
 
int main() {
    fin.sync_with_stdio(false);
    fout.sync_with_stdio(false);
    fin.tie(nullptr);
    fout.tie(nullptr);
    int N, P;
    fin >> N >> P;
    int mx = INT_MIN, ID = INT_MAX;
    for(int itr = 0; itr < N; ++itr) {
        int id1, score1, id2, score2;
        fin >> id1 >> score1 >> id2 >> score2;
        if(score1 > mx) {
            mx = score1;
            ID = id1;
        }
        else
            if(score1 == mx && ID > id1)
                ID = id1;
        if(score2 > mx) {
            mx = score2;
            ID = id2;
        }
        else
            if(score2 == mx && ID > id2)
                ID = id2;
    }
    fout << ID << ' ' << mx;
}
 
