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
#define trieType unordered_map< string, vector<string> >

bool sortP(pair<ll, char> p1, pair<ll, char> p2){
    return p1.first < p2.first;
}

char charBase = '&';
unordered_set<string> rulesNames;
unordered_map< string, ll> rulesN;
unordered_map< string, ll> rulesM;
trieType tries;

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

void dfs(vector<vector<pair<ll,char>>> adj, vector<ll> pos, vector<string> &cad, ll node, ll limit, string perm, string str = ""){
    if(node >= limit){
        string cadena = str;
        for(ll i = 0; i < str.size(); i++)
            cadena[perm[i] - '0'] = str[i];
        cad.push_back(cadena);
        return;
    }
    for(auto v : adj[node]){
        if(v.first >= limit)
            dfs(adj, pos, cad, v.first, limit, perm, str + v.second);
        else
            dfs(adj, pos, cad, v.first, limit, perm + to_string(pos[v.first]), str + v.second);
    }
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
            vector<vector<pair<ll,char>>> adj(edges+1);//Hay edges + 1 nodos

            for(ll i=0; i<edges; i++){
                ll nodeA = getNumber(temporal);
                ll nodeB = getNumber(temporal);
                char caracter = getCar(temporal);
                adj[nodeA].push_back({nodeB, caracter});
            }

            for(auto vect : adj)    sort(begin(vect), end(vect), sortP);

            vector<string> cad;
            dfs(adj, pos, cad, 0, posSize, to_string(pos[0]));
            tries[rule] = cad;
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

int main()
{
    fstream file, trieF;
    //ofstream offile;
    //string trieFile = "triesCompHeu.txt";
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
            //Xaa
            if(consulta.size() != rulesM[rule]){
                cout << "La consulta tiene muchos caracteres\n";
                continue;
            }
            vector<char> res;
            for(ll i = 0; i < rulesN[rule]; i++){
                char resConsulta;
                bool valid = true;
                for(ll j = 0; j < rulesM[rule]; j++){
                    if(consulta[j] == 'X')  resConsulta = tries[rule][i][j];
                    else{
                        if(consulta[j] != tries[rule][i][j]){
                            valid = false;
                            break;
                        }
                    }
                }
                if(valid)   res.push_back(resConsulta);
            }
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
