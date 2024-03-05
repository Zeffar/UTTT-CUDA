#ifndef NODE_HPP
#define NODE_HPP
#include <vector>
#include "bitset.hpp"

template <size_t M, size_t N>
class Node {
private:
    bitset2D<M, N> gameState;
    Node<M, N>* parent;
    std::vector<Node<M, N>*> children;
    int wins;
    int visits;
    int score;

public:
    
    Node(const bitset2D<M, N>& state, Node<M, N>* parent = nullptr)
        : gameState(state), parent(parent), wins(0), visits(0) {}

    void addChild(const bitset2D<M, N>& state) {
        Node<M, N>* child = new Node<M, N>(state, this);
        children.push_back(child);
    }

    bool isLeaf() const { 
        return children.empty(); 
    }
    
    // bool isOver() {
    //     //toDo
    // }
    
    ~Node() {
        for (Node<M, N> child : children) {
            delete child;
        }
    }
};
#endif
