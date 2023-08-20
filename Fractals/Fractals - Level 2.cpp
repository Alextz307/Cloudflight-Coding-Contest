#include <bits/stdc++.h>
#define int long long
 
using namespace std;
 
int32_t main() {
    int N, itr;
    cin >> N >> itr;
    int ans = 4 * N, nr = 4;
    for(int i = 1; i <= itr; ++i) {
        N /= 3;
        ans += 2 * nr * N;
        nr *= 5;
    }
    cout << ans;
}
 
