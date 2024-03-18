#ifndef MCTS_HPP
#define MCTS_HPP
#include "node.hpp"
#include "bitset.hpp"

template <short M, short N>
class MCTS {
private:
    //toDo: turn mechanics

    Node<M, N> root;
    double exploration = sqrt(2);
    
    void expand(Node<M, N>& node) {
        // todo `generatePossibleMoves`
        auto possibleMoves = node->generatePossibleMoves();
        for (const auto& move : possibleMoves) {
            Node<M, N>* childNode = new Node<M, N>(node->state.applyMove(move));
            node->addChild(childNode);
        }
    }

    void backpropagate(Node<M, N>* leaf, bool result) {
        Node<M, N>* currentNode = leaf;
        while (currentNode != nullptr) {
            currentNode->visits ++;
            currentNode->wins[result] ++;

            currentNode = currentNode->parent;
        }
    }

    
    Node<M, N>* selectBestChild(Node<M, N>* node) {
        Node<M, N>* bestChild = nullptr;
        double bestValue = std::numeric_limits<double>::lowest();

        for (auto& child : node->children) {
            double uctValue = 
                static_cast<double>(child->wins) / static_cast<double>(child->visits) +
                exploration * sqrt(log(static_cast<double>(node->visits)) / static_cast<double>(child->visits));

            if (uctValue > bestValue) {
                bestValue = uctValue;
                bestChild = child;
            }
        }

        return bestChild;
    }

    Node<M, N>* selectLeaf(Node<M, N>* node) {
        while (!node->isLeaf() && !node->isOver()) {
            node = selectBestChild(node);
        }
        return node;
    }

    bool rollout(Node<M, N>* node) {
        Node<M, N>* currentNode = node;
        bool winner = 0;
        while (!currentNode->isOver()) {
            currentNode->simulateRandomMove();
        }

        return winner;
    }

public: 

    MCTS(const bitset2D<M, N>& initState) : root(initState) {}

    Node<M, N> getRoot() const {
        return root;
    }

    void search(int iterations) {
        for (int i = 0; i < iterations; ++i) {
            Node<M, N>* leaf = selectLeaf(&root);
            if (!leaf->isOver()) {
                expand(leaf);
                bool result = rollout(leaf);
                backpropagate(leaf, result);
            }
        }
    }


};

#endif