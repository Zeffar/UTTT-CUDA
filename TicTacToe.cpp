#include <iostream>
#include <algorithm>
#include <cmath>
#include <fstream>
#include "GUI.hpp"

using namespace std;

int main(int, char **)
{

    const int M = 10, N = 18;
    // string file = "gameState.txt";
    // ifstream read(file);
    // srand(time(0));
    // bitset2D<M, N> b;
    // read>>b;
    // read.close();

    // // Node<M, N> root(b);
    // // cout<<root<<'\n';
    // MCTS tree(b);
    // tree.search(1000);
    // // cout<<tree.getRoot()<<'\n';
    // cout<<"Search done\n";

    GUI gui;
    gui.Run();

    return 0;
}

