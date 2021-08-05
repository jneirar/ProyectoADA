#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>
#include <unordered_map>
#include "trie.h"

using namespace std;

vector<string> rules;
set<string> rulesNames;
vector<string> chars;
unordered_map<string, vector<string>> mapa;

string getRuleName(string rule){
    auto x = rule.find(' ');
    return rule.substr(0, x);
}

string getCharsByRule(string rule){
    auto x = rule.find(' ');
    return rule.substr(x+1, rule.size());
}

void read(fstream &file, string &inputName){ 
    if(file.is_open()){
        string temporal;
        while(getline(file, temporal)){
            rules.push_back(temporal);
            if(rulesNames.find(getRuleName(temporal)) == rulesNames.end()){
                rulesNames.insert(getRuleName(temporal));
                mapa[getRuleName(temporal)].push_back(getCharsByRule(temporal));
            }else{
                mapa[getRuleName(temporal)].push_back(getCharsByRule(temporal));
            }
        }
    }

}



int main()
{
  fstream file;
  ofstream offile;
  string inputFile = "input.txt";
  string outputFile = "output.txt";
  file.open(inputFile, ios::in);
  offile.open(outputFile);
  read(file, inputFile);
  
  for(auto y: mapa){
    trie tri(y.first, y.second.size(), y.second[0].size(), y.second);
    tri.write(offile, outputFile);
  }
  cout << "\nArhivo generado\n";
  file.close();
  offile.close();
  return 0;
}
