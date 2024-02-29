#pragma GCC optimize("O3,unroll-loops")
#include <iostream>
#include <algorithm>
#include <cmath>
#include <fstream>
#include "bitset.hpp"
#include "node.hpp"
#include "MCTS.hpp"
using namespace std;

const int N = 10, M = 18;
int main() {
    string file = "gameState.txt";
    ifstream read(file);
    srand(time(0));
    bitset2D<N, M> b;

    short x;
    for(short i{}; i < N; ++i) {
        for(short j{}; j < M; j+=2) {
            read>>x;
            if(x) {
                b.set(i, j+2-x);    
            }
        }
    }

    auto root = new Node(b);
    root->addChild(b);
    root->children[0]->gameState.set(4, 4);
    root->children[0]->gameState.debug();
    cout<<"\n\n";
    root->gameState.debug();
    // auto selectedNode = root->select();
    // selectedNode->gameState.debug();

    return 0;
}