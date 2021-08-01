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
#include <array>

using namespace std;
#define ll long long
#define pll pair<ll, ll>

const ll MOD = 1e9+7;
const ll MAX = 1e9+7;

ll n, m;

vector<string> cad;
vector<vector<vector<bool>>> K;
vector<vector<ll>> KSize;
//vector<vector<vector<vector<ll>>>> C1;
//vector<vector<vector<vector<ll>>>> C2;
vector<vector<ll>> dp;
vector<vector<ll>> path;

vector<ll> fillC(ll i, ll j, ll r);
void resiz();

int main(){
    cin >> n >> m;
    //Resize
    resiz();
    for(ll i = 1; i <= n; i++)                                          //O(n*m)
        cin >> cad[i];                                  
    for(ll i = 1; i <= n; i++){                                         //O(n*m)
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
    
    for(ll i = 1; i <= n; i++)  dp[i][i] = 0;       //O(n)
    for(ll l = 2; l <= n; l++){                     //O(n^2*m*(n+m))
        for(ll i = 1; i <= n - l + 1; i++){         //O(n*m*(n+m))
            ll j = i + l - 1;
            ll mn = LLONG_MAX;
            for(ll r = 0; r < m; r++){              //O(m*(n+m))
                if(K[i][j][r])  continue;
                ll loc = 0;
                /*fillC(i, j, r);                     //O(n)
                for(ll k = 0; k < C1[i][j][r].size(); k++)              //O(m)
                    loc += dp[ C1[i][j][r][k] ][ C2[i][j][r][k] ] + KSize[ C1[i][j][r][k] ][ C2[i][j][r][k] ] - KSize[i][j];
                if(loc < mn){
                    mn = loc;
                    path[i][j] = r;
                }*/
                auto C = fillC(i, j, r);                     //O(n)
                for(ll k = 0; k < C.size(); k+=2)
                    loc += dp[ C[k] ][ C[k+1] ] + KSize[ C[k] ][ C[k+1] ] - KSize[i][j];
                if(loc < mn){
                    mn = loc;
                    path[i][j] = r;
                }
            }
            dp[i][j] = mn;
        }
    }
    ll edges = dp[1][n] + KSize[1][n];
    

/*    for(ll i = 1; i <= n; i++){
        for(ll j = i; j <= n; j++){
            cout << i << "-" << j << " : " << path[i][j] << endl;
        }
    }*/

    set<char> alf;
    for(ll i=1; i<=n; i++){
        for(ll j=0; j<m; j++){
            alf.insert(cad[i][j]);
        }
    }
    map<char, ll> posAlf;
    map<ll, char> alfPos;
    ll posAlfab = 0;
    for(char c : alf){
        posAlf[c] = posAlfab;
        alfPos[posAlfab++] = c;
    }
    
    vector<vector<bool>> posUsed(n+1);
    for(ll i=1; i<=n; i++)  posUsed[i].resize(m, 0);
    
    vector<ll> pos; //pos[nodo] = alguna posición de 0 a m-1
    vector<vector<ll>> sptrie(m*n+1);   //
    for(ll i=0; i<m*n+1; i++)   sptrie[i].resize(alf.size());

    queue<array<ll, 3>> q;  //nodo, pinicial, pfinal
    
    ll nodo = 0;
    q.push({nodo++, 1, n});

    while(!q.empty()){
        auto cur = q.front();
        q.pop();
        ll partition = path[ cur[1] ][ cur[2] ];
        ll nodePar = cur[0];

        bool continua = false;
        //Asegurar que tenga K's pendientes
        for(ll p=0; p<m; p++){
            //Si los caracteres no están marcados, y pertenece a K[][] entonces entra primero
            if(!posUsed[ cur[1] ][p] && K[cur[1]][cur[2]][p]){
                //Agrego al sptrie
                pos.push_back( p );

                for(ll k=cur[1]; k<=cur[2]; k++)
                    posUsed[k][p] = 1;

                sptrie[nodePar][ posAlf[cad[cur[1]][p]] ] = nodo;
                q.push({nodo++, cur[1], cur[2]});
                continua = true;
                break;
            }
        }
        if(continua) continue;
        if(partition == -1){
            bool faltan = false;
            for(ll i=cur[1]; i <= cur[2]; i++){
                for(ll p=0; p<m; p++){
                    if(!posUsed[i][p]){
                        pos.push_back( p );
                        for(ll k=cur[1]; k<=cur[2]; k++)
                            posUsed[k][p] = 1;

                        sptrie[nodePar][ posAlf[cad[i][p]] ] = nodo;
                        q.push({nodo++, cur[1], cur[2]});
                        faltan = true;
                        break;
                    }
                }
                if(faltan)  break;
            }
        }else{
            for(ll i=cur[1]; i<=cur[2]; i++)  posUsed[i][ partition ] = 1;
            pos.push_back( partition );
            
            vector<ll> C = fillC(cur[1], cur[2], partition);//1,3 4,4 5,6
            for(ll p = 0; p < C.size(); p += 2){
                sptrie[ nodePar ][ posAlf[   cad[ C[p] ][ partition ]   ] ] = nodo;
                q.push({nodo++, C[p], C[p+1]} );
            }
        }
    }
    nodo = pos.size()-1;

    cout << "\nSPTRIE: " << endl;
    cout << "\t";
    for(auto c : alf){cout << c << "\t";
    }cout << endl;
    for(ll i=0; i<=nodo; i++){
        cout << i << "\t";
        for(auto c : alf){
            cout << sptrie[i][posAlf[c]] << "\t";
        }
        cout << endl;
    }cout << "\n";
    
    cout << "node -> pos" << endl;
    for(ll i=0; i<pos.size(); i++){
        cout << i << " -> " << pos[i] << "\n";
    }
    
    cout << "Edges: " << edges << endl;
    return 0;
}

vector<ll> fillC(ll i, ll j, ll r){               //O(n)
    //if(C1[i][j][r].size() > 0)  return;
    /*ll idx = i;
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
    C2[i][j][r].push_back(j);*/
    vector<ll> ans;
    ll idx = i;
    char c = cad[i][r];
    for(ll it = i+1; it <= j; it++){
        if(c != cad[it][r]){
            ans.push_back(idx);
            ans.push_back(it-1);
            idx = it;
            c = cad[it][r];
        }
    }
    ans.push_back(idx);
    ans.push_back(j);
    return ans;
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
    for(ll i = 0; i <= n; i++){             //O(n^2*m)
        K[i].resize(n+1);
        KSize[i].resize(n+1);
        //R[i].resize(n+1);
        for(ll j=0; j<=n; j++){
            K[i][j].resize(m,0);
            KSize[i][j] = 0;
        }
    }
    /*C1.resize(n+1);
    C2.resize(n+1);
    for(ll i = 1; i <= n; i++){             //O(n^2*m)
        C1[i].resize(n+1);
        C2[i].resize(n+1);
        for(ll j = 1; j <= n; j++){
            C1[i][j].resize(m);
            C2[i][j].resize(m);
        }
    }*/
}