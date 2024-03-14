#ifndef NODE_HPP
#define NODE_HPP
#include <vector>
#include "bitset.hpp"

template <size_t M, size_t N>
class Node
{
private:
    bitset2D<M, N> gameState;
    Node<M, N> *parent;
    std::vector<Node<M, N> *> children;
    int wins[2];
    int visits;
    int score;

    // bitset2D<3, 3>* getSmallBoard() {

    // }

public:
    Node(const bitset2D<M, N> &state, Node<M, N> *parent = nullptr)
        : gameState(state), parent(parent), visits(0) { wins[0] = wins[1] = 0; }

    void addChild(const bitset2D<M, N> &state)
    {
        Node<M, N> *child = new Node<M, N>(state, this);
        children.push_back(child);
    }

    bool isLeaf() const
    {
        return children.empty();
    }

    short isOver()
    {
        for (int i = 0; i < 3; ++i)
        {
            if (gameState[i, 0] && gameState[i, 0] == gameState[i, 1] && gameState[i, 0] == gameState[i, 2] ||
                gameState[0, i] && gameState[0, i] == gameState[1, i] && gameState[0, i] == gameState[2, i])
                return gameState[i, 0];
        }

        if (gameState[0, 0] && gameState[0, 0] == gameState[1, 1] && gameState[0, 0] == gameState[2, 2] ||
            gameState[0, 2] && gameState[0, 2] == gameState[1, 1] && gameState[0, 2] == gameState[2, 0])
            return gameState[1, 1];

        for (short i{}; i < 3; ++i)
            for (short j{}; j < 3; ++j)
                if (gameState[i, j] == 0)
                    return 0;

        return 3;
    }

    ~Node()
    {
        for (Node<M, N> *child : children)
        {
            delete child;
        }
    }

    bitset2D<M, N> get() const
    {
        return gameState;
    }
};
template <size_t M, size_t N>
std::ostream &operator<<(std::ostream &out, const Node<M, N> &x)
{
    bitset2D<M, N> state = x.get();

    for (short i{}; i < 3; ++i)
    {
        for (short j{}; j < 3; j++)
            out << state[i, j] << " ";
        out << '\n';
    }

    for (int x{}; x < 3; ++x)
    {
        for (short i{}; i < 3; ++i)
        {
            for (int y{}; y < 3; ++y)
            {
                for (short j{}; j < 3; j++)

                {
                    out << state(x, y, i, j) << " ";
                }
            }
            out << '\n';
        }
    }

    return out;
}

#endif
