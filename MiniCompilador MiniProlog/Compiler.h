#ifndef COMPILER_H
#define COMPILER_H

#include "lib.h"
#include "trieHeu.h"
#include "trieOpt.h"

class Compiler{
    vector<string> rules;
    set<string> rulesNames;
    unordered_map<string, vector<string>> mapa;
    unordered_map<string, unordered_set<string>> mapaCheck;
public:
    Compiler(){
        cout << "\nCompilador creado\n";
    }

    void compile(string inputFile, bool opt){
        rules.clear();
        rulesNames.clear();
        mapa.clear();
        mapaCheck.clear();
        fstream file;
        ofstream offile;

        string outputFile;
        if(opt)
            outputFile = "opt.trie";
        else
            outputFile = "heu.trie";

        file.open(inputFile, ios::in);
        offile.open(outputFile);
        read(file);
        for(auto y: mapa){
            if(opt){
                trieOpt tri(y.first, y.second.size(), y.second[0].size(), y.second);
                tri.write(offile, outputFile);
            }else{
                trieHeu tri(y.first, y.second.size(), y.second[0].size(), y.second);
                tri.write(offile, outputFile);
            }
        }
        cout << "\nCompilacion terminada\n";
        file.close();
        offile.close();
    }

    string getRuleName(string &rule){
        string temp = "";
        string temp2 = "";
        for(auto& c: rule){
            if(c == '(')
                break;
            temp += c;
        }
        return temp;
    }

    string getCharsByRule(string &rule){
        string caracteres = "";
        auto x = rule.find('(');
        for(unsigned int i = x + 1; i < rule.size() - 1; ++i){
            if(rule[i] != ',' && rule[i] != ' '){
                caracteres += rule[i];
            }
        }
        return caracteres;
    }

    void read(fstream &file){ 
        if(file.is_open()){
            string temporal;
            while(getline(file, temporal)){
                rules.push_back(temporal);
                if(rulesNames.find(getRuleName(temporal)) == rulesNames.end()){
                    rulesNames.insert(getRuleName(temporal));
                    mapa[getRuleName(temporal)].push_back(getCharsByRule(temporal));
                    mapaCheck[getRuleName(temporal)].insert(getCharsByRule(temporal));
                }else{
                    string chars = getCharsByRule(temporal);
                    if(mapaCheck[getRuleName(temporal)].find(chars) == mapaCheck[getRuleName(temporal)].end()){
                        mapa[getRuleName(temporal)].push_back(chars);
                        mapaCheck[getRuleName(temporal)].insert(chars);
                    }
                }
            }
        }
    }
};

#endif