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
            std::cout<<"Selecting best child\n";
            node = node->selectBestChild(exploration);
            std::cout<<"Selected node: "<<*node<<'\n';
        }
        return node;
    }

public:
    MCTS(const bitset2D<M, N> &initState) : root(initState) {}

    Node<M, N> getRoot() const
    {
        return root;
    }

    void search(int iterations)
    {
        for (int i = 0; i < iterations; ++i)
        {
            Node<M, N> *leaf = selectLeaf(&root);
            // std::cout<<*leaf<<'\n';
            if (!leaf->isOver())
            {
                leaf->expand();
                Node <M, N> aux = *leaf;
                bool result = aux.rollout();
                leaf->backpropagate(result);
                
            }
        }
    }
};

#endif