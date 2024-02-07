#ifndef NODE_HPP
#define NODE_HPP
#define node Node<M, N>
#include <vector>
#include "bitset.hpp"

template <size_t M, size_t N>
class Node {
public:
    bitset2D<M, N> gameState;
    node* parent;
    std::vector<node*> children;
    int wins;
    int visits;
    int score;

    Node(const bitset2D<M, N>& state, node* parent = nullptr)
        : gameState(state), parent(parent), wins(0), visits(0) {}

    void addChild(const bitset2D<M, N>& state) {
        node* child = new node(state, this);
        children.push_back(child);
    }
    // bool isOver() {
    //     //toDo
    // }
    bool isLeaf() const { return children.empty(); }
    node* select() { 
        node* selectedNode = this;
        while(!selectedNode->isLeaf()) {
            for (node* it: selectedNode->children) {
                //evaluate all children

            }
            //select a child using heuristics
        }
        //after the selection reaches a leaf, 
        //return pointer to the selected node
        return selectedNode;
    }
    // int rollout() {
    //     node* currentNode = new Node(this->gameState);
    //     while(gameNotOver) {
    //          simulateRandomMove();
    //     }
    //     delete currentNode
    //     return currentNode->score;
    // }



    ~Node() {
        for (node child : children) {
            delete child;
        }
    }
};

#endif
