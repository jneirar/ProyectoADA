#ifndef LIB_H
#define LIB_H

#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <array>
#include <cctype>
#include <stdlib.h>     
#include <time.h>
#include <ctime>
#include <fstream>
#include <stdio.h>
#include <ctype.h>

using namespace std;
#define ll long long
#define pll pair<ll, ll>
#define plc pair<ll, char>
#define vll vector<ll>
#define vplc vector<plc>
#define vvplc vector<vplc>
#define trieType unordered_map< string, vvplc >
#define triePosType unordered_map< string, vll >

bool sortP(pair<ll, ll> p1, pair<ll, ll> p2){
    if(p1.second == p2.second)  return p1.first < p2.first;
    return p1.second < p2.second;
}

template< typename F, typename S >
struct PairComparator {
bool operator()( const pair<F, S>& p1, const pair<F, S>& p2 ) const {  
        return p1.first > p2.first;
    }
};

unsigned t0, t1;
double tiempo;

double timeCalculate(double t0, double t1){
    return (double(t1-t0)/(CLOCKS_PER_SEC/1));
}

#endif