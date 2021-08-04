#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>
#include <utility>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>

using namespace std;
#define ll long long
#define pll pair<ll, ll>
#define plc pair<ll, char>
#define vll vector<ll>
#define vplc vector<plc>
#define vvplc vector<vplc>
#define trieType unordered_map< string, vvplc >
#define triePosType unordered_map< string, vll >

char charBase = '&';
unordered_set<string> rulesNames;
unordered_map< string, ll> rulesN;
unordered_map< string, ll> rulesM;
trieType tries;
triePosType triesPos;

char getCar(string &rule){
    char temp = rule[0];
    rule = rule.substr(2, rule.size() - 2);
    return temp;
}

ll getNumber(string &rule){
    string temp = "";
    for(auto& c: rule){
        if(c == charBase)
            break;
        temp += c;
    }
    rule = rule.substr(temp.size()+1, rule.size() - temp.size() - 1);
    return stoll(temp);
}

string getRuleName(string &rule){
    string temp = "";
    for(auto& c: rule){
        if(c == charBase)
            break;
        temp += c;
    }
    rule = rule.substr(temp.size()+1, rule.size() - temp.size() - 1);
    return temp;
}

void readTrie(fstream &file){ 
    if(file.is_open()){
        string temporal;
        
        while(getline(file, temporal)){
            //Primera regla
            string rule = getRuleName(temporal);
            if(rulesNames.count(rule)){
                cout << "\nRegla repetida\n";
                continue;
            }
            rulesNames.insert(rule);
            rulesN[rule] = getNumber(temporal);
            rulesM[rule] = getNumber(temporal);
            ll posSize = getNumber(temporal);
            vector<ll> pos;
            for(ll i=0; i<posSize; i++){
                pos.push_back(getNumber(temporal));
            }
            ll edges = getNumber(temporal);
            vvplc adj(edges+1);//Hay edges + 1 nodos
            for(ll i=0; i<edges; i++){
                ll nodeA = getNumber(temporal);
                ll nodeB = getNumber(temporal);
                char caracter = getCar(temporal);
                adj[nodeA].push_back({nodeB, caracter});
            }
            tries[rule] = adj;
            triesPos[rule] = pos;
        }
    }
}

string getRuleConsulta(string &rule){
    string temp = "";
    string temp2 = "";
    for(auto& c: rule){
        if(c == '(')
            break;
        temp += c;
    }
    return temp;
}

string getCharsByRuleConsulta(string &rule){
    string caracteres = "";
    auto x = rule.find('(');
    for(unsigned int i = x + 1; i < rule.size() - 1; ++i){
        if(rule[i] != ',' && rule[i] != ' '){
            caracteres += rule[i];
        }
    }
    return caracteres;
}

void dfs(vector<vector<pair<ll,char>>> &adj, vector<ll> &pos, vector<char> &res, ll node, ll limit, string consulta, char possible = ' '){
    if(node >= limit){
        if(possible != ' ')
            res.push_back(possible);
        return;
    }
    for(auto v : adj[node]){
        if(possible != ' '){
            //Ya encontré X, debo verificar si llego hasta el final
            if(consulta[pos[node]] == v.second){
                dfs(adj, pos, res, v.first, limit, consulta, possible);
            }
        }else{
            if(consulta[pos[node]] == 'X'){
                dfs(adj, pos, res, v.first, limit, consulta, v.second);
            }else{
                if(consulta[pos[node]] == v.second){
                    dfs(adj, pos, res, v.first, limit, consulta, possible);
                }
            }
        }
    }
}

int main()
{
    fstream file, trieF;
    string trieFile = "triesCompOpt.txt";
    string inputFile = "input.txt";
    trieF.open(trieFile, ios::in);
    readTrie(trieF);
    
    file.open(inputFile, ios::in);
    if(file.is_open()){
        string temporal;
        while(getline(file, temporal)){
            string rule = getRuleConsulta(temporal);
            if(rulesNames.count(rule) == 0){
                cout << "No existe regla " << rule << " para la consulta: " << temporal << "\n";
                continue;
            }
            string consulta = getCharsByRuleConsulta(temporal);
            if(consulta.size() != rulesM[rule]){
                cout << "La consulta tiene muchos caracteres\n";
                continue;
            }
            vector<char> res;
            //SPTrie: tries[rule] = vector<vector<pair<ll, char>>>;
            dfs(tries[rule], triesPos[rule], res, 0, triesPos[rule].size(), consulta);

            cout << temporal << "\n\t";
            if(res.size() == 0) cout << "Consulta no encontrada\n";
            
            for(ll i = 0; i < res.size(); i++){
                cout << "X = " << res[i];
                if(i != res.size() - 1)
                    cout << ", ";
                else
                    cout << ".\n";
            }
        }
    }
    cout << "\nConsultas finalizadas\n";
    file.close();
    trieF.close();
    return 0;
}
