#pragma GCC optimize("O3,unroll-loops")
#include <iostream>
#include <algorithm>
#include <cmath>
#include <fstream>
#include "bitset.hpp"
#include "node.hpp"
using namespace std;

const int N = 9, M = 18;
int main() {
    bitset2D<9,18> b;
    string file = "gameState.txt";
    ifstream read(file);
    srand(time(0));
    short x;
    for(short i{}; i < 9; ++i) {
        for(short j{}; j < 18; j+=2) {
            read>>x;
            if(x) {
                b.set(i, j+2-x);
            }
        }
    }
    auto root = new Node(b);
    root->gameState.debug();
    

    return 0;
}