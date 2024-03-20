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

    Node<M, N> *selectBestChild(Node<M, N> *node)
    {
        Node<M, N> *bestChild = nullptr;
        double bestValue = std::numeric_limits<double>::lowest();

        for (auto &child : node->children)
        {
            double uctValue =
                static_cast<double>(child->wins) / static_cast<double>(child->visits) +
                exploration * sqrt(log(static_cast<double>(node->visits)) / static_cast<double>(child->visits));

            if (uctValue > bestValue)
            {
                bestValue = uctValue;
                bestChild = child;
            }
        }

        return bestChild;
    }

    Node<M, N> *selectLeaf(Node<M, N> &node)
    {
        while (!node->isLeaf())
        {
            node = selectBestChild(node);
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
            Node<M, N> *leaf = selectLeaf(root);
            if (!leaf->isOver())
            {
                leaf->expand();
                Node <M, N> aux = *leaf;
                bool result = aux->rollout();
                leaf->backpropagate(result);
            }
        }
    }
};

#endif