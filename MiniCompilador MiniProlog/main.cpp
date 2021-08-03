#include "lib.h"
#include "Compiler.h"
#include "Parser.h"

void solve();
int menu1();

bool flag;
Compiler compiler;
Parser parser;

int main()
{
    srand (time(NULL));
    do{
        flag = 1;
        solve();
    }while(flag);
    cout << "\n\nPrograma finalizado exitosamente\n\n";
    return 0;
}

void solve(){
    int opt1 = menu1();
    if(opt1 == 6){
        flag = 0;
        return;
    }

    switch (opt1){
        case 1:{    //Compilación heurística
            t0 = clock();
            compiler.compile("rules.txt", false);
            parser.parse(false);
            t1 = clock();
            tiempo = timeCalculate(t0, t1);
            cout << "\nExecution Time: " << tiempo << "\n";
            break;
        }
        case 2:{    //Compilación óptima
            t0 = clock();
            compiler.compile("rules.txt", true);
            parser.parse(true);
            t1 = clock();
            tiempo = timeCalculate(t0, t1);
            cout << "\nExecution Time: " << tiempo << "\n";
            break;
        }   
        case 3:{    //Ejecución de consultas
            t0 = clock();
            parser.queryExecuter("queries.txt");
            t1 = clock();
            tiempo = timeCalculate(t0, t1);
            cout << "\nExecution Time: " << tiempo << "\n";
            break;
        }
        case 4:{    //Mostrar reglas en memoria
            parser.showRules();
            break;
        }
        case 5:{    //Elimina regla
            cout << "Inserte regla a eliminar: ";
            string r;
            cin >> r;
            parser.eraseRule(r);
            break;
        }
    }
}

int menu1(){
    int opt = 0, optMax = 6;
    do{
        cout << "\n\n--------------------Proyecto de Analisis y Disenho de Algoritmos--------------------\n";
        cout << "1. Compilacion heuristica.\n";
        cout << "2. Compilacion optima.\n";
        cout << "3. Ejecutar consultas.\n";
        cout << "4. Mostrar reglas en memoria.\n";
        cout << "5. Borrar regla.\n";
        cout << "6. Salir del programa.\n";
        cout << "Ingrese una opcion: ";
        cin >> opt;
    }while(!isdigit(opt) && (opt < 1 || opt > optMax) );
    return opt;
}