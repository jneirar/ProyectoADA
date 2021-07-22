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
    //freopen("inBig1.txt", "r", stdin);
    //aaa, baa, bac, cbb
    //0 -> a,b,c    3
    //1 -> a,b      2
    //2 -> a,b,c    3
    //102
    ll n, m; cin >> n >> m;
    
    vector<string> cad(n);
    vector<unordered_set<int>> charByPosition(m);
    for(ll i = 0; i < n; i++){                                          //O(n*m)
        cin >> cad[i];                                  
        for(ll j = 0; j < m; j++)                                       //O(m)
            charByPosition[j].insert(cad[i][j]-'a');                    //O(1)
    }

    vector<pair<ll, ll>> permutation;   //{position, #car by position
    for(ll i = 0; i < m; i++)                                           //O(m)
        permutation.push_back(make_pair(i, charByPosition[i].size()));   //O(1)
    sort(permutation.begin(), permutation.end(), sortP);                //O(mlgm)

    unordered_set<int> characters;   //26 caracteres
    vector<int> alf;                                                    //O(1), alfabeto = 26 letras

    for(string &s : cad){                                               //O(n*m)
        string news = "";
        for(ll i = 0; i < m; i++){                                      //O(m)
            news += s[permutation[i].first];                            //O(1)
            if(!characters.count(s[permutation[i].first] - 'a')){       //O(1)
                characters.insert(s[permutation[i].first] - 'a');       //O(1)
                alf.push_back(s[permutation[i].first] - 'a');           //O(1)
            }
        }
        s = news;                                                       //O(m)
    }
    //aaa, baa, bac, cbb
    //102
    //aaa, aba, abc, bcb
    
    vector<vector<ll>> sptrie(m * n + 1);                           
    for(ll i = 0; i < m * n + 1; i++)                                   //O(m*n)
        sptrie[i].resize(alf.size(), 0);                                //O(alfabeto) = O(1)

    unordered_map<char, ll> position;
    for(ll i = 0; i < alf.size(); i++)  position[char(alf[i] + 'a')] = i;   //O(alfabeto)

    // De 0 a m-1
    ll parent = 0, node = 0;
    for(string s : cad){                                                //O(n * m)
        parent = 0; 
        for(char c : s){                                                //O(m)
            if(sptrie[parent][position[c]] == 0)                              //O(1)
                //No existe, la creamos                                 
                sptrie[parent][position[c]] = ++node;                         //O(1)
            parent = sptrie[parent][position[c]];                             //O(1)
        }
    } 

    //Print sptrie
    /*cout << "i -> ";
    for(ll j = 0; j < alf.size(); j++)  cout << "\t" << char(alf[j]+'a');   cout << "\n";
    for(ll i=0; i<node; i++){
        cout << i << " ->";
        for(ll j=0; j<alf.size(); j++)  cout << "\t" << sptrie[i][j];
        cout << "\n";
    }*/
    cout << "\nPermutation: ";
    for(ll i = 0; i < m; i++)                                       //O(m)
        cout << permutation[i].first << " ";
    cout << "\n";
    //Print edges
    cout << "Aristas = " << node << "\n";
    return 0;
}