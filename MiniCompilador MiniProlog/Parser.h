#ifndef PARSER_H
#define PARSER_H

#include "lib.h"

class Parser{
    char charBase = '&';
    unordered_set<string> rulesNames;
    unordered_map< string, ll> rulesN;
    unordered_map< string, ll> rulesM;
    unordered_map< string, ll> rulesEdges;
    trieType tries;
    triePosType triesPos;
public:
    Parser(){
        cout << "\nParser creado\n";
    }

    void parse(bool opt){
        fstream trieF;
        string trieFile;
        if(opt)
            trieFile = "opt.trie";
        else
            trieFile = "heu.trie";
        
        trieF.open(trieFile, ios::in);
        readTrie(trieF);
        trieF.close();
        cout << "\nParser terminado\n";
    }

    void queryExecuter(string inputFile){
        fstream file;
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
                    cout << "La consulta tiene una cantidad de caracteres distinta a la regla\n";
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
        }else{
            cout << "\nParser. Archivo de consultas, no se abrió\n";
        }
        file.close();
        cout << "\nConsultas finalizadas\n";
    }

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
            cout << "\nInicia parseo\n";

            string temporal;
            unordered_set<string> ruleNew;
            while(getline(file, temporal)){
                //Primera regla
                string rule = getRuleName(temporal);
                if(rulesNames.count(rule) == 1){
                    rulesNames.erase(rule);
                    rulesN.erase(rule);
                    rulesM.erase(rule);
                    tries.erase(rule);
                    triesPos.erase(rule);
                }
                if(ruleNew.count(rule)){
                    cout << "\nRegla repetida\n";
                    continue;
                }
                ruleNew.insert(rule);
                rulesNames.insert(rule);
                rulesN[rule] = getNumber(temporal);
                rulesM[rule] = getNumber(temporal);
                ll posSize = getNumber(temporal);
                vector<ll> pos;
                for(ll i=0; i<posSize; i++){
                    pos.push_back(getNumber(temporal));
                }
                ll edges = getNumber(temporal);
                if(edges <= 0){
                    cout << "\nAristas negativas\n";
                    continue;
                }
                rulesEdges[rule] = edges;
                vvplc adj(edges+1);//Hay edges + 1 nodos
                for(ll i=0; i<edges; i++){
                    if(temporal.size()==0){
                        cout << "Faltan aristas debido a mala entrada\n";
                        break;
                    } 
                    ll nodeA = getNumber(temporal);
                    ll nodeB = getNumber(temporal);
                    char caracter = getCar(temporal);
                    adj[nodeA].push_back({nodeB, caracter});
                }
                tries[rule] = adj;
                triesPos[rule] = pos;
            }
        }else{
            cout << "\nParser. Archivo no leído\n";
        }
    }

    string getRuleConsulta(string &rule){
        auto x = rule.find(' ');
        return rule.substr(0, x);
    }

    string getCharsByRuleConsulta(string &rule){
        auto x = rule.find(' ');
        return rule.substr(x+1, rule.size());
    }

    void dfs(vector<vector<pair<ll,char>>> &adj, vector<ll> &pos, vector<char> &res, ll node, ll limit, string consulta, char possible = ' '){
        if(node >= limit){
            if(possible != ' ')
                res.push_back(possible);
            return;
        }
        for(auto v : adj[node]){
            if(possible != ' '){
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
    void showRules(){
        cout << "Reglas en memoria:\n";
        for(string s : rulesNames)
            cout << "\t" << s << " tiene " << rulesEdges[s] << " aristas\n";
        cout << "\n";
    }
    void eraseRule(string rule){
        if(rulesNames.count(rule) > 0){
            rulesNames.erase(rule);
            rulesN.erase(rule);
            rulesM.erase(rule);
            tries.erase(rule);
            triesPos.erase(rule);
            cout << "\nRegla " << rule << " eliminada\n";
        }else
            cout << "\nNo existe la regla " << rule << "\n";
    }
    ll getNumberShow(string &someCad){
        string temp = "";
        for(auto& c: someCad){
            if(c == ',')
                break;
            temp += c;
        }
        someCad = someCad.substr(temp.size()+1, someCad.size() - temp.size() - 1);
        return stoll(temp);
    }
    void dfsShow(vector<vector<pair<ll,char>>> &adj, vector<ll> &pos, vector<string> &cad, ll node, string cadena = "", string perm = ""){
        if(node >= pos.size()){
            //abcd, 1,3,4,0
            vector<pair<ll, char>> toOrder;
            for(char c : cadena)
                toOrder.push_back(make_pair(getNumberShow(perm), c));
            sort(toOrder.begin(), toOrder.end(), sortPLLC);
            
            string nueva = "";
            for(auto p : toOrder)   nueva += p.second;
            cad.push_back(nueva);
            return;
        }
        for(auto v : adj[node]){
            dfsShow(adj, pos, cad, v.first, cadena + v.second, perm + to_string(pos[node]) + ",");
        }
    }
    void showRule(string rule){
        if(rulesNames.count(rule) > 0){
            vector<string> cadenas;
            dfsShow(tries[rule], triesPos[rule], cadenas, 0);
            for(string s : cadenas)
                cout << rule << " " << s << "\n";
        }else
            cout << "\nNo existe la regla " << rule << "\n";
    }

};

#endif