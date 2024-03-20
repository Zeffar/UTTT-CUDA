#ifndef NODE_HPP
#define NODE_HPP
#include <vector>
#include "bitset.hpp"

template <short M, short N>
class Node
{
private:
    bitset2D<M, N> gameState;
    Node<M, N> *parent;
    std::vector<Node<M, N> *> children;
    short x, y; // which mini-board you can play in
    bool turn;  // which player's turn it is
    short wins[2];
    short visits;
    short score;
    void move(short x, short y, short i, short j)
    {
        gameState(x, y, i, j) = turn + 1;
        if (isOverMini(x, y))
            gameState[x, y] = turn + 1;
    }

    void addChild(const Node<M, N> *child)
    {
        children.push_back(child);
    }

public:
    Node(const bitset2D<M, N> &state, Node<M, N> *parent = nullptr)
        : gameState(state), parent(parent), visits(0) { wins[0] = wins[1] = 0; }

    bool isLeaf() const
    {
        return children.empty();
    }

    // void expand()
    // {
    //     // todo `generatePossibleMoves`
    //     auto possibleMoves = node->generatePossibleMoves();
    //     for (const auto &move : possibleMoves)
    //     {
    //         Node<M, N> *childNode = new Node<M, N>(node->state.applyMove(move));
    //         node->addChild(childNode);
    //     }
    // }
    void expand()
    {
        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                if (gameState(x, y, i, j) == 0)
                {
                    bitset2D<M, N> childBoard = gameState;
                    childBoard.move(x, y, i, j);
                    Node<M, N> *child = new Node<M, N>(childBoard);
                    addChild(child);
                }
            }
        }
    }

    short rollout()
    {
        short winner = 0;
        while (true)
        {
            // pick random move
            std::vector<std::pair<short, short>> possibleMoves;
            for (int i = 0; i < 3; ++i)
            {
                for (int j = 0; j < 3; ++j)
                {
                    if (gameState(x, y, i, j) == 0)
                    {
                        possibleMoves.push_back({i, j});
                    }
                }
            }
            short len = possibleMoves.size();
            short choice = rand() % len;
            gameState.move(x, y, possibleMoves[choice].first, possibleMoves[choice].second);

            // if game over, retun winner
            winner = isOver();
            if (winner)
                return winner;
            
        }
    }

    // void backpropagate(Node<M, N> *leaf, bool result)
    // {
    //     Node<M, N> *currentNode = leaf;
    //     while (currentNode != nullptr)
    //     {
    //         currentNode->visits++;
    //         currentNode->wins[result]++;

    //         currentNode = currentNode->parent;
    //     }
    // }

    short isOver() // returns 0 if not over, 1 if p1 won, 2 if p2 won, 3 if draw
    {
        for (short i = 0; i < 3; ++i)
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

    short isOverMini(short x, short y)
    {
        for (short i = 0; i < 3; ++i)
        {
            if (gameState(x, y, i, 0) && gameState(x, y, i, 0) == gameState(x, y, i, 1) && gameState(x, y, i, 0) == gameState(x, y, i, 2) ||
                gameState(x, y, 0, i) && gameState(x, y, 0, i) == gameState(x, y, 1, i) && gameState(x, y, 0, i) == gameState(x, y, 2, i))
                return gameState(x, y, i, 0);
        }

        if (gameState(x, y, 0, 0) && gameState(x, y, 0, 0) == gameState(x, y, 1, 1) && gameState(x, y, 0, 0) == gameState(x, y, 2, 2) ||
            gameState(x, y, 0, 2) && gameState(x, y, 0, 2) == gameState(x, y, 1, 1) && gameState(x, y, 0, 2) == gameState(x, y, 2, 0))
            return gameState(x, y, 1, 1);

        for (short i{}; i < 3; ++i)
            for (short j{}; j < 3; ++j)
                if (gameState(x, y, i, j) == 0)
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

template <short M, short N>
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
