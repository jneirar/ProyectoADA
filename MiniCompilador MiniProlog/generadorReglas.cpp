#include "lib.h"

int main(){
    srand (time(NULL));
    ofstream file;
    string outputFile = "rules.txt";
    file.open(outputFile);
    string regla = "Regla";
    int n, m;
    cout << "Ingrese: ";
    cin >> n >> m;
    vector<string> cadenas(n);

    vector<ll> alfabeto;
    for(ll i = 0; i<26; i++){
        alfabeto.push_back(i);
    }

    for(ll j = 0; j < m; j++){
        cout << j << " 1:\n";
        vector<ll> veces;
        ll sum = 0;
        while(sum < n){
            ll a = rand() % 50 + 1; //(1 a 50)
            if(sum + a < n)
                veces.push_back(a);
            else
                break;
            if(veces.size() == 24)
                break;
            sum += a;
        }
        if(sum < n) veces.push_back(n-sum);
        ll idx = 0;
        set<ll> tomados;
        for(ll k = 0; k < 26; k++)  tomados.insert(k);
        cout << j << " 2:\n";
        for(auto v : veces){
            int choose;
            choose = rand() % tomados.size();
            cout << v << " - " << char(choose+'a')  << " idx: " << idx << endl;
            for(ll i = 0; i < v; i++){
                cadenas[i+idx] += char(choose+'a');
                //cadenas[i][m] = char(choose+'a');
            }
            idx += v;
            if(tomados.size() != 1){
                tomados.erase(choose);
            }
        }
    }
    for(auto s : cadenas){
        file << regla << "(";
        for(ll i = 0; i < s.length(); i++){
            file << s[i];
            if(i != s.length() - 1)
                file << ", ";
            else
                file << ")\n";            
        }
    }
    cout << "\nCreado correctamente\n";
    return 0;
}