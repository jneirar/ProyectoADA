#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;
#define ll long long
#define pll pair<ll, ll>

const ll MOD = 1e9+7;
const ll MAX = 1e9+7;

ll n, m;
vector<string> cad;
vector<vector<vector<bool>>> K;
vector<vector<ll>> KSize;
vector<vector<vector<vector<ll>>>> C1;
vector<vector<vector<vector<ll>>>> C2;
vector<vector<ll>> dp;
vector<vector<ll>> path;

void fillC(ll i, ll j, ll r);
void resiz();

ll opt(ll i, ll j){
    if(i == j)  return 0;
    if(dp[i][j] != -1)  return dp[i][j];
    ll mn = LLONG_MAX;
    for(ll r = 0; r < m; r++){   
        if(K[i][j][r])  continue;
        ll loc = 0;
        fillC(i, j, r);
        for(ll k = 0; k < C1[i][j][r].size(); k++)              //O(m)
            loc += opt(C1[i][j][r][k], C2[i][j][r][k]) + KSize[ C1[i][j][r][k] ][ C2[i][j][r][k] ] - KSize[i][j];
        mn = min(mn, loc);
    }
    dp[i][j] = mn;
    return dp[i][j];
}

int main(){
    cin >> n >> m;
    //Resize
    resiz();
    for(ll i = 1; i <= n; i++)                                          //O(n*m)
        cin >> cad[i];                                  
    
    for(ll i = 1; i <= n; i++){             //O(n*m)
        KSize[i][i] = m;
        for(ll p = 0; p < m; p++)
            K[i][i][p] = 1;    
    }
    for(ll i = 1; i < n; i++){                  //O(n*m)
        for(ll p = 0; p < m; p++){              //O(m)
            if(cad[i][p] == cad[i+1][p]){
                if(!K[i][i+1][p]) KSize[i][i+1]++;
                K[i][i+1][p] = 1;
            }
        }
    }
    for(ll l = 2; l <= n-1; l++){               //O(n^2*m)
        for(ll i = 1; i <= n - l; i++){
            ll j = i + l;
            for(ll p = 0; p < m; p++){
                if(K[i][i+1][p] && K[i+1][j][p]){
                    if(!K[i][j][p]) KSize[i][j]++;
                    K[i][j][p] = 1;
                }
            }
        }
    }
    ll edges = opt(1, n) + KSize[1][n];
    cout << edges << endl;
    return 0;
}


void fillC(ll i, ll j, ll r){
    if(C1[i][j][r].size() > 0)  return;
    ll idx = i;
    char c = cad[i][r];
    for(ll it = i+1; it <= j; it++){
        if(c != cad[it][r]){
            C1[i][j][r].push_back(idx);
            C2[i][j][r].push_back(it-1);
            idx = it;
            c = cad[it][r];
        }
    }
    C1[i][j][r].push_back(idx);
    C2[i][j][r].push_back(j);
}

void resiz(){
    cad.resize(n+1);
    dp.resize(n+1);
    path.resize(n+1);
    for(ll i = 1; i <= n; i++){
        dp[i].resize(n+1);
        path[i].resize(n+1);
        for(ll j = 1; j <= n; j++){
            dp[i][j] = -1;
            path[i][j] = -1;
        }
    }
    K.resize(n+1);
    KSize.resize(n+1);
    //R.resize(n+1);
    for(ll i = 0; i <= n; i++){             //O(n^2*m)
        K[i].resize(n+1);
        KSize[i].resize(n+1);
        //R[i].resize(n+1);
        for(ll j=0; j<=n; j++){
            K[i][j].resize(m,0);
            KSize[i][j] = 0;
        }
    }
    C1.resize(n+1);
    C2.resize(n+1);
    for(ll i = 1; i <= n; i++){             //O(n^2*m)
        C1[i].resize(n+1);
        C2[i].resize(n+1);
        for(ll j = 1; j <= n; j++){
            C1[i][j].resize(m);
            C2[i][j].resize(m);
        }
    }
}