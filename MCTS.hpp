#ifndef MCTS_HPP
#define MCTS_HPP
#include "node.hpp"
#include "bitset.hpp"

template <short M, short N>
class MCTS
{
private:

    Node<M, N> root;
    double exploration = sqrt(2);


    Node<M, N> *selectLeaf(Node<M, N> *node)
    {
        while (!node->isLeaf())
        {
            node = node->selectBestChild(exploration);
        }
        return node;
    }

public:
    MCTS(const bitset2D<M, N> &initState) : root(initState) {}

    Node<M, N>* getRoot() const
    {
        return *root;
    }

    void search(int iterations)
    {
        for (int i = 0; i < iterations; ++i)
        {
            Node<M, N> *leaf = selectLeaf(&root);
            if (!leaf->isOver())
            {
                leaf->expand();
                Node <M, N> aux = *leaf;
                bool result = aux.rollout();
                leaf->backpropagate(result-1); // 0 for player 1, 1 for player 2, 2 for draw
            }
        }
    }
};

#endif