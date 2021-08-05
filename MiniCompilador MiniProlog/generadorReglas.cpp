#include "lib.h"

int main(){
    srand (time(NULL));
    ofstream file;
    string outputFile = "rules.txt";
    file.open(outputFile);
    string regla = "Regla";
    int n, m, ran;
    cout << "Ingrese: ";
    cin >> n >> m >> ran;
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
            ll a = rand() % ran + 1; //(1 a 50)
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
        vector<ll> tomados;
        for(ll k = 0; k < 26; k++)  tomados.push_back(k);
        cout << j << " 2:\n";
        for(auto v : veces){
            int choose;
            choose = rand() % tomados.size();
            cout << v << " - " << char(tomados[choose]+'a')  << " idx: " << idx << endl;
            for(ll i = 0; i < v; i++)
                cadenas[i+idx] += char(tomados[choose]+'a');
            idx += v;
            if(tomados.size() != 1){
                tomados.erase(tomados.begin()+choose);
            }
        }
    }
    unordered_set<string> setCad;
    for(auto s : cadenas){
        if(setCad.find(s) != setCad.end())  continue;
        file << regla << " " << s << "\n";
        setCad.insert(s);
    }
    cout << "\n" << cadenas.size() - setCad.size() << " repetidos\n";
    cout << "\nCreado correctamente\n";
    return 0;
}