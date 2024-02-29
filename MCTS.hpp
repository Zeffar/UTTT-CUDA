#ifndef MCTS_HPP
#define MCTS_HPP
#include "node.hpp"
#include "binders.h"

template <size_t M, size_t N>
class MCTS {
public:
    Node root;
    // bool isOver() {
    //     //toDo
    // }
    
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


};
#endif