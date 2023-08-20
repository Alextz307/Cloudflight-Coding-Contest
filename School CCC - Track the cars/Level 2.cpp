#include <bits/stdc++.h>
 
using namespace std;
 
ifstream fin("text.in");
ofstream fout("text.out");
 
struct observator {
    string id, time, latitiude, longitude;
};
 
bool bigger(string s, string t) {
    string S, T;
    int ps = 0, pt = 0;
    while(ps < (int)s.size() && isdigit(s[ps]))
        S.push_back(s[ps++]);
    while(pt < (int)t.size() && isdigit(t[pt]))
        T.push_back(t[pt++]);
    if(S.size() > T.size())
        return true;
    if(S.size() < T.size())
        return false;
    int dim = S.size();
    int p = 0;
    while(p < dim && S[p] == T[p])
        ++p;
    if(p != dim)
        return S[p] > T[p];
    ++ps, ++pt;
    S.clear(), T.clear();
    while(ps < (int)s.size() && isdigit(s[ps]))
        S.push_back(s[ps++]);
    while(pt < (int)t.size() && isdigit(t[pt]))
        T.push_back(t[pt++]);
    dim = min(S.size(), T.size());
    p = 0;
    while(p < dim && S[p] == T[p])
        ++p;
    if(p != dim)
        return S[p] > T[p];
    return S.size() > T.size();
}
 
int main() {
    int N;
    fin >> N;
    vector < observator > a(N);
    string id1, time1, id2, time2, mx1 = "", mx2 = "";
    for(auto& x : a) {
        string s;
        fin >> s;
        int p = 0;
        while(isalnum(s[p]) || s[p] == '-')
            x.id.push_back(s[p++]);
        ++p;
        while(isdigit(s[p]) || s[p] == ':')
            x.time.push_back(s[p++]);
        ++p;
        while(isdigit(s[p]) || s[p] == '.')
            x.latitiude.push_back(s[p++]);
        ++p;
        while(isdigit(s[p]) || s[p] == '.')
            x.longitude.push_back(s[p++]);
        if(bigger(x.latitiude, mx1)) {
            mx1 = x.latitiude;
            id1 = x.id;
            time1 = x.time;
        }
        if(bigger(x.longitude, mx2)) {
            mx2 = x.longitude;
            id2 = x.id;
            time2 = x.time;
        }
    }
    fout << id1 << ',' << time1 << ',' << id2 << ',' << time2;
}
 
