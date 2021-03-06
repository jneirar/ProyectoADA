#ifndef PROYECTOADA_trie_H
#define PROYECTOADA_trie_H
  
#include <iostream>
#include <fstream>
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

bool sortP(pair<ll, ll> p1, pair<ll, ll> p2){
    if(p1.second == p2.second)  return p1.first < p2.first;
    return p1.second < p2.second;
}

class trie{
    string name;
    vector<string> cad;
    vector<unordered_set<int>> charByPosition;
    vector<pair<ll, ll>> permutation;   //{position, #car by position
    unordered_set<int> characters;   //26 caracteres
    vector<int> alf;                                                    //O(1), alfabeto = 26 letras
    vector<vector<ll>> sptrie;   
    unordered_map<char, ll> position;
    queue<array<ll, 4>> q;
    vector<ll> pos;
    ll node, edges, n, m; 

    public:
    trie(string nombre, ll n, ll m, vector<string> cadenas){
        name = nombre;
        this->n = n;
        this->m = m;
        cad = cadenas;    
        charByPosition.resize(m);    
        sptrie.resize(m * n + 1);
        for(ll i = 0; i < n; i++)                          
            for(ll j = 0; j < m; j++)                                       //O(m)
                charByPosition[j].insert(cad[i][j]-'a');                    //O(1)
        

        for(ll i = 0; i < m; i++)                                           //O(m)
            permutation.push_back(make_pair(i, charByPosition[i].size()));   //O(1)
        sort(permutation.begin(), permutation.end(), sortP);                //O(mlgm)


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
        
                            
        for(ll i = 0; i < m * n + 1; i++)                                   //O(m*n)
            sptrie[i].resize(alf.size(), 0);                                //O(alfabeto) = O(1)

        
        for(ll i = 0; i < alf.size(); i++)  position[char(alf[i] + 'a')] = i;   //O(alfabeto)
        node = 0;

        q.push({node++, 1, n, 0});

        while(!q.empty()){
            auto cur = q.front();
            q.pop();
            if(cur[3] >= m) continue;
            pos.push_back(permutation[cur[3]].first);
            ll k = cur[1];
            char ck = cad[cur[1]-1][cur[3]];
            for(ll i=cur[1]+1; i<=cur[2]; i++){
                if(cad[i-1][cur[3]] != ck){
                    sptrie[cur[0]][position[ck]] = node;
                    q.push({node++, k, i-1, cur[3]+1});
                    k = i;
                    ck = cad[i-1][cur[3]];
                }
            }
            sptrie[cur[0]][position[ck]] = node;
            q.push({node++, k, cur[2], cur[3]+1});
        }
        
        edges = node - 1;
        node = pos.size();
    }

    void print(){
        for(ll i=0; i<node; i++){
            for(ll j=0; j<alf.size(); j++)  
                if(sptrie[i][j] != 0)
                    cout << i  << " " << sptrie[i][j] << " " << char(alf[j]+'a') << '\n';
        }
        cout << "\nPermutation: ";
        for(ll i = 0; i < m; i++)                                       //O(m)
            cout << permutation[i].first << " ";
        cout << "\n";
        cout << "node -> perm\n";
        for(int i=0; i<pos.size(); i++){
            cout << i << " -> " << pos[i] << endl;
        }

        //Print edges
        cout << "Aristas = " << edges << "\n";
    }

    template< typename F, typename S >
    struct PairComparator {
    bool operator()( const pair<F, S>& p1, const pair<F, S>& p2 ) const {  
            return p1.first > p2.first;
        }
    };
    
    void write(ofstream &file, string &outputName){
        char charBase = '&';
        file << name << charBase << n << charBase << m << charBase << pos.size() << charBase;
        for(ll i=0; i<pos.size(); i++){
            file << pos[i];
            if(i != pos.size()-1)   file << charBase;
            else file << charBase;
        }
        file << edges << charBase;
        for(ll i=0; i<node; i++){
            //Ordenar de acuerdo al n??mero
            priority_queue< pair<ll, char> , vector< pair<ll, char> >, PairComparator<ll, char> > pq;

            for(ll j=0; j<alf.size(); j++)
                if(sptrie[i][j] != 0)
                    pq.push(make_pair(sptrie[i][j], char(alf[j]+'a')));

            while(!pq.empty()){
                file << i << charBase << pq.top().first << charBase << pq.top().second << charBase;
                pq.pop();
            }
        }
        file << "\n";
    }
};

#endif