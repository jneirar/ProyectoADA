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
vector<vector<unordered_set<ll>>> K;
vector<vector<unordered_set<ll>>> R;
vector<vector<vector<set<pll>>>> C;
ll opt(ll i, ll j){
    if(i == j)  return 0;
    ll mn = LLONG_MAX;
    for(auto r : R[i][j]){
        ll loc = 0;
        for(auto p : C[i][j][r])
            loc += opt(p.first, p.second) + K[p.first][p.second].size() - K[i][j].size();
        mn = min(mn, loc);
    }
    return mn;
}

int main(){
    //freopen("inBig1.txt", "r", stdin);
    //aaa, baa, bac, cbb
    //0 -> a,b,c    3
    //1 -> a,b      2
    //2 -> a,b,c    3
    //102
    ll n, m; cin >> n >> m;
    
    vector<string> cad(n+1);//1 a n
    for(ll i = 1; i <= n; i++){                                          //O(n*m)
        cin >> cad[i];                                  
    }

    K.resize(n+1);
    R.resize(n+1);
    for(ll i = 1; i <= n; i++){
        K[i].resize(n+1);
        R[i].resize(n+1);
        for(ll p = 0; p < m; p++){
            K[i][i].insert(p);    
        }
    }
    for(ll i = 1; i < n; i++){
        //i a i+1
        for(ll p = 0; p < m; p++){
            if(cad[i][p] == cad[i+1][p])
                K[i][i+1].insert(p);
            else
                R[i][i+1].insert(p);
        }
    }
    //(1,3) = (1,2) y (2,3)
    //(2,5) = (2,3) y (3,5)
    for(ll l = 2; l <= n-1; l++){
        for(ll i = 1; i <= n - l; i++){
            ll j = i + l;
            //i, i+1 y i+1, j
            for(ll p = 0; p < m; p++){
                if(K[i][i+1].count(p) && K[i+1][j].count(p))
                    K[i][j].insert(p);
                else
                    R[i][j].insert(p);
            }
        }
    }
    /*for(ll i = 1; i <= n; i++){
        for(ll j = i; j <= n; j++){
            cout << i << "-" << j << "\n\t";
            for(auto p : K[i][j])   cout << p << ",";   cout << "\n\t";
            for(auto p : R[i][j])   cout << p << ",";   cout << endl;
        }
    }*/
    C.resize(n+1);
    for(ll i = 1; i <= n; i++){
        C[i].resize(n+1);
        for(ll j = 1; j <= n; j++){
            C[i][j].resize(m);
        }
    }
    for(ll i = 1; i <= n; i++){
        for(ll j = i+1; j <= n; j++){
            for(auto p : R[i][j]){
                ll idx = i;
                char c = cad[i][p];
                for(ll ij = i+1; ij <= j; ij++){
                    if(c != cad[ij][p]){
                        C[i][j][p].insert({idx, ij-1});
                        idx = ij;
                        c = cad[ij][p];
                    }
                }
                C[i][j][p].insert({idx, j});
            }
        }
    }
    /*while(1){
        cout << "\nIngresa i j p: ";
        ll i, j, p;
        cin >> i >> j >> p;
        for(auto p : C[i][j][p]){
            cout << p.first << ", " << p.second << endl;
        }
    }*/

    ll edges = opt(1, n) + K[1][n].size();
    cout << edges << endl;
    return 0;
}