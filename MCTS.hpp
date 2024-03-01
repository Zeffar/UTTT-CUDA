#ifndef MCTS_HPP
#define MCTS_HPP
#include "node.hpp"
#include "bitset.hpp"

template <size_t M, size_t N>
class MCTS {
private:
    //toDo: turn mechanics

    Node<M, N>* root;
    double exploration = sqrt(2);

    
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

    int rollout() {
    //     node* currentNode = new Node(this->gameState);
    //     while(gameNotOver) {
    //          simulateRandomMove();
    //     }
    //     delete currentNode
    //     return currentNode->score;
        return rand() % 2;
    }

public: 
    MCTS(const bitset2D<M, N>& initState) {
        root = new Node<M,N>(initState);
    }
    ~MCTS() {
        delete root;
    }

    Node<M, N>* select(Node<M, N>* node) {
        while (!node->isLeaf()) {
            node = selectBestChild(node);
        }
        return node;
    }

    void search(int iterations) {
        for (int i = 0; i < iterations; ++i) {
            Node<M, N>* leaf = selectLeaf(root);
            if (!leaf->isOver()) {
                expand(leaf);
            }
            int result = rollout(leaf);
            backpropagate(leaf, result);
        }
    }

};
#endif