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
    int wins[2];
    int visits;
    int score;

public:
    Node(const bitset2D<M, N>& state, Node<M, N>* parent = nullptr)
        : gameState(state), parent(parent), visits(0) { wins[0]=wins[1]=0;}

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
        for (Node<M, N>* child : children) {
            delete child;
        }
    }

    bitset2D<M, N> get() const {
        return gameState;
    }
};
template <size_t M, size_t N>
std::ostream &operator<<(std::ostream &out, const Node<M, N> &x){
    // out<<1;
    bitset2D<M, N> state = x.get();

    for(short j{}; j < N; j+=2) {
      out<<state(M-1, j)*2 + state(M-1, j+1)<<" ";
      if((j/2)%3==2) out<<'\n';
    } //big board (toDo: make it clean)

    for(short i{}; i < M-1; ++i) {
        for(short j{}; j < N; j+=2) 
            out<<state(i, j)*2 + state(i, j+1)<<" ";
        out<<'\n';
    } //small board
  return out;
}
 
#endif
