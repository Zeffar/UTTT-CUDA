#pragma GCC optimize("O2,unroll-loops")
#include <iostream>
#include <algorithm>
#include <cmath>
#include <fstream>
#include "bitset.hpp"
#include "node.hpp"
#include "MCTS.hpp"
using namespace std;

const int M = 10, N = 18;
int main() {
    string file = "gameState.txt";
    ifstream read(file);
    srand(time(0));
    bitset2D<M, N> b;
    read>>b;
    read.close();

    // Node<M, N> root(b);
    // cout<<root<<'\n';
    MCTS tree(b);
    tree.search(1000);
    cout<<"Search done\n";

    return 0;
}