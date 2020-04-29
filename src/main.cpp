#include <iostream>
#include "exp3.h"
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<pair<string, string>> vec;
    for (int i = 0; i < n; i++) {
        string s1, s2;
        cin >> s1 >> s2;
        vec.emplace_back(s1, s2);
    }


    exp3 e(vec);
    e.print_ret();
}

/*
7
lparen (
ident a
plus + 
number 15
rparen ) 
times * 
ident b 

2
ident a
plus +

5
lparen (
ident a
plus +
number 15
rparen )

4
lparen (
ident a
plus +
ident b

4
lparen (
ident a
rparen )
ident b

4
lparen (
plus +
rparen )
ident b

2
times *
ident b
*/