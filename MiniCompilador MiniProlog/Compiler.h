#ifndef COMPILER_H
#define COMPILER_H

#include "lib.h"
#include "trieHeu.h"
#include "trieOpt.h"

class Compiler{
    set<string> rulesNames;
    unordered_map<string, vector<string>> mapa;
    unordered_map<string, unordered_set<string>> mapaCheck;
public:
    Compiler(){
        cout << "\nCompilador creado\n";
    }

    void compile(string inputFile, bool opt){
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
                //tri.print();
            }else{
                trieHeu tri(y.first, y.second.size(), y.second[0].size(), y.second);
                tri.write(offile, outputFile);
                //tri.print();
            }
        }
        cout << "\nCompilacion terminada\n";
        file.close();
        offile.close();
    }

    string getRuleName(string rule){
        auto x = rule.find(' ');
        return rule.substr(0, x);
    }

    string getCharsByRule(string rule){
        auto x = rule.find(' ');
        return rule.substr(x+1, rule.size());
    }

    void read(fstream &file){ 
        if(file.is_open()){
            string temporal;
            while(getline(file, temporal)){
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