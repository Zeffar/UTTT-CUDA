#include <iostream>
#include <algorithm>
#include <cmath>
#include <fstream>
#include "GUI.hpp"
#include "avizier.hpp"

using namespace std;

int main(int, char **)
{

    const int M = 11, N = 18;
    // string file = "gameState.txt";
    // ifstream read(file);
    // srand(time(0));
    // bitset2D<M, N> b;
    // read>>b;
    // read.close();

    // Node<M, N> root(b);
    // cout<<root<<'\n';
    // MCTS tree(b);
    // tree.search(1000);
    // cout<<"Search done\n";

    GUI<M, N> gui;
    gui.Run();

    return 0;
}

