#ifndef NODE_HPP
#define NODE_HPP
#include <vector>
#include "bitset.hpp"

template <short M, short N>
class GameState
{
protected:
    bitset2D<M, N> gameState;
    short x, y; // which mini-board you can play in
    bool turn;  // which player's turn it is
public:
    GameState() : gameState(), x(0), y(0), turn(0) {}

    GameState(const bitset2D<M, N> &state)
        : gameState(state), x(0), y(0), turn(0) {}

    virtual void move(short x, short y, short i, short j)
    {
        gameState.set(3 * x + i, 3 * y + j, turn + 1);
        if (isOverMini(x, y))
        {
            gameState.set(M - 2, j, turn + 1);
        }
    }
    virtual void flip_turn()
    {
        turn = 1 - turn;
    }
    virtual void changeBoard(short i, short j)
    {
        x = i;
        y = j;
    }
    virtual short getX() {return x;}
    virtual short getY() {return y;}
    
    virtual short isOver() const // returns 0 if not over, 1 if p1 won, 2 if p2 won, 3 if draw
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

    virtual short isOverMini(short x, short y) const
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
    virtual bitset2D<M, N> get() const
    {
        return gameState;
    }
};

template <short M, short N>
class Node : public GameState<M, N>
{
private:
    Node<M, N> *parent;
    std::vector<Node<M, N> *> children;
    int wins[3];
    short visits;
    short score;

    void addChild(Node<M, N> *child)
    {
        children.push_back(child);
        child->parent = this;
    }

public:
    Node(const bitset2D<M, N> &state, Node<M, N> *parent = nullptr)
        : GameState<M, N>(state), parent(parent), visits(1), score(0) { wins[0] = wins[1] = 0; }

    bool isLeaf() const
    {
        return children.empty();
    }

    void getBest(short v[4])
    {
        int maxScore = -1;
        v[0] = this->x;
        v[1] = this->y;
        for (auto &child : children)
        {
            if (child->wins[this->turn] > maxScore)
            {
                v[2] = child->x;
                v[3] = child->y;
                maxScore = wins[this->turn];
            }
        }
        return;
    }

    void expand()
    {
        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                if (this->gameState(this->x, this->y, i, j) == 0)
                {
                    Node<M, N> *child = new Node<M, N>(this->gameState);
                    child->move(this->x, this->y, i, j);
                    addChild(child);
                    child->flip_turn();
                    // child->turn = 1 - this->turn;
                    child->changeBoard(i, j);
                    // child->x = i;
                    // child->y = j;
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
                    if (this->gameState(this->x, this->y, i, j) == 0)
                    {
                        possibleMoves.push_back({i, j});
                    }
                }
            }
            short len = possibleMoves.size();
            if (!len)
                return this->isOver();
            short choice = rand() % len;
            this->move(this->x, this->y, possibleMoves[choice].first, possibleMoves[choice].second);
            this->x = possibleMoves[choice].first;
            this->y = possibleMoves[choice].second;
            this->turn = 1 - this->turn;

            // if game over, retun winner
            winner = this->isOver();
            if (winner)
                return winner;
        }
    }

    void backpropagate(short result)
    {
        Node<M, N> *currentNode = this;
        while (currentNode != nullptr)
        {
            currentNode->visits++;
            currentNode->wins[result]++;
            currentNode = currentNode->parent;
        }
    }

    Node<M, N> *selectBestChild(double exploration)
    {
        Node<M, N> *bestChild = nullptr;
        double bestValue = -1;
        for (auto &child : children)
        {
            double uctValue =
                static_cast<double>(child->wins[this->turn]) / static_cast<double>(child->visits) +
                exploration * sqrt(log(static_cast<double>(visits)) / static_cast<double>(child->visits));

            if (uctValue > bestValue)
            {

                bestValue = uctValue;
                bestChild = child;
            }
        }
        return bestChild;
    }

    Node<M, N> &operator=(const Node<M, N> &other)
    {
        if (this != &other)
        {
            this->gameState = other.gameState;
            parent = other.parent;
            children = other.children;
            this->x = other.x;
            this->y = other.y;
            this->turn = other.turn;
            wins[0] = other.wins[0];
            wins[1] = other.wins[1];
            visits = other.visits;
            score = other.score;
        }
        return *this;
    }
};

template <short M, short N>
std::ostream &operator<<(std::ostream &out, const GameState<M, N> &x)
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
