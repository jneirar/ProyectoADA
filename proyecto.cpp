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

using namespace std;
#define ll long long

const ll MOD = 1e9+7;

bool sortP(pair<ll, ll> p1, pair<ll, ll> p2){
    if(p1.second == p2.second)  return p1.first < p2.first;
    return p1.second < p2.second;
}

int main(){
    //aaa, baa, bac, cbb
    //0 -> a,b,c    3
    //1 -> a,b      2
    //2 -> a,b,c    3
    //102

    ll n, m; cin >> n >> m;
    
    vector<string> cad(n);
    unordered_set<int> caracters;   //26 caracteres
    vector<unordered_set<int>> carByPosition(m);
    for(ll i = 0; i < n; i++){                                          //O(n*m)
        cin >> cad[i];                                  
        for(ll j = 0; j < m; j++){                                      //O(m)
            caracters.insert(cad[i][j]-'a');                            //O(1)
            carByPosition[j].insert(cad[i][j]-'a');                     //O(1)
        }
    }
    vector<pair<ll, ll>> permutation;   //{position, #car by position
    for(ll i = 0; i < m; i++)                                           //O(m)
        permutation.push_back(make_pair(i, carByPosition[i].size()));   //O(1)
    sort(permutation.begin(), permutation.end(), sortP);                //O(mlgm)

    vector<int> alf;                                                    //O(1), alfabeto = 26 letras
    for(int c : caracters)                                              //O(alfabeto)
        alf.push_back(c);                                               
    sort(alf.begin(), alf.end());                                       //O(alfabeto lg alfabeto)
    
    for(string &s : cad){                                               //O(n*m)
        string news = "";
        for(ll i = 0; i < m; i++)                                       //O(m)
            news += s[permutation[i].first];                            //O(1)
        s = news;                                                       //O(m)
    }
    //aaa, baa, bac, cbb
    //102
    //aaa, aba, abc, bcb
    sort(cad.begin(), cad.end());

    vector<vector<ll>> sptrie(m * n + 1);                           
    for(ll i = 0; i < m * n + 1; i++)                                   //O(m*n)
        sptrie[i].resize(alf.size(), 0);                                //O(alfabeto) = O(1)
        
    // De 0 a m-1
    ll parent = 0, node = 0;
    for(string s : cad){                                                //O(n * m)
        parent = 0; 
        for(char c : s){                                                //O(m)
            if(sptrie[parent][c-'a'] == 0)                              //O(1)
                //No existe, la creamos                                 
                sptrie[parent][c-'a'] = ++node;                         //O(1)
            parent = sptrie[parent][c-'a'];                             //O(1)
        }
    }   
    

    //Print sptrie
    cout << "i -> ";
    for(ll j = 0; j < alf.size(); j++)  cout << "\t" << char(alf[j]+'a');   cout << "\n";
    for(ll i=0; i<node; i++){
        cout << i << " ->";
        for(ll j=0; j<alf.size(); j++)  cout << "\t" << sptrie[i][j];
        cout << "\n";
    }
    //Print edges
    cout << "Aristas = " << node << "\n";
    return 0;
}